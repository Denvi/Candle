// This file is a part of "Candle" application.
// Copyright 2015-2025 Hayrullin Denis Ravilevich

#ifndef UTIL
#define UTIL

#include <QColor>
#include <QIcon>
#include <QImage>
#include <QAbstractButton>
#include <QVector3D>
#include <QEventLoop>
#include <QTimer>

class Util
{
public:
    static double nMin(double v1, double v2)
    {
        if (!qIsNaN(v1) && !qIsNaN(v2)) return qMin<double>(v1, v2);
        else if (!qIsNaN(v1)) return v1;
        else if (!qIsNaN(v2)) return v2;
        else return qQNaN();
    }

    static double nMax(double v1, double v2)
    {
        if (!qIsNaN(v1) && !qIsNaN(v2)) return qMax<double>(v1, v2);
        else if (!qIsNaN(v1)) return v1;
        else if (!qIsNaN(v2)) return v2;
        else return qQNaN();
    }

    static QVector3D nMin(const QVector3D &v1, const QVector3D &v2)
    {
        return QVector3D(nMin(v1.x(), v2.x()), nMin(v1.y(), v2.y()), nMin(v1.z(), v2.z()));
    }
    
    static QVector3D nMax(const QVector3D &v1, const QVector3D &v2)
    {
        return QVector3D(nMax(v1.x(), v2.x()), nMax(v1.y(), v2.y()), nMax(v1.z(), v2.z()));
    }

    static double nAssign(double newValue, double defaultValue = 0.0)
    {
        return qIsNaN(newValue) ? defaultValue : newValue;
    }

    static QVector3D nAssign(const QVector3D &newVector, const QVector3D &defaultVector = QVector3D())
    {
        return QVector3D(
                qIsNaN(newVector.x()) ? defaultVector.x() : newVector.x(),
                qIsNaN(newVector.y()) ? defaultVector.y() : newVector.y(),
                qIsNaN(newVector.z()) ? defaultVector.z() : newVector.z()
        );
    }

    static QVector3D nVector()
    {
        return QVector3D(qQNaN(), qQNaN(), qQNaN());
    }

    static QVector3D colorToVector(QColor color)
    {
        return QVector3D(color.redF(), color.greenF(), color.blueF());
    }

    static void waitEvents(int ms)
    {
        QEventLoop loop;

        QTimer::singleShot(ms, &loop, SLOT(quit()));
        loop.exec();
    }

    static QIcon invertIconColors(QIcon icon)
    {
        QImage img = icon.pixmap(icon.actualSize(QSize(64, 64))).toImage();
        img.invertPixels();

        return QIcon(QPixmap::fromImage(img));
    }

    static void invertButtonIconColors(QAbstractButton *button)
    {
        button->setIcon(invertIconColors(button->icon()));
    }
};

#endif // UTIL

