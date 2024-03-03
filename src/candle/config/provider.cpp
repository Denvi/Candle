#include "provider.h"
#include "qguiapplication.h"

Provider::Provider() {
}

QSettings *Provider::open()
{
    return new QSettings(qApp->applicationDirPath() + "/settings.ini", QSettings::IniFormat);
}
