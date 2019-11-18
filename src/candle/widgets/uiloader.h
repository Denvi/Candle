#ifndef UILOADER_H
#define UILOADER_H

#include <QUiLoader>

class UiLoader: public QUiLoader
{
    Q_OBJECT
public:
    UiLoader(QObject *parent = 0);

    QWidget *createWidget(const QString &className, QWidget *parent = 0, const QString &name = QString()) override;
};

#endif