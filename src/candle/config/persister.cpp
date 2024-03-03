#include "persister.h"
#include "qguiapplication.h"

Persister::Persister() {
}

QSettings *Persister::open()
{
    return new QSettings(qApp->applicationDirPath() + "/settings.ini", QSettings::IniFormat);
}
