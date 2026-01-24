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
#include <cmath>

class Util
{
public:
    enum RotationVector {
        RotationVectorX,
        RotationVectorY,
        RotationVectorZ,
        RotationVectorNone
    };

    static const QVector3D &rotationVector(RotationVector vector)
    {
        static QMap<RotationVector, QVector3D> vectors;
        if (vectors.isEmpty()) {
            vectors[RotationVectorX] = QVector3D(1.0, 0.0, 0.0);
            vectors[RotationVectorY] = QVector3D(0.0, 1.0, 0.0);
            vectors[RotationVectorZ] = QVector3D(0.0, 0.0, 1.0);
            vectors[RotationVectorNone] = nVector();
        }
        return vectors[vector];
    };

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

    static bool nIsNaN(const QVector3D &vector)
    {
        return qIsNaN(vector.x()) && qIsNaN(vector.y()) && qIsNaN(vector.z());
    }

    static bool nIsEqual(const QVector3D &v1, const QVector3D &v2)
    {
        return (v1.x() == v2.x() || qIsNaN(v1.x()) && qIsNaN(v2.x()))
            && (v1.y() == v2.y() || qIsNaN(v1.y()) && qIsNaN(v2.y()))
            && (v1.z() == v2.z() || qIsNaN(v1.z()) && qIsNaN(v2.z()));
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

        QTimer::singleShot(ms, &loop, &QEventLoop::quit);
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

    static double normalizeRotation(double value)
    {
        return value - std::trunc(value / 360.0) * 360.0;
    }
};

#endif // UTIL

