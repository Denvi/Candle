#ifndef PERSISTER_H
#define PERSISTER_H

#include <QSettings>

class Persister
{
public:
    Persister();

private:
    QSettings* open();
};

#endif // PERSISTER_H
