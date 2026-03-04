#ifndef CANDLEPATHS_H
#define CANDLEPATHS_H

#include <QString>
#include <QApplication>

static inline QString candleTranslationsDir()
{
    QString dir = CANDLE_TRANSLATIONS_DIR;
    return dir.isEmpty() ? qApp->applicationDirPath() + "/translations" : dir;
}

static inline QString candlePluginsDir()
{
    QString dir = CANDLE_PLUGINS_DIR;
    return dir.isEmpty() ? qApp->applicationDirPath() + "/candleplugins" : dir;
}

static inline QString candleScriptPluginsDir()
{
    QString dir = CANDLE_SCRIPT_PLUGINS_DIR;
    return dir.isEmpty() ? qApp->applicationDirPath() + "/plugins/script" : dir;
}

static inline QString candleDocsDir()
{
    QString dir = CANDLE_DOCS_DIR;
    return dir.isEmpty() ? qApp->applicationDirPath() : dir;
}

static inline QString candleDataDir()
{
    QString dir = CANDLE_DATA_DIR;
    return dir.isEmpty() ? qApp->applicationDirPath() : dir;
}

#endif // CANDLEPATHS_H
