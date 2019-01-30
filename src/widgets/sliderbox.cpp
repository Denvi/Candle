#include "sliderbox.h"
#include "ui_sliderbox.h"

SliderBox::SliderBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SliderBox)
{
    ui->setupUi(this);    

    ui->chkTitle->setVisible(false);

    this->setCheckable(true);
    this->setRatio(1);
    this->setMinimum(0);
    this->setMaximum(10000);
    this->setValue(0);
    this->setCurrentValue(0);

    connect(&m_timerValueChanged, SIGNAL(timeout()), this, SLOT(onTimerValueChanged()));
    m_timerValueChanged.setInterval(250);
}

SliderBox::~SliderBox()
{
    delete ui;
}

int SliderBox::value()
{
    return ui->txtValue->value();
}

void SliderBox::setValue(int value)
{
    ui->txtValue->setValue(value);
    ui->sliValue->setValue(value / m_ratio);
}

int SliderBox::currentValue()
{
    return m_currentValue;
}

void SliderBox::setCurrentValue(int value)
{
    m_currentValue = value;

    ui->sliValue->setCurrentValue(value / m_ratio);
    ui->txtValue->setStyleSheet(value == ui->txtValue->value() || !this->isChecked() ? "color: palette(text);" : "color: red;");
}

int SliderBox::sliderPosition()
{
    return ui->sliValue->sliderPosition();
}

void SliderBox::setSliderPosition(int position)
{
    ui->sliValue->setSliderPosition(position);
}

bool SliderBox::isCheckable() const
{
    return m_isCheckable;
}

void SliderBox::setCheckable(bool checkable)
{
    m_isCheckable = checkable;

    ui->chkTitle->setVisible(checkable);
    ui->lblTitle->setVisible(!checkable);
}

bool SliderBox::isChecked()
{
    return ui->chkTitle->isChecked();
}

void SliderBox::setChecked(bool checked)
{
    ui->chkTitle->setChecked(checked);
}

int SliderBox::ratio() const
{
    return m_ratio;
}

void SliderBox::setRatio(int ratio)
{
    m_ratio = ratio;
}

void SliderBox::on_txtValue_editingFinished()
{
    ui->sliValue->setValue(ui->txtValue->value() / this->ratio());
    emit valueUserChanged();
}

void SliderBox::on_sliValue_actionTriggered(int action)
{
    ui->txtValue->setValue(ui->sliValue->sliderPosition() * this->ratio());
    emit valueUserChanged();
}

void SliderBox::on_sliValue_valueChanged(int value)
{
    if (this->isChecked()) {
        ui->txtValue->setStyleSheet("color: red;");
        m_timerValueChanged.start();
    }
}

void SliderBox::onTimerValueChanged()
{
    m_timerValueChanged.stop();
    emit valueChanged();
}

int SliderBox::maximum() const
{
    return m_maximum;
}

void SliderBox::setMaximum(int maximum)
{
    m_maximum = maximum;

    ui->txtValue->setMaximum(maximum);
    ui->sliValue->setMaximum(maximum / m_ratio);
}

QString SliderBox::suffix()
{
    return ui->txtValue->suffix();
}

void SliderBox::setSuffix(QString suffix)
{
    ui->txtValue->setSuffix(suffix);
}

QString SliderBox::title()
{
    return ui->chkTitle->text();
}

void SliderBox::setTitle(QString title)
{
    ui->chkTitle->setText(title);
    ui->lblTitle->setText(title);
}

int SliderBox::minimum() const
{
    return m_minimum;
}

void SliderBox::setMinimum(int minimum)
{
    m_minimum = minimum;

    ui->txtValue->setMinimum(minimum);
    ui->sliValue->setMinimum(minimum / m_ratio);
}

void SliderBox::on_chkTitle_toggled(bool checked)
{
    emit toggled(checked);
}
