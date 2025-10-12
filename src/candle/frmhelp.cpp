#include "frmhelp.h"
#include "ui_frmhelp.h"
#include <QDebug>
#include <QSplitter>
#include <QVBoxLayout>
#include <QTreeView>
#include <QHelpContentWidget>
#include <QApplication>
#include <QStandardPaths>
#include <QDir>
#include <QTextStream>
#include <QHelpSearchEngine>
#include <QHelpSearchQueryWidget>
#include <QHelpSearchResultWidget>
#include <QHelpFilterEngine>
#include <QShortcut>
#include <QKeyEvent>
#include "loggingcategories.h"

frmHelp::frmHelp(const QString &language, QWidget *parent) : QDialog(parent), ui(new Ui::frmHelp)
{
    ui->setupUi(this);

    ui->splitMain->setStretchFactor(0, 0);
    ui->splitMain->setStretchFactor(1, 1);

    auto helpFile = prepareHelpFiles();
    m_helpEngine = new QHelpEngine(helpFile, this);

    ui->txtBrowser->setHelpEngine(m_helpEngine);

    m_defaultPalette = ui->txtBrowser->palette();
    ui->wgtSearch->setVisible(false);

    auto contents = m_helpEngine->contentWidget();
    contents->setStyleSheet("QTreeView::item { height: 2em; }");
    ui->tabContents->layout()->addWidget(contents);

    ui->tabSearch->layout()->addWidget(m_helpEngine->searchEngine()->queryWidget());
    ui->tabSearch->layout()->addWidget(m_helpEngine->searchEngine()->resultWidget());

    for (const auto &f : m_helpEngine->customFilters())
    {
        if (f.contains("-" + language))
        {
            m_helpEngine->setCurrentFilter(f);
            ui->txtBrowser->setSource(QUrl(QString("qthelp://candle.%1/html/purpose/index.html").arg(language)));
            break;
        }
    }

    if (ui->txtBrowser->source().isEmpty())
    {
        m_helpEngine->setCurrentFilter("candle-en");
        ui->txtBrowser->setSource(QUrl("qthelp://candle.en/html/purpose/index.html"));
    }

    auto searchShortcut = new QShortcut(QKeySequence("CTRL+F"), this);

    connect(searchShortcut, &QShortcut::activated, [this] { showSearchWidget(!ui->wgtSearch->isVisible()); });

    connect(contents, &QTreeView::clicked, [this](const QModelIndex &idx) {
        auto item = m_helpEngine->contentModel()->contentItemAt(idx);
        ui->txtBrowser->setSource(item->url());
    });

    connect(contents, &QHelpContentWidget::linkActivated, ui->txtBrowser, qOverload<const QUrl &>(&QTextBrowser::setSource));

    connect(m_helpEngine->searchEngine()->queryWidget(), &QHelpSearchQueryWidget::search, [this] {
        m_helpEngine->searchEngine()->search(m_helpEngine->searchEngine()->queryWidget()->searchInput());
    });

    connect(m_helpEngine->searchEngine()->resultWidget(), &QHelpSearchResultWidget::requestShowLink,
        [this] (const QUrl &url) { ui->txtBrowser->setSource(url); });

    if (!m_helpEngine->setupData())
    {
        qWarning() << "Help engine setup failed:" << m_helpEngine->error();
        return;
    }

    installEventFilter(this);
}

void frmHelp::on_cmdNext_clicked()
{
    auto r = ui->txtBrowser->find(ui->txtSearch->text());

    if (!r) {
        ui->txtBrowser->moveCursor(QTextCursor::Start);
        ui->txtBrowser->find(ui->txtSearch->text());
    }
}

void frmHelp::on_cmdPrevious_clicked()
{
    auto r = ui->txtBrowser->find(ui->txtSearch->text(), QTextDocument::FindBackward);

    if (!r) {
        ui->txtBrowser->moveCursor(QTextCursor::End);
        auto r = ui->txtBrowser->find(ui->txtSearch->text(), QTextDocument::FindBackward);
    }
}

void frmHelp::on_cmdClose_clicked()
{
   showSearchWidget(false);
}

void frmHelp::showSearchWidget(bool visible)
{
    if (visible) {
        auto p = ui->txtBrowser->palette();
        p.setColor(QPalette::Inactive, QPalette::Highlight, p.color(QPalette::Active, QPalette::Highlight));
        p.setColor(QPalette::Inactive, QPalette::HighlightedText, p.color(QPalette::Active, QPalette::HighlightedText));
        ui->txtBrowser->setPalette(p);
        ui->txtSearch->setFocus();
    } else {
        ui->txtBrowser->setPalette(m_defaultPalette);
    }

    ui->wgtSearch->setVisible(visible);
}

QString frmHelp::prepareHelpFiles()
{
    auto baseDir = qApp->applicationDirPath() + "/help";
    auto dataDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/help";
    auto baseCollectionFile = baseDir + "/candle.qhc";
    auto dataCollectionFile = dataDir + "/candle.qhc";

    QDir().mkpath(dataDir);

    QFile versionFile(dataDir + "/version.txt");
    if (!versionFile.open(QIODevice::ReadWrite))
    {
        qWarning(generalLogCategory) << "Can not open help version file";
        return baseCollectionFile;
    }

    QTextStream stream(&versionFile);
    auto version = stream.readLine();
    if (qApp->applicationVersion() == version)
        return dataCollectionFile;

    qInfo(generalLogCategory) << "Preparing help files";

    versionFile.resize(0);
    stream << qApp->applicationVersion();

    copyFile(baseCollectionFile, dataCollectionFile);
    copyFile(baseDir + "/en/candle.qch", dataDir + "/en/candle.qch");
    copyFile(baseDir + "/ru/candle.qch", dataDir + "/ru/candle.qch");
    copyFile(baseDir + "/script/script.qch", dataDir + "/script/script.qch");

    return dataCollectionFile;
}

void frmHelp::copyFile(const QString &from, const QString &to)
{
    auto fileInfo = QFileInfo(to);

    QDir().mkpath(fileInfo.absolutePath());

    if (QFile::exists(to))
        QFile::remove(to);

    QFile::copy(from, to);
}

bool frmHelp::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        auto ke = static_cast<QKeyEvent*>(event);

        if (ke->key() == Qt::Key_Escape)
        {
            if (ui->wgtSearch->isVisible())
            {
                showSearchWidget(false);
                return true;
            }
        }
    }

    return QDialog::eventFilter(obj, event);
}