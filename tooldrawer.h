#ifndef TOOLDRAWER_H
#define TOOLDRAWER_H

#include <QVector3D>
#include <QTimer>
#include "gldrawable.h"

class ToolDrawer : public GLDrawable
{
    Q_OBJECT
public:
    explicit ToolDrawer(QObject *parent = 0);
    void draw();
    QVector3D getSizes();
    QVector3D getMinimumExtremes();
    QVector3D getMaximumExtremes();

    double toolDiameter() const;
    void setToolDiameter(double toolDiameter);

    double toolLength() const;
    void setToolLength(double toolLength);

    QVector3D toolPosition() const;
    void setToolPosition(const QVector3D &toolPosition);

    double rotationAngle() const;
    void setRotationAngle(double rotationAngle);
<<<<<<< HEAD
    void rotate(double angle);
=======
>>>>>>> origin/master

signals:

public slots:

private:
    double m_toolDiameter;
    double m_toolLength;
    QVector3D m_toolPosition;
    double m_rotationAngle;
<<<<<<< HEAD

    double normalizeAngle(double angle);
=======
>>>>>>> origin/master
};

#endif // TOOLDRAWER_H
