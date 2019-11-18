#ifndef SLIDERBOX_H
#define SLIDERBOX_H

#include <QWidget>
#include <QTimer>

namespace Ui {
class SliderBox;
}

class SliderBox : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int value READ value WRITE setValue)
    Q_PROPERTY(int currentValue READ currentValue WRITE setCurrentValue)
    Q_PROPERTY(int sliderPosition READ sliderPosition WRITE setSliderPosition)
    Q_PROPERTY(bool isCheckable READ isCheckable WRITE setCheckable)
    Q_PROPERTY(bool isChecked READ isChecked WRITE setChecked)
    Q_PROPERTY(int ratio READ ratio WRITE setRatio)
    Q_PROPERTY(int minimum READ minimum WRITE setMinimum)
    Q_PROPERTY(int maximum READ maximum WRITE setMaximum)
    Q_PROPERTY(QString suffix READ suffix WRITE setSuffix)
    Q_PROPERTY(QString title READ title WRITE setTitle)
    
public:
    explicit SliderBox(QWidget *parent = 0);
    ~SliderBox();

    int value();
    void setValue(int value);

    int currentValue();
    void setCurrentValue(int value);

    int sliderPosition();
    void setSliderPosition(int position);

    bool isCheckable() const;
    void setCheckable(bool checkable);

    bool isChecked();
    void setChecked(bool checked);

    int ratio() const;
    void setRatio(int ratio);

    int minimum() const;
    void setMinimum(int minimum);

    int maximum() const;
    void setMaximum(int maximum);

    QString suffix();
    void setSuffix(QString suffix);

    QString title();
    void setTitle(QString title);

signals:
    void valueUserChanged();
    void valueChanged();
    void toggled(bool checked);

public slots:
    void click();    

private slots:
    void onTimerValueChanged();
    void on_txtValue_editingFinished();
    void on_sliValue_actionTriggered(int action);
    void on_sliValue_valueChanged(int value);
    void on_chkTitle_toggled(bool checked);

private:
    Ui::SliderBox *ui;

    bool m_isCheckable;
    int m_ratio;

    int m_currentValue;
    int m_minimum, m_maximum;

    QTimer m_timerValueChanged;
};

#endif // SLIDERBOX_H
