#pragma once

#include <QDialog>
#include <QHelpEngine>
#include <QPalette>

namespace Ui {
class frmHelp;
}

class frmHelp : public QDialog
{
    Q_OBJECT

public:
    explicit frmHelp(const QString &language, QWidget *parent = nullptr);

private slots:
    void on_cmdNext_clicked();
    void on_cmdPrevious_clicked();
    void on_cmdClose_clicked();

private:
    Ui::frmHelp *ui;

    QHelpEngine *m_helpEngine;
    QPalette m_defaultPalette;

    void showSearchWidget(bool visible);
    QString prepareHelpFiles();
    void copyFile(const QString &from, const QString &to);
};