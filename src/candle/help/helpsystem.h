#pragma once

#include <QObject>
#include <QHelpEngine>
#include <QDialog>

class HelpSystem : public QDialog
{
    Q_OBJECT

public:
    explicit HelpSystem(const QString &language, QWidget *parent = nullptr);

private:
    QHelpEngine *m_helpEngine;

    QString prepareHelpFiles();
    void copyFile(const QString &from, const QString &to);
};