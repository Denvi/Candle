// This file is a part of "Candle" application.
// Copyright 2015-2016 Hayrullin Denis Ravilevich

#ifndef FRMSETTINGS_H
#define FRMSETTINGS_H

#include <QDialog>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QSettings>
#include "widgets/colorpicker.h"

namespace Ui {
class frmSettings;
}

class GroupBox;

class frmSettings : public QDialog
{
    Q_OBJECT
    Q_PROPERTY(QString port READ port WRITE setPort)
    Q_PROPERTY(int baud READ baud WRITE setBaud)
    Q_PROPERTY(double toolDiameter READ toolDiameter WRITE setToolDiameter)
    Q_PROPERTY(double toolLength READ toolLength WRITE setToolLength)
    Q_PROPERTY(bool antialiasing READ antialiasing WRITE setAntialiasing)
    Q_PROPERTY(bool zBuffer READ zBuffer WRITE setZBuffer)
    Q_PROPERTY(double lineWidth READ lineWidth WRITE setLineWidth)
    Q_PROPERTY(double arcLength READ arcLength WRITE setArcLength)
    Q_PROPERTY(double arcDegree READ arcDegree WRITE setArcDegree)
    Q_PROPERTY(bool arcDegreeMode READ arcDegreeMode WRITE setArcDegreeMode)
    Q_PROPERTY(bool showProgramCommands READ showProgramCommands WRITE setShowProgramCommands)
    Q_PROPERTY(bool showUICommands READ showUICommands WRITE setShowUICommands)
    Q_PROPERTY(QString safePositionCommand READ safePositionCommand WRITE setSafePositionCommand)
    Q_PROPERTY(bool moveOnRestore READ moveOnRestore WRITE setMoveOnRestore)
    Q_PROPERTY(int restoreMode READ restoreMode WRITE setRestoreMode)
    Q_PROPERTY(int spindleSpeedMin READ spindleSpeedMin WRITE setSpindleSpeedMin)
    Q_PROPERTY(int spindleSpeedMax READ spindleSpeedMax WRITE setSpindleSpeedMax)
    Q_PROPERTY(int laserPowerMin READ laserPowerMin WRITE setLaserPowerMin)
    Q_PROPERTY(int laserPowerMax READ laserPowerMax WRITE setLaserPowerMax)
    Q_PROPERTY(int rapidSpeed READ rapidSpeed WRITE setRapidSpeed)
    Q_PROPERTY(int heightmapProbingFeed READ heightmapProbingFeed WRITE setHeightmapProbingFeed)
    Q_PROPERTY(int acceleration READ acceleration WRITE setAcceleration)
    Q_PROPERTY(int queryStateTime READ queryStateTime WRITE setQueryStateTime)
    Q_PROPERTY(int toolType READ toolType WRITE setToolType)
    Q_PROPERTY(double toolAngle READ toolAngle WRITE setToolAngle)
    Q_PROPERTY(int fps READ fps WRITE setFps)
    Q_PROPERTY(bool vsync READ vsync WRITE setVsync)
    Q_PROPERTY(bool msaa READ msaa WRITE setMsaa)
    Q_PROPERTY(bool autoCompletion READ autoCompletion WRITE setAutoCompletion)
    Q_PROPERTY(bool units READ units WRITE setUnits)
    Q_PROPERTY(QString touchCommand READ touchCommand WRITE setTouchCommand)
    Q_PROPERTY(bool simplify READ simplify WRITE setSimplify)
    Q_PROPERTY(double simplifyPrecision READ simplifyPrecision WRITE setSimplifyPrecision)
    Q_PROPERTY(int fontSize READ fontSize WRITE setFontSize)
    Q_PROPERTY(bool grayscaleSegments READ grayscaleSegments WRITE setGrayscaleSegments)
    Q_PROPERTY(bool grayscaleSCode READ grayscaleSCode WRITE setGrayscaleSCode)
    Q_PROPERTY(bool drawModeVectors READ drawModeVectors WRITE setDrawModeVectors)
    Q_PROPERTY(bool ignoreErrors READ ignoreErrors WRITE setIgnoreErrors)
    Q_PROPERTY(bool autoLine READ autoLine WRITE setAutoLine)

public:
    explicit frmSettings(QWidget *parent = 0);
    ~frmSettings();

    Ui::frmSettings *ui;

    int exec();
    void undo();

    void addCustomSettings(GroupBox *box);
    void saveCustomSettings(QSettings &set);
    void loadCustomSettings(QSettings &set);

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
    // Ui::frmSettings *ui;
    void searchPorts();

    QList<double> m_storedValues;
    QList<bool> m_storedChecks;
    QList<QString> m_storedCombos;
    QList<QColor> m_storedColors;
    QList<QString> m_storedTextBoxes;
    QList<QString> m_storedPlainTexts;

    QIntValidator m_intValidator;

    QList<QWidget*> m_customSettings;

    int m_units;
    int m_acceleration;
    int m_rapidSpeed;
};

#endif // FRMSETTINGS_H
