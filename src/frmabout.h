// This file is a part of "Candle" application.
// Copyright 2015-2016 Hayrullin Denis Ravilevich

#ifndef FRMABOUT_H
#define FRMABOUT_H

#include <QDialog>

namespace Ui {
class frmAbout;
}

class frmAbout : public QDialog
{
    Q_OBJECT

public:
    explicit frmAbout(QWidget *parent = 0);
    ~frmAbout();

private slots:
    void on_cmdOk_clicked();

    void on_lblAbout_linkActivated(const QString &link);

private:
    Ui::frmAbout *ui;
};

#endif // FRMABOUT_H
