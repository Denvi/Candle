#include "colorpicker.h"

ColorPicker::ColorPicker(QWidget *parent) :
    QWidget(parent)
{
    m_layout = new QHBoxLayout(this);
    m_frame = new QFrame(this);
    m_button = new QToolButton(this);

    m_frame->setFrameShape(QFrame::Box);

    m_button->setText("...");

    m_layout->setMargin(0);
    m_layout->addWidget(m_frame, 1);
    m_layout->addWidget(m_button);

    connect(m_button, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
}

QColor ColorPicker::color() const
{
    return m_color;
}

void ColorPicker::setColor(const QColor &color)
{
    m_color = color;
    m_frame->setStyleSheet(QString("background-color: %1").arg(color.name()));
}

void ColorPicker::onButtonClicked()
{
    QColor color = QColorDialog::getColor(m_color, this);

    if (color.isValid()) {
        setColor(color);
        emit colorSelected(color);
    }
}

