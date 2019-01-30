// This file is a part of "Candle" application.
// Copyright 2015-2016 Hayrullin Denis Ravilevich

#ifndef FRMSETTINGS_H
#define FRMSETTINGS_H

#include <QDialog>
#include <QMessageBox>
#include <QListWidgetItem>
#include "widgets/colorpicker.h"

namespace Ui {
class frmSettings;
}

class frmSettings : public QDialog
{
    Q_OBJECT

public:
    explicit frmSettings(QWidget *parent = 0);
    ~frmSettings();

    int exec();
    void undo();

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
    double arcLength();
    void setArcLength(double arcLength);
    double arcDegree();
    void setArcDegree(double arcDegree);
    double arcPrecision();
    bool arcDegreeMode();
    void setArcDegreeMode(bool arcDegreeMode);
    bool showProgramCommands();
    void setShowProgramCommands(bool showProgramCommands);
    bool showUICommands();
    void setShowUICommands(bool showUICommands);
    QString safePositionCommand();
    void setSafePositionCommand(QString command);
    bool moveOnRestore();
    void setMoveOnRestore(bool value);
    int restoreMode();
    void setRestoreMode(int value);
    int spindleSpeedMin();
    void setSpindleSpeedMin(int speed);
    int spindleSpeedMax();
    void setSpindleSpeedMax(int speed);
    int laserPowerMin();
    void setLaserPowerMin(int value);
    int laserPowerMax();
    void setLaserPowerMax(int value);
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
    bool vsync();
    void setVsync(bool value);
    bool msaa();
    void setMsaa(bool msaa);
    bool autoCompletion();
    void setAutoCompletion(bool autoCompletion);
    int units();
    void setUnits(int units);
    QString touchCommand();
    void setTouchCommand(QString touchCommand);
    bool simplify();
    void setSimplify(bool simplify);
    double simplifyPrecision();
    void setSimplifyPrecision(double simplifyPrecision);
    bool panelUserCommands();
    void setPanelUserCommands(bool value);
    bool panelHeightmap();
    void setPanelHeightmap(bool panelHeightmap);
    bool panelSpindle();
    void setPanelSpindle(bool panelSpindle);
    bool panelOverriding();
    void setPanelOverriding(bool panelFeed);
    bool panelJog();
    void setPanelJog(bool panelJog);
    QList<ColorPicker*> colors();
    QColor colors(QString name);
    int fontSize();
    void setFontSize(int fontSize);
    bool grayscaleSegments();
    void setGrayscaleSegments(bool value);
    bool grayscaleSCode();
    void setGrayscaleSCode(bool value);
    bool drawModeVectors();
    void setDrawModeVectors(bool value);
    QString userCommands(int index);
    void setUserCommands(int index, QString commands);
    bool ignoreErrors();
    void setIgnoreErrors(bool value);
    bool autoLine();
    void setAutoLine(bool value);

protected:
    void showEvent(QShowEvent *se);

private slots:
    void onScrollBarValueChanged(int value);

    void on_cmdRefresh_clicked();
    void on_cmdOK_clicked();
    void on_cmdCancel_clicked();
    void on_cboToolType_currentIndexChanged(int index);
    void on_listCategories_currentRowChanged(int currentRow);

    void on_cmdDefaults_clicked();

    void on_cboFontSize_currentTextChanged(const QString &arg1);

    void on_radDrawModeVectors_toggled(bool checked);

    void on_radDrawModeRaster_toggled(bool checked);

    void on_radGrayscaleS_toggled(bool checked);

    void on_radGrayscaleZ_toggled(bool checked);

private:
    Ui::frmSettings *ui;
    void searchPorts();

    QList<double> m_storedValues;
    QList<bool> m_storedChecks;
    QList<QString> m_storedCombos;
    QList<QColor> m_storedColors;

    QIntValidator m_intValidator;
};

#endif // FRMSETTINGS_H
