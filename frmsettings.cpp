// This file is a part of "grblControl" application.
// Copyright 2015 Hayrullin Denis Ravilevich

#include "frmsettings.h"
#include "ui_frmsettings.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>

frmSettings::frmSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frmSettings)
{
    ui->setupUi(this);

//    foreach (QAbstractSpinBox* sb, this->findChildren<QAbstractSpinBox*>())
//    {
//        sb->setLocale(QLocale::C);
//    }

    this->setLocale(QLocale::C);

    searchPorts();
}

frmSettings::~frmSettings()
{
    delete ui;
}

QString frmSettings::port()
{
    return ui->cboPort->currentText();
}

void frmSettings::setPort(QString port)
{
    ui->cboPort->setCurrentText(port);
}

int frmSettings::baud()
{
    return ui->cboBaud->currentText().toInt();
}

void frmSettings::setBaud(int baud)
{
    ui->cboBaud->setCurrentText(QString::number(baud));
}

double frmSettings::toolDiameter()
{
    return ui->txtToolDiameter->value();
}

void frmSettings::setToolDiameter(double diameter)
{
    ui->txtToolDiameter->setValue(diameter);
}

double frmSettings::toolLength()
{
    return ui->txtToolLength->value();
}

void frmSettings::setToolLength(double length)
{
    ui->txtToolLength->setValue(length);
}

bool frmSettings::antialiasing()
{
    return ui->chkAntialiasing->isChecked();
}

void frmSettings::setAntialiasing(bool antialiasing)
{
    ui->chkAntialiasing->setChecked(antialiasing);
}

bool frmSettings::zBuffer()
{
    return ui->chkZBuffer->isChecked();
}

void frmSettings::setZBuffer(bool zBuffer)
{
    ui->chkZBuffer->setChecked(zBuffer);
}

double frmSettings::lineWidth()
{
    return ui->txtLineWidth->value();
}

void frmSettings::setLineWidth(double lineWidth)
{
    ui->txtLineWidth->setValue(lineWidth);
}

double frmSettings::arcPrecision()
{
    return ui->txtArcPrecision->value();
}

void frmSettings::setArcPrecision(double arcPrecision)
{
    ui->txtArcPrecision->setValue(arcPrecision);
}

bool frmSettings::showAllCommands()
{
    return ui->chkShowAllCommands->isChecked();
}

void frmSettings::setShowAllCommands(bool showAllCommands)
{
    ui->chkShowAllCommands->setChecked(showAllCommands);
}

double frmSettings::safeZ()
{
    return ui->txtSafeZ->value();
}

void frmSettings::setSafeZ(double safeZ)
{
    ui->txtSafeZ->setValue(safeZ);
}

int frmSettings::spindleSpeedMin()
{
    return ui->txtSpindleSpeedMin->value();
}

void frmSettings::setSpindleSpeedMin(int speed)
{
    ui->txtSpindleSpeedMin->setValue(speed);
}

int frmSettings::spindleSpeedMax()
{
    return ui->txtSpindleSpeedMax->value();
}

void frmSettings::setSpindleSpeedMax(int speed)
{
    ui->txtSpindleSpeedMax->setValue(speed);
}

int frmSettings::rapidSpeed()
{
    return ui->txtRapidSpeed->value();
}

void frmSettings::setRapidSpeed(int rapidSpeed)
{
    ui->txtRapidSpeed->setValue(rapidSpeed);
}

int frmSettings::heightmapProbingFeed()
{
    return ui->txtHeightMapProbingFeed->value();
}

void frmSettings::setHeightmapProbingFeed(int heightmapProbingFeed)
{
    ui->txtHeightMapProbingFeed->setValue(heightmapProbingFeed);
}

int frmSettings::acceleration()
{
    return ui->txtAcceleration->value();
}

void frmSettings::setAcceleration(int acceleration)
{
    ui->txtAcceleration->setValue(acceleration);
}

int frmSettings::queryStateTime()
{
    return ui->txtQueryStateTime->value();
}

void frmSettings::setQueryStateTime(int queryStateTime)
{
    ui->txtQueryStateTime->setValue(queryStateTime);
}

int frmSettings::toolType()
{
    return ui->cboToolType->currentIndex();
}

void frmSettings::setToolType(int toolType)
{
    ui->cboToolType->setCurrentIndex(toolType);
}

double frmSettings::toolAngle()
{
    return ui->txtToolAngle->value();
}

void frmSettings::setToolAngle(double toolAngle)
{
    ui->txtToolAngle->setValue(toolAngle);
}

int frmSettings::fps()
{
    return ui->cboFps->currentText().toInt();
}

void frmSettings::setFps(int fps)
{
    ui->cboFps->setCurrentText(QString::number(fps));
}

bool frmSettings::msaa()
{
    return ui->radMSAA->isChecked();
}

void frmSettings::setMsaa(bool msaa)
{
    ui->radMSAA->setChecked(msaa);
}

bool frmSettings::autoCompletion()
{
    return ui->chkAutocompletion->isChecked();
}

void frmSettings::setAutoCompletion(bool autoCompletion)
{
    ui->chkAutocompletion->setChecked(autoCompletion);
}

int frmSettings::units()
{
    return ui->cboUnits->currentIndex();
}

void frmSettings::setUnits(int units)
{
    ui->cboUnits->setCurrentIndex(units);
}

QString frmSettings::touchCommand()
{
    return ui->txtTouchCommand->text();
}

void frmSettings::setTouchCommand(QString touchCommand)
{
    ui->txtTouchCommand->setText(touchCommand);
}

bool frmSettings::simplify()
{
    return ui->chkSimplify->isChecked();
}

void frmSettings::setSimplify(bool simplify)
{
    ui->chkSimplify->setChecked(simplify);
}

double frmSettings::simplifyPrecision()
{
    return ui->txtSimplifyPrecision->value();
}

void frmSettings::setSimplifyPrecision(double simplifyPrecision)
{
    ui->txtSimplifyPrecision->setValue(simplifyPrecision);
}

void frmSettings::searchPorts()
{
    ui->cboPort->clear();

    foreach (QSerialPortInfo info ,QSerialPortInfo::availablePorts()) {
//        ui->cboPort->addItem(info.portName());
        ui->cboPort->insertItem(0, info.portName());
    }    
}

void frmSettings::on_cmdRefresh_clicked()
{
    searchPorts();
}

void frmSettings::on_cmdOK_clicked()
{
    this->accept();
}

void frmSettings::on_cmdCancel_clicked()
{
    this->reject();
}

void frmSettings::on_cboToolType_currentIndexChanged(int index)
{
    ui->lblToolAngle->setEnabled(index == 1);
    ui->txtToolAngle->setEnabled(index == 1);
}
