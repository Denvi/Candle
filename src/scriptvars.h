#ifndef SCRIPTVARS_H
#define SCRIPTVARS_H

#include <QObject>

class ScriptVars: public QObject
{
    Q_OBJECT
    Q_PROPERTY(double Mx READ Mx WRITE setMx)
    Q_PROPERTY(double My READ My WRITE setMy)
    Q_PROPERTY(double Mz READ Mz WRITE setMz)
    
    Q_PROPERTY(double Wx READ Wx WRITE setWx)
    Q_PROPERTY(double Wy READ Wy WRITE setWy)
    Q_PROPERTY(double Wz READ Wz WRITE setWz)
    
    Q_PROPERTY(double G54x READ G54x WRITE setG54x)
    Q_PROPERTY(double G54y READ G54y WRITE setG54y)
    Q_PROPERTY(double G54z READ G54z WRITE setG54z)
    
    Q_PROPERTY(double G55x READ G55x WRITE setG55x)
    Q_PROPERTY(double G55y READ G55y WRITE setG55y)
    Q_PROPERTY(double G55z READ G55z WRITE setG55z)
    
    Q_PROPERTY(double G56x READ G56x WRITE setG56x)
    Q_PROPERTY(double G56y READ G56y WRITE setG56y)
    Q_PROPERTY(double G56z READ G56z WRITE setG56z)
    
    Q_PROPERTY(double G57x READ G57x WRITE setG57x)
    Q_PROPERTY(double G57y READ G57y WRITE setG57y)
    Q_PROPERTY(double G57z READ G57z WRITE setG57z)
    
    Q_PROPERTY(double G58x READ G58x WRITE setG58x)
    Q_PROPERTY(double G58y READ G58y WRITE setG58y)
    Q_PROPERTY(double G58z READ G58z WRITE setG58z)
    
    Q_PROPERTY(double G59x READ G59x WRITE setG59x)
    Q_PROPERTY(double G59y READ G59y WRITE setG59y)
    Q_PROPERTY(double G59z READ G59z WRITE setG59z)
    
    Q_PROPERTY(double G28x READ G28x WRITE setG28x)
    Q_PROPERTY(double G28y READ G28y WRITE setG28y)
    Q_PROPERTY(double G28z READ G28z WRITE setG28z)
    
    Q_PROPERTY(double G30x READ G30x WRITE setG30x)
    Q_PROPERTY(double G30y READ G30y WRITE setG30y)
    Q_PROPERTY(double G30z READ G30z WRITE setG30z)
    
    Q_PROPERTY(double G92x READ G92x WRITE setG92x)
    Q_PROPERTY(double G92y READ G92y WRITE setG92y)
    Q_PROPERTY(double G92z READ G92z WRITE setG92z)
    
    Q_PROPERTY(double TLOx READ TLOx WRITE setTLOx)
    Q_PROPERTY(double TLOy READ TLOy WRITE setTLOy)
    Q_PROPERTY(double TLOz READ TLOz WRITE setTLOz)
    
    Q_PROPERTY(double PRBx READ PRBx WRITE setPRBx)
    Q_PROPERTY(double PRBy READ PRBy WRITE setPRBy)
    Q_PROPERTY(double PRBz READ PRBz WRITE setPRBz)

public:
    ScriptVars();

    void setMx(double value);
    double Mx() const;
    void setMy(double value);
    double My() const;
    void setMz(double value);
    double Mz() const;

    void setWx(double value);
    double Wx() const;
    void setWy(double value);
    double Wy() const;
    void setWz(double value);
    double Wz() const;

    void setG54x(double value);
    double G54x() const;
    void setG54y(double value);
    double G54y() const;
    void setG54z(double value);
    double G54z() const;

    void setG55x(double value);
    double G55x() const;
    void setG55y(double value);
    double G55y() const;
    void setG55z(double value);
    double G55z() const;

    void setG56x(double value);
    double G56x() const;
    void setG56y(double value);
    double G56y() const;
    void setG56z(double value);
    double G56z() const;

    void setG57x(double value);
    double G57x() const;
    void setG57y(double value);
    double G57y() const;
    void setG57z(double value);
    double G57z() const;

    void setG58x(double value);
    double G58x() const;
    void setG58y(double value);
    double G58y() const;
    void setG58z(double value);
    double G58z() const;

    void setG59x(double value);
    double G59x() const;
    void setG59y(double value);
    double G59y() const;
    void setG59z(double value);
    double G59z() const;

    void setG28x(double value);
    double G28x() const;
    void setG28y(double value);
    double G28y() const;
    void setG28z(double value);
    double G28z() const;

    void setG30x(double value);
    double G30x() const;
    void setG30y(double value);
    double G30y() const;
    void setG30z(double value);
    double G30z() const;

    void setG92x(double value);
    double G92x() const;
    void setG92y(double value);
    double G92y() const;
    void setG92z(double value);
    double G92z() const;

    void setTLOx(double value);
    double TLOx() const;
    void setTLOy(double value);
    double TLOy() const;
    void setTLOz(double value);
    double TLOz() const;

    void setPRBx(double value);
    double PRBx() const;
    void setPRBy(double value);
    double PRBy() const;
    void setPRBz(double value);
    double PRBz() const;

private:
    double m_Mx;
    double m_My;
    double m_Mz;

    double m_Wx;
    double m_Wy;
    double m_Wz;

    double m_G54x;
    double m_G54y;
    double m_G54z;

    double m_G55x;
    double m_G55y;
    double m_G55z;

    double m_G56x;
    double m_G56y;
    double m_G56z;

    double m_G57x;
    double m_G57y;
    double m_G57z;

    double m_G58x;
    double m_G58y;
    double m_G58z;

    double m_G59x;
    double m_G59y;
    double m_G59z;

    double m_G28x;
    double m_G28y;
    double m_G28z;

    double m_G30x;
    double m_G30y;
    double m_G30z;

    double m_G92x;
    double m_G92y;
    double m_G92z;

    double m_TLOx;
    double m_TLOy;
    double m_TLOz;

    double m_PRBx;
    double m_PRBy;
    double m_PRBz;
};

#endif  