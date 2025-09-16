// This file is a part of "Candle" application.
// Copyright 2015-2025 Hayrullin Denis Ravilevich

#pragma once
#include <QFrame>

namespace Ui {
class frmLog;
}

class frmLog : public QFrame
{
    Q_OBJECT

public:
    explicit frmLog(QWidget *parent = 0);
    ~frmLog();

private:
    void loadLogFile();

private slots:
    void onLogFileChanged(const QString &path);

private:
    Ui::frmLog *ui;

    QString m_logFileName;
};
