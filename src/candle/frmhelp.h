#pragma once

#include <QDialog>
#include <QHelpEngine>

namespace Ui {
class frmHelp;
}

class frmHelp : public QDialog
{
    Q_OBJECT

public:
    explicit frmHelp(const QString &language, QWidget *parent = nullptr);

private:
    Ui::frmHelp *ui;

    QHelpEngine *m_helpEngine;

    QString prepareHelpFiles();
    void copyFile(const QString &from, const QString &to);
};