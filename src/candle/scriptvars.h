#ifndef SCRIPTVARS_H
#define SCRIPTVARS_H

#include <QObject>
#include <QMap>
#include <QVector3D>

class ScriptVars: public QObject
{
    Q_OBJECT
    Q_PROPERTY(double Mx READ Mx)
    Q_PROPERTY(double My READ My)
    Q_PROPERTY(double Mz READ Mz)
    
    Q_PROPERTY(double Wx READ Wx)
    Q_PROPERTY(double Wy READ Wy)
    Q_PROPERTY(double Wz READ Wz)
    
    Q_PROPERTY(double G54x READ G54x)
    Q_PROPERTY(double G54y READ G54y)
    Q_PROPERTY(double G54z READ G54z)
    
    Q_PROPERTY(double G55x READ G55x)
    Q_PROPERTY(double G55y READ G55y)
    Q_PROPERTY(double G55z READ G55z)
    
    Q_PROPERTY(double G56x READ G56x)
    Q_PROPERTY(double G56y READ G56y)
    Q_PROPERTY(double G56z READ G56z)
    
    Q_PROPERTY(double G57x READ G57x)
    Q_PROPERTY(double G57y READ G57y)
    Q_PROPERTY(double G57z READ G57z)
    
    Q_PROPERTY(double G58x READ G58x)
    Q_PROPERTY(double G58y READ G58y)
    Q_PROPERTY(double G58z READ G58z)
    
    Q_PROPERTY(double G59x READ G59x)
    Q_PROPERTY(double G59y READ G59y)
    Q_PROPERTY(double G59z READ G59z)
    
    Q_PROPERTY(double G28x READ G28x)
    Q_PROPERTY(double G28y READ G28y)
    Q_PROPERTY(double G28z READ G28z)
    
    Q_PROPERTY(double G30x READ G30x)
    Q_PROPERTY(double G30y READ G30y)
    Q_PROPERTY(double G30z READ G30z)
    
    Q_PROPERTY(double G92x READ G92x)
    Q_PROPERTY(double G92y READ G92y)
    Q_PROPERTY(double G92z READ G92z)
    
    Q_PROPERTY(double TLOx READ TLOx)
    Q_PROPERTY(double TLOy READ TLOy)
    Q_PROPERTY(double TLOz READ TLOz)
    
    Q_PROPERTY(double PRBx READ PRBx)
    Q_PROPERTY(double PRBy READ PRBy)
    Q_PROPERTY(double PRBz READ PRBz)

    Q_PROPERTY(double x READ x)
    Q_PROPERTY(double y READ y)
    Q_PROPERTY(double z READ z)

    Q_PROPERTY(QString CS READ CS)

    Q_PROPERTY(int tool READ tool);

public:
    ScriptVars();

    double Mx() const;
    double My() const;
    double Mz() const;

    double Wx() const;
    double Wy() const;
    double Wz() const;

    double G54x() const;
    double G54y() const;
    double G54z() const;

    double G55x() const;
    double G55y() const;
    double G55z() const;

    double G56x() const;
    double G56y() const;
    double G56z() const;

    double G57x() const;
    double G57y() const;
    double G57z() const;

    double G58x() const;
    double G58y() const;
    double G58z() const;

    double G59x() const;
    double G59y() const;
    double G59z() const;

    double G28x() const;
    double G28y() const;
    double G28z() const;

    double G30x() const;
    double G30y() const;
    double G30z() const;

    double G92x() const;
    double G92y() const;
    double G92z() const;

    double TLOx() const;
    double TLOy() const;
    double TLOz() const;

    double PRBx() const;
    double PRBy() const;
    double PRBz() const;

    QVector3D coords(QString name) const;
    QString CS() const;

    int tool() const;

public slots:

    void setCoords(QString name, QVector3D coords);
    void setCS(QString cs);
    void setTool(int tool);

    double x() const;
    double y() const;
    double z() const;

    double x(QString name) const;
    double y(QString name) const;
    double z(QString name) const;

private:
    QMap<QString, QVector3D> m_coords;
    QString m_cs;
    int m_tool;
};

#endif  