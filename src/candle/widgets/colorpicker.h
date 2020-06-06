#ifndef COLORPICKER_H
#define COLORPICKER_H

#include <QWidget>
#include <QHBoxLayout>
#include <QFrame>
#include <QToolButton>
#include <QColorDialog>

class ColorPicker : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int colorInt READ colorInt WRITE setColorInt);

public:
    explicit ColorPicker(QWidget *parent = 0);

    QColor color() const;
    void setColor(const QColor &color);

    int colorInt() const;
    void setColorInt(int color);

signals:
    void colorSelected(QColor color);

public slots:

private slots:
    void onButtonClicked();

private:
    QHBoxLayout *m_layout;
    QFrame *m_frame;
    QToolButton *m_button;
    QColor m_color;
};

#endif // COLORPICKER_H
