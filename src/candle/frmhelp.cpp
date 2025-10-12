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
#include "loggingcategories.h"

frmHelp::frmHelp(const QString &language, QWidget *parent) : QDialog(parent), ui(new Ui::frmHelp)
{
    ui->setupUi(this);

    ui->splitMain->setStretchFactor(0, 0);
    ui->splitMain->setStretchFactor(1, 1);

    auto helpFile = prepareHelpFiles();
    m_helpEngine = new QHelpEngine(helpFile, this);

    ui->txtBrowser->setHelpEngine(m_helpEngine);

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

    connect(contents, &QTreeView::clicked, [engine = m_helpEngine, browser = ui->txtBrowser](const QModelIndex &idx) {
        auto item = engine->contentModel()->contentItemAt(idx);
        browser->setSource(item->url());
    });

    connect(contents, &QHelpContentWidget::linkActivated, ui->txtBrowser, qOverload<const QUrl &>(&QTextBrowser::setSource));

    connect(m_helpEngine->searchEngine()->queryWidget(), &QHelpSearchQueryWidget::search, [engine = m_helpEngine] {
        engine->searchEngine()->search(engine->searchEngine()->queryWidget()->searchInput());
    });

    connect(m_helpEngine->searchEngine()->resultWidget(), &QHelpSearchResultWidget::requestShowLink,
        [browser = ui->txtBrowser] (const QUrl &url) {
            browser->setSource(url);
    });

    if (!m_helpEngine->setupData())
    {
        qWarning() << "Help engine setup failed:" << m_helpEngine->error();
        return;
    }
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