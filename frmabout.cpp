#include <QDesktopServices>
#include "frmabout.h"
#include "ui_frmabout.h"

frmAbout::frmAbout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frmAbout)
{
    ui->setupUi(this);

    QFile file(qApp->applicationDirPath() + "/LICENSE");

    if (file.open(QIODevice::ReadOnly)) {
        ui->txtLicense->setPlainText(file.readAll());
    }
}

frmAbout::~frmAbout()
{
    delete ui;
}

void frmAbout::on_cmdOk_clicked()
{
    this->hide();
}

void frmAbout::on_label_linkActivated(const QString &link)
{
    QDesktopServices::openUrl(link);
}
