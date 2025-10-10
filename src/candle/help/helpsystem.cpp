#include "helpsystem.h"
#include "helpbrowser.h"
#include <QDebug>
#include <QSplitter>
#include <QVBoxLayout>
#include <QTreeView>
#include <QHelpContentWidget>
#include <QApplication>
#include <QStandardPaths>
#include <QDir>
#include <QTextStream>
#include "../utils/util.h"
#include "../loggingcategories.h"

HelpSystem::HelpSystem(const QString &language, QWidget *parent) : QDialog(parent)
{
    auto helpFile = prepareHelpFiles();
    m_helpEngine = new QHelpEngine(helpFile, parent);

    auto contents = m_helpEngine->contentWidget();
    auto browser = new HelpBrowser(m_helpEngine, this);

    auto *split = new QSplitter(Qt::Horizontal);
    split->addWidget(contents);
    split->addWidget(browser);
    split->setStretchFactor(1, 1);

    auto fm = QFontMetrics(QFont());
    split->setHandleWidth(fm.height());

    auto *lay = new QVBoxLayout(this);
    lay->addWidget(split);

    for (const auto &f : m_helpEngine->customFilters())
        if (f.contains("-" + language))
        {
            m_helpEngine->setCurrentFilter(f);
            browser->setSource(QUrl(QString("qthelp://candle.%1/html/purpose/index.html").arg(language)));
            break;
        }

    if (browser->source().isEmpty())
    {
        m_helpEngine->setCurrentFilter("candle-en");
        browser->setSource(QUrl("qthelp://candle.en/html/purpose/index.html"));
    }

    contents->expandAll();

    connect(contents, &QTreeView::clicked, [engine = m_helpEngine, browser](const QModelIndex &idx)
            {
        auto item = engine->contentModel()->contentItemAt(idx);
        browser->setSource(item->url()); });

    connect(contents, &QHelpContentWidget::linkActivated, browser, qOverload<const QUrl &>(&QTextBrowser::setSource));

    if (!m_helpEngine->setupData())
    {
        qWarning() << "Help engine setup failed:" << m_helpEngine->error();
        return;
    }
}

QString HelpSystem::prepareHelpFiles()
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

void HelpSystem::copyFile(const QString &from, const QString &to)
{
    auto fileInfo = QFileInfo(to);

    QDir().mkpath(fileInfo.absolutePath());

    if (QFile::exists(to))
        QFile::remove(to);

    QFile::copy(from, to);
}