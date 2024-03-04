#include "jog.h"
#include "ui_jog.h"

Jog::Jog(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Jog)
{
    ui->setupUi(this);
}

Jog::~Jog()
{
    delete ui;
}
