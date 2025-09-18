// This file is a part of "Candle" application.
// Copyright 2015-2025 Hayrullin Denis Ravilevich

#pragma once
#include <QFrame>

namespace Ui {
class frmScript;
}

class frmScript : public QFrame
{
    Q_OBJECT

public:
    explicit frmScript(QWidget *parent = 0);
    ~frmScript();

signals:
    void ScriptStartClicked(const QString& script);

private slots:
    void on_cmdNew_clicked();
    void on_cmdOpen_clicked();
    void on_cmdSave_clicked();
    void on_cmdStart_clicked();
    void on_txtScript_textChanged();

private:
    Ui::frmScript *ui;

    bool m_changed;
    QString m_fileName;
    QString m_lastFolder;

    bool saveChanges();
    bool saveFile();
};
