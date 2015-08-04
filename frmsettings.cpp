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

    QDoubleValidator *validator = new QDoubleValidator(0.1, 100, 3, this);
    validator->setLocale(QLocale::C);
    ui->txtToolDiameter->setValidator(validator);
    ui->txtToolLength->setValidator(validator);

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
//    return QLocale::system().toDouble(ui->txtToolDiameter->text());
    return ui->txtToolDiameter->text().toDouble();
}

void frmSettings::setToolDiameter(double diameter)
{
//    ui->txtToolDiameter->setText(QLocale::system().toString(diameter));
    ui->txtToolDiameter->setText(QString::number(diameter));
}

double frmSettings::toolLength()
{
    return ui->txtToolLength->text().toDouble();
}

void frmSettings::setToolLength(double length)
{
    ui->txtToolLength->setText(QString::number(length));
}

bool frmSettings::antialiasing()
{
    return ui->chkAntialiasing->isChecked();
}

void frmSettings::setAntialiasing(bool antialiasing)
{
    ui->chkAntialiasing->setChecked(antialiasing);
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
