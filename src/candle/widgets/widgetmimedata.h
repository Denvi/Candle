#ifndef WIDGETMIMEDATA_H
#define WIDGETMIMEDATA_H

#include <QMimeData>
#include <QWidget>

class WidgetMimeData: public QMimeData
{
public:
    WidgetMimeData(): QMimeData()
    {
    }

    static QString mimeType()
    {
        return "application/widget";
    }

    void setWidget(QWidget *widget)
    {
        setData(WidgetMimeData::mimeType(), QByteArray());
        m_widget = widget;
    }

    QWidget *widget() const
    {
        return m_widget;
    }

private:
    QWidget* m_widget;
};

#endif