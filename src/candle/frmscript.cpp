// This file is a part of "Candle" application.
// Copyright 2015-2025 Hayrullin Denis Ravilevich

#include <QFileSystemWatcher>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include "frmscript.h"
#include "ui_frmscript.h"

frmScript::frmScript(QWidget *parent) : QFrame(parent), ui(new Ui::frmScript)
{
    ui->setupUi(this);

    m_changed = false;
    m_fileName = "";
}

frmScript::~frmScript()
{
    delete ui;
}

void frmScript::on_txtScript_textChanged()
{
    m_changed = true;
}

void frmScript::on_cmdNew_clicked()
{
    if (!saveChanges())
        return;

    ui->txtScript->clear();
    m_changed = false;
}

void frmScript::on_cmdOpen_clicked()
{
    if (!saveChanges())
        return;

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open"), QString(), tr("Script files (*.js)"));

    if (fileName != "")
    {
        QFile file(fileName);

        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::critical(this, this->windowTitle(), tr("Can't open file:\n") + fileName);
            return;
        }

        QTextStream textStream(&file);
        ui->txtScript->setPlainText(textStream.readAll());
        m_changed = false;
    }
}

void frmScript::on_cmdSave_clicked()
{
    saveFile();
}

void frmScript::on_cmdStart_clicked()
{
    emit ScriptStartClicked(ui->txtScript->toPlainText());
}

bool frmScript::saveChanges()
{
    if (m_changed)
    {
        int res = QMessageBox::warning(this, this->windowTitle(), tr("Script was changed. Save?"),
                                       QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

        if (res == QMessageBox::Cancel)
            return false;

        if (res == QMessageBox::No)
            return true;

        else if (res == QMessageBox::Yes && saveFile())
            return true;

        return false;
    }

    return true;
}

bool frmScript::saveFile()
{
    QString fileName = (QFileDialog::getSaveFileName(this, tr("Save file as"), m_lastFolder, tr("Script files (*.js)")));

    if (!fileName.isEmpty())
    {
        QFile file(fileName);
        QDir dir;

        if (file.exists())
            dir.remove(file.fileName());
        if (!file.open(QIODevice::WriteOnly))
            return false;

        QTextStream textStream(&file);
        textStream << ui->txtScript->toPlainText();

        file.close();

        m_fileName = fileName;
        m_changed = false;
        return true;
    }

    return false;
}