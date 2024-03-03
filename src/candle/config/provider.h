#ifndef PROVIDER_H
#define PROVIDER_H

#include <QSettings>

class Provider
{
public:
    Provider();

private:
    QSettings* open();
};

#endif // PROVIDER_H
