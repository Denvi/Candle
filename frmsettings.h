// This file is a part of "grblControl" application.
// Copyright 2015 Hayrullin Denis Ravilevich

#ifndef FRMSETTINGS_H
#define FRMSETTINGS_H

#include <QDialog>

namespace Ui {
class frmSettings;
}

class frmSettings : public QDialog
{
    Q_OBJECT

public:
    explicit frmSettings(QWidget *parent = 0);
    ~frmSettings();

    QString port();
    void setPort(QString port);
    int baud();
    void setBaud(int baud);
    double toolDiameter();
    void setToolDiameter(double diameter);
    double toolLength();
    void setToolLength(double length);
    bool antialiasing();
    void setAntialiasing(bool antialiasing);
    bool zBuffer();
    void setZBuffer(bool zBuffer);
    double lineWidth();
    void setLineWidth(double lineWidth);
    double arcPrecision();
    void setArcPrecision(double arcPrecision);
    bool showAllCommands();
    void setShowAllCommands(bool showAllCommands);
    double safeZ();
    void setSafeZ(double safeZ);
    int spindleSpeedMin();
    void setSpindleSpeedMin(int speed);
    int spindleSpeedMax();
    void setSpindleSpeedMax(int speed);
    int rapidSpeed();
    void setRapidSpeed(int rapidSpeed);
    int heightmapProbingFeed();
    void setHeightmapProbingFeed(int heightmapProbingFeed);
    int acceleration();
    void setAcceleration(int acceleration);
    int queryStateTime();
    void setQueryStateTime(int queryStateTime);
    int toolType();
    void setToolType(int toolType);
    double toolAngle();
    void setToolAngle(double toolAngle);
    int fps();
    void setFps(int fps);
    bool msaa();
    void setMsaa(bool msaa);
    bool autoCompletion();
    void setAutoCompletion(bool autoCompletion);
    int units();
    void setUnits(int units);
    QString touchCommand();
    void setTouchCommand(QString touchCommand);

private slots:
    void on_cmdRefresh_clicked();
    void on_cmdOK_clicked();
    void on_cmdCancel_clicked();

    void on_cboToolType_currentIndexChanged(int index);

private:
    Ui::frmSettings *ui;
    void searchPorts();
};

#endif // FRMSETTINGS_H
