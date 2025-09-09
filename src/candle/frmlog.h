// This file is a part of "Candle" application.
// Copyright 2015-2025 Hayrullin Denis Ravilevich

#pragma once
#include <QDialog>

namespace Ui {
class frmLog;
}

class frmLog : public QDialog
{
    Q_OBJECT

public:
    explicit frmLog(QWidget *parent = 0);
    ~frmLog();

private:
    void loadLogFile();

private slots:
    void on_cmdOk_clicked();
    void onLogFileChanged(const QString &path);

private:
    Ui::frmLog *ui;

    QString m_logFileName;
};
