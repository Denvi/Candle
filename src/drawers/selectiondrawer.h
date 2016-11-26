#ifndef SELECTIONDRAWER_H
#define SELECTIONDRAWER_H

#include "shaderdrawable.h"

class SelectionDrawer : public ShaderDrawable
{        
public:
    SelectionDrawer();

    QVector3D startPosition() const;
    void setStartPosition(const QVector3D &startPosition);

    QColor color() const;
    void setColor(const QColor &color);

    QVector3D endPosition() const;
    void setEndPosition(const QVector3D &endPosition);

protected:
    bool  updateData();

private:
    QVector3D m_startPosition;
    QVector3D m_endPosition;

    QColor m_color;
};

#endif // SELECTIONDRAWER_H
