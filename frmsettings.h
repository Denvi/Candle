#ifndef FRMSETTINGS_H
#define FRMSETTINGS_H

#include <QDialog>

namespace Ui {
class frmSettings;
}

class frmSettings : public QDialog
{
    Q_OBJECT

public:
    explicit frmSettings(QWidget *parent = 0);
    ~frmSettings();

    QString port();
    void setPort(QString port);
    int baud();
    void setBaud(int baud);

private slots:
    void on_cmdRefresh_clicked();
    void on_cmdOK_clicked();
    void on_cmdCancel_clicked();

private:
    Ui::frmSettings *ui;
    searchPorts();
};

#endif // FRMSETTINGS_H
