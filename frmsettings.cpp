#include "frmsettings.h"
#include "ui_frmsettings.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

frmSettings::frmSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frmSettings)
{
    ui->setupUi(this);

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

frmSettings::searchPorts()
{
    ui->cboPort->clear();

    foreach (QSerialPortInfo info ,QSerialPortInfo::availablePorts()) {
        ui->cboPort->addItem(info.portName());
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
