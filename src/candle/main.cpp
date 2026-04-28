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

    return a.exec();
}