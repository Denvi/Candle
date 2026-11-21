// This file is a part of "Candle" application.
// Copyright 2015-2021 Hayrullin Denis Ravilevich

#include <QApplication>
#include <QDebug>
#include <QGLWidget>
#include <QLocale>
#include <QTranslator>
#include <QFile>
#include <QStyleFactory>
#include <QFontDatabase>
#include <QMessageBox>
#include <QDir>

#include "parser/gcodepreprocessorutils.h"
#include "parser/gcodeparser.h"
#include "parser/gcodeviewparse.h"
#include "logging/fileloghandler.h"
#include "versionconfig.h"

#include "automation/automationserver.h"

#include "frmmain.h"

void loadTranslationsForLocale(const QString &locale, QCoreApplication &app)
{
    auto translationsFolder = qApp->applicationDirPath() + "/translations/";
    QDir dir(translationsFolder);

    if (!dir.exists())
        return;

    for (const QString &fileName : dir.entryList(QStringList{ "*_" + locale + ".qm" }, QDir::Files))
    {
        auto tr = new QTranslator(&app);

        if (tr->load(dir.absoluteFilePath(fileName)))
            app.installTranslator(tr);
        else
            delete tr;
    }
}

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
#ifdef Q_OS_LINUX
    QApplication::setAttribute(Qt::AA_DontUseNativeDialogs);
#endif
    QApplication a(argc, argv);

    a.setOrganizationName(APP_NAME);
    a.setApplicationName(APP_NAME);
    a.setApplicationDisplayName(APP_NAME);
    a.setApplicationVersion(APP_VERSION);

    installFileLogHandler();

    QSettings set;
    QString locale = set.value("General/language", "en").toString();

    loadTranslationsForLocale(locale, a);

    a.setStyleSheet(a.styleSheet() + "QWidget {font-size: 8pt}");

    // MCP (Model Context Protocol) automation endpoint, off by default:
    // --mcp [port]           enable JSON-RPC endpoint on 127.0.0.1 (default port 8765)
    // --mcp-port <port>      explicit port
    // --mcp-allow-motion     unlock motion tools (gcode_send/jog/motion_control/job_control)
    quint16 mcpPort = 0;
    bool mcpAllowMotion = false;
    const QStringList argList = a.arguments();
    for (int i = 1; i < argList.size(); i++) {
        if (argList[i] == "--mcp") {
            mcpPort = 8765;
            if (i + 1 < argList.size() && argList[i + 1].toInt())
                mcpPort = argList[++i].toUShort();
        } else if (argList[i] == "--mcp-port" && i + 1 < argList.size()) {
            mcpPort = argList[++i].toUShort();
        } else if (argList[i] == "--mcp-allow-motion") {
            mcpAllowMotion = true;
        }
    }

    frmMain w;

#if defined(Q_OS_WIN) || defined(Q_OS_LINUX)
    QFile styles(":/styles/frmmaindefault.qss");
#elif defined(Q_OS_MAC)
    QFile styles(":/styles/frmmainmacos.qss");
#else
    QFile styles(":/styles/frmmaindefault.qss");
#endif

    if (styles.open(QFile::ReadOnly))
        w.setStyleSheet(styles.readAll());

    w.show();

    if (mcpPort) {
        AutomationServer *mcp = new AutomationServer(&w, mcpPort, mcpAllowMotion, &w);
        mcp->start();
    }

    return a.exec();
}