// This file is a part of "Candle" application.
// Copyright 2015-2021 Hayrullin Denis Ravilevich

#include "frmsettings.h"
#include "ui_frmsettings.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include <QScrollBar>
#include <QColorDialog>
#include <QStyledItemDelegate>
#include <QKeySequenceEdit>
#include <QKeyEvent>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QDir>
#include <QLocale>

class CustomKeySequenceEdit : public QKeySequenceEdit
{
public:
    explicit CustomKeySequenceEdit(QWidget *parent = 0): QKeySequenceEdit(parent) {}
    ~CustomKeySequenceEdit() {}

protected:
    void keyPressEvent(QKeyEvent *pEvent) {
        QKeySequenceEdit::keyPressEvent(pEvent);
        QString s = keySequence().toString().split(", ").first();

        QString shiftedKeys = "~!@#$%^&*()_+{}|:?><\"";
        QString key = s.right(1);
        
        if (pEvent->modifiers() & Qt::KeypadModifier) s = "Num+" + s;
        else if (!key.isEmpty() && shiftedKeys.contains(key)) {
            s.remove("Shift+");
            s = s.left(s.size() - 1) + QString("Shift+%1").arg(key);
        }

        QKeySequence seq(QKeySequence::fromString(s));
        setKeySequence(seq);
    }
};

class ShortcutDelegate: public QStyledItemDelegate
{
public:
    ShortcutDelegate() {}

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override
    {
        return new CustomKeySequenceEdit(parent);
    }

    void setEditorData(QWidget *editor, const QModelIndex &index) const override
    {
        static_cast<QKeySequenceEdit*>(editor)->setKeySequence(index.data(Qt::DisplayRole).toString());
    }

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override
    {
        model->setData(index, static_cast<QKeySequenceEdit*>(editor)->keySequence().toString());
    }
};

frmSettings::frmSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frmSettings)
{
    ui->setupUi(this);

    this->setLocale(QLocale::C);
    m_intValidator.setBottom(1);
    m_intValidator.setTop(999);
    ui->cboFps->setValidator(&m_intValidator);
    ui->cboFontSize->setValidator(&m_intValidator);

    foreach (QGroupBox *box, this->findChildren<QGroupBox*>()) {
        ui->listCategories->addItem(box->title());
        ui->listCategories->item(ui->listCategories->count() - 1)->setData(Qt::UserRole, box->objectName());
    }

    ui->listCategories->item(0)->setSelected(true);
    connect(ui->scrollSettings->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(onScrollBarValueChanged(int)));
    connect(this, SIGNAL(settingsSetByDefault()), parent, SIGNAL(settingsSetByDefault()));

    // Shortcuts table
    ui->tblShortcuts->setItemDelegateForColumn(2, new ShortcutDelegate);
    ui->tblShortcuts->setTabKeyNavigation(false);
    ui->tblShortcuts->setEditTriggers(QAbstractItemView::AllEditTriggers);

    searchPorts();

    // Languages
    QDir d(qApp->applicationDirPath() + "/translations");
    QStringList fl = QStringList() << "candle_*.qm";
    QStringList tl = d.entryList(fl, QDir::Files);
    QRegExp fx("_([^\\.]+)");
    foreach (const QString &t, tl) {
        if (fx.indexIn(t) != -1) {
            QLocale l(fx.cap(1));
            ui->cboLanguage->addItem(l.nativeLanguageName(), l.name().left(2));
        }
    }
}

frmSettings::~frmSettings()
{
    delete ui;
}

int frmSettings::exec()
{
    // Store settings to undo
    m_storedValues.clear();
    m_storedChecks.clear();
    m_storedCombos.clear();
    m_storedColors.clear();
    m_storedTextBoxes.clear();
    m_storedPlainTexts.clear();

    foreach (QAbstractSpinBox* o, this->findChildren<QAbstractSpinBox*>())
        m_storedValues.append(o->property("value").toDouble());

    foreach (QAbstractButton* o, this->findChildren<QAbstractButton*>())
        m_storedChecks.append(o->isChecked());

    foreach (QComboBox* o, this->findChildren<QComboBox*>())
        m_storedCombos.append(o->currentText());

    foreach (ColorPicker* o, this->findChildren<ColorPicker*>())
        m_storedColors.append(o->color());

    foreach (QLineEdit* o, this->findChildren<QLineEdit*>())
        m_storedTextBoxes.append(o->text());

    foreach (QPlainTextEdit* o, this->findChildren<QPlainTextEdit*>())
        m_storedPlainTexts.append(o->toPlainText());

    return QDialog::exec();
}

void frmSettings::undo()
{
    foreach (QAbstractSpinBox* o, this->findChildren<QAbstractSpinBox*>())
        o->setProperty("value", m_storedValues.takeFirst());

    foreach (QAbstractButton* o, this->findChildren<QAbstractButton*>())
        o->setChecked(m_storedChecks.takeFirst());

    foreach (QComboBox* o, this->findChildren<QComboBox*>())
        o->setCurrentText(m_storedCombos.takeFirst());

    foreach (ColorPicker* o, this->findChildren<ColorPicker*>())
        o->setColor(m_storedColors.takeFirst());

    foreach (QLineEdit* o, this->findChildren<QLineEdit*>())
        o->setText(m_storedTextBoxes.takeFirst());

    foreach (QPlainTextEdit* o, this->findChildren<QPlainTextEdit*>())
        o->setPlainText(m_storedPlainTexts.takeFirst());
}

void frmSettings::addCustomSettings(QGroupBox *box)
{
    static_cast<QVBoxLayout*>(ui->scrollAreaWidgetContents->layout())->addWidget(box);
    
    ui->listCategories->addItem(box->title());
    ui->listCategories->item(ui->listCategories->count() - 1)->setData(Qt::UserRole, box->objectName());

    m_customSettings.append(box);
}

void frmSettings::on_listCategories_currentRowChanged(int currentRow)
{
    // Scroll to selected groupbox
    QGroupBox *box = this->findChild<QGroupBox*>(ui->listCategories->item(currentRow)->data(Qt::UserRole).toString());
    if (box) {
        ui->scrollSettings->ensureWidgetVisible(box);
    }
}

void frmSettings::onScrollBarValueChanged(int value)
{
    Q_UNUSED(value)

    // Search for first full visible groupbox
    for (int i = 0; i < ui->listCategories->count(); i++) {
        QGroupBox *box = this->findChild<QGroupBox*>(ui->listCategories->item(i)->data(Qt::UserRole).toString());
        if (box) {
            if (!box->visibleRegion().isEmpty() && box->visibleRegion().boundingRect().y() == 0) {
                // Select corresponding item in categories list
                ui->listCategories->setCurrentRow(i);
                return;
            }
        }
    }
}

QString frmSettings::port()
{
    return ui->cboPort->currentText();
}

void frmSettings::setPort(QString port)
{
    ui->cboPort->setCurrentText(port);
}

int frmSettings::baud()
{
    return ui->cboBaud->currentText().toInt();
}

void frmSettings::setBaud(int baud)
{
    ui->cboBaud->setCurrentText(QString::number(baud));
}

double frmSettings::toolDiameter()
{
    return ui->txtToolDiameter->value();
}

void frmSettings::setToolDiameter(double diameter)
{
    ui->txtToolDiameter->setValue(diameter);
}

double frmSettings::toolLength()
{
    return ui->txtToolLength->value();
}

void frmSettings::setToolLength(double length)
{
    ui->txtToolLength->setValue(length);
}

bool frmSettings::antialiasing()
{
    return ui->chkAntialiasing->isChecked();
}

void frmSettings::setAntialiasing(bool antialiasing)
{
    ui->chkAntialiasing->setChecked(antialiasing);
}

bool frmSettings::zBuffer()
{
    return ui->chkZBuffer->isChecked();
}

void frmSettings::setZBuffer(bool zBuffer)
{
    ui->chkZBuffer->setChecked(zBuffer);
}

double frmSettings::lineWidth()
{
    return ui->txtLineWidth->value();
}

void frmSettings::setLineWidth(double lineWidth)
{
    ui->txtLineWidth->setValue(lineWidth);
}

double frmSettings::arcLength()
{
    return ui->txtArcLength->value();
}

void frmSettings::setArcLength(double arcPrecision)
{
    ui->txtArcLength->setValue(arcPrecision);
}

double frmSettings::arcDegree()
{
    return ui->txtArcDegree->value();
}

void frmSettings::setArcDegree(double arcDegree)
{
    ui->txtArcDegree->setValue(arcDegree);
}

double frmSettings::arcPrecision()
{
    return ui->radArcDegreeMode->isChecked() ? ui->txtArcDegree->value() : ui->txtArcLength->value();
}

bool frmSettings::arcDegreeMode()
{
    return ui->radArcDegreeMode->isChecked();
}

void frmSettings::setArcDegreeMode(bool arcDegreeMode)
{
    ui->radArcDegreeMode->setChecked(arcDegreeMode);
}

bool frmSettings::showProgramCommands()
{
    return ui->chkShowProgramCommands->isChecked();
}

void frmSettings::setShowProgramCommands(bool showAllCommands)
{
    ui->chkShowProgramCommands->setChecked(showAllCommands);
}

bool frmSettings::showUICommands()
{
    return ui->chkShowUICommands->isChecked();
}

void frmSettings::setShowUICommands(bool showUICommands)
{
    ui->chkShowUICommands->setChecked(showUICommands);
}

int frmSettings::spindleSpeedMin()
{
    return ui->txtSpindleSpeedMin->value();
}

void frmSettings::setSpindleSpeedMin(int speed)
{
    ui->txtSpindleSpeedMin->setValue(speed);
}

int frmSettings::spindleSpeedMax()
{
    return ui->txtSpindleSpeedMax->value();
}

void frmSettings::setSpindleSpeedMax(int speed)
{
    ui->txtSpindleSpeedMax->setValue(speed);
}

int frmSettings::laserPowerMin()
{
    return ui->txtLaserPowerMin->value();
}

void frmSettings::setLaserPowerMin(int value)
{
    ui->txtLaserPowerMin->setValue(value);
}

int frmSettings::laserPowerMax()
{
    return ui->txtLaserPowerMax->value();
}

void frmSettings::setLaserPowerMax(int value)
{
    ui->txtLaserPowerMax->setValue(value);
}

int frmSettings::rapidSpeed()
{
    return m_rapidSpeed;
}

void frmSettings::setRapidSpeed(int rapidSpeed)
{
    m_rapidSpeed = rapidSpeed;
}

int frmSettings::acceleration()
{
    return m_acceleration;
}

void frmSettings::setAcceleration(int acceleration)
{
    m_acceleration = acceleration;
}

int frmSettings::queryStateTime()
{
    return ui->txtQueryStateTime->value();
}

void frmSettings::setQueryStateTime(int queryStateTime)
{
    ui->txtQueryStateTime->setValue(queryStateTime);
}

int frmSettings::toolType()
{
    return ui->cboToolType->currentIndex();
}

void frmSettings::setToolType(int toolType)
{
    ui->cboToolType->setCurrentIndex(toolType);
}

double frmSettings::toolAngle()
{
    return ui->txtToolAngle->value();
}

void frmSettings::setToolAngle(double toolAngle)
{
    ui->txtToolAngle->setValue(toolAngle);
}

int frmSettings::fps()
{
    return ui->cboFps->currentText().toInt();
}

void frmSettings::setFps(int fps)
{
    ui->cboFps->setCurrentText(QString::number(fps));
}

bool frmSettings::vsync()
{
    return ui->chkVSync->isChecked();
}

void frmSettings::setVsync(bool value)
{
    ui->chkVSync->setChecked(value);
}

bool frmSettings::msaa()
{
    return ui->radMSAA->isChecked();
}

void frmSettings::setMsaa(bool msaa)
{
    ui->radMSAA->setChecked(msaa);
}

bool frmSettings::autoCompletion()
{
    return ui->chkAutocompletion->isChecked();
}

void frmSettings::setAutoCompletion(bool autoCompletion)
{
    ui->chkAutocompletion->setChecked(autoCompletion);
}

int frmSettings::units()
{
    return m_units;
}

void frmSettings::setUnits(int units)
{
    m_units = units;
}

bool frmSettings::simplify()
{
    return ui->chkSimplify->isChecked();
}

void frmSettings::setSimplify(bool simplify)
{
    ui->chkSimplify->setChecked(simplify);
}

double frmSettings::simplifyPrecision()
{
    return ui->txtSimplifyPrecision->value();
}

void frmSettings::setSimplifyPrecision(double simplifyPrecision)
{
    ui->txtSimplifyPrecision->setValue(simplifyPrecision);
}

QList<ColorPicker *> frmSettings::colors()
{
    return ui->grpColors->findChildren<ColorPicker*>();
}

QColor frmSettings::colors(QString name)
{
    ColorPicker *pick = this->findChildren<ColorPicker*>("clp" + name).at(0);
    if (pick) return pick->color(); else return QColor();
}

int frmSettings::fontSize()
{
    return ui->cboFontSize->currentText().toInt();
}

void frmSettings::setFontSize(int fontSize)
{
    ui->cboFontSize->setCurrentText(QString::number(fontSize));
}

bool frmSettings::grayscaleSegments()
{
    return ui->chkGrayscale->isChecked();
}

void frmSettings::setGrayscaleSegments(bool value)
{
    ui->chkGrayscale->setChecked(value);
}

bool frmSettings::grayscaleSCode()
{
    return ui->radGrayscaleS->isChecked();
}

void frmSettings::setGrayscaleSCode(bool value)
{
    ui->radGrayscaleS->setChecked(value);
    ui->radGrayscaleZ->setChecked(!value);
}

bool frmSettings::drawModeVectors()
{
    return ui->radDrawModeVectors->isChecked();
}

void frmSettings::setDrawModeVectors(bool value)
{
    ui->radDrawModeVectors->setChecked(value);
    ui->radDrawModeRaster->setChecked(!value);
}

bool frmSettings::ignoreErrors()
{
    return ui->chkIgnoreErrors->isChecked();
}

void frmSettings::setIgnoreErrors(bool value)
{
    ui->chkIgnoreErrors->setChecked(value);
}

bool frmSettings::autoLine()
{
    return ui->chkAutoLine->isChecked();
}

void frmSettings::setAutoLine(bool value)
{
    ui->chkAutoLine->setChecked(value);
}

QString frmSettings::startCommands()
{
    return ui->txtStartCommands->toPlainText();
}

void frmSettings::setStartCommands(QString commands)
{
    ui->txtStartCommands->setPlainText(commands);
}

QString frmSettings::endCommands()
{
    return ui->txtEndCommands->toPlainText();
}

void frmSettings::setEndCommands(QString commands)
{
    ui->txtEndCommands->setPlainText(commands);
}

QString frmSettings::toolChangeCommands()
{
    return ui->txtToolChangeCommands->toPlainText();
}

void frmSettings::setToolChangeCommands(QString commands)
{
    ui->txtToolChangeCommands->setPlainText(commands);
}

bool frmSettings::pauseToolChange()
{
    return ui->chkPauseToolChange->isChecked();
}

void frmSettings::setPauseToolChange(bool pause)
{
    ui->chkPauseToolChange->setChecked(pause);
}

QString frmSettings::language()
{
    return ui->cboLanguage->currentData().toString();
}

void frmSettings::setLanguage(QString language)
{
    int i = ui->cboLanguage->findData(language);
    if (i != -1) ui->cboLanguage->setCurrentIndex(i);
}

QVector3D frmSettings::machineBounds()
{
    return m_machineBounds;
}

void frmSettings::setMachineBounds(QVector3D bounds)
{
    m_machineBounds = bounds;
}

bool frmSettings::homingEnabled()
{
    return m_homingEnabled;
}

void frmSettings::setHomingEnabled(bool homing)
{
    m_homingEnabled = homing;
}

bool frmSettings::softLimitsEnabled()
{
    return m_softLimitsEnabled;
}

void frmSettings::setSoftLimitsEnabled(bool softLimits)
{
    m_softLimitsEnabled = softLimits;
}

void frmSettings::showEvent(QShowEvent *se)
{
    Q_UNUSED(se)
}

void frmSettings::searchPorts()
{
    ui->cboPort->clear();

    foreach (QSerialPortInfo info ,QSerialPortInfo::availablePorts()) {
        ui->cboPort->insertItem(0, info.portName());
    }
}

void frmSettings::on_cmdRefresh_clicked()
{
    searchPorts();
}

void frmSettings::on_cmdOK_clicked()
{
    this->accept();
}

void frmSettings::on_cmdCancel_clicked()
{
    this->reject();
}

void frmSettings::on_cboToolType_currentIndexChanged(int index)
{
    ui->lblToolAngle->setEnabled(index == 1);
    ui->txtToolAngle->setEnabled(index == 1);
}

void frmSettings::on_cmdDefaults_clicked()
{
    if (QMessageBox::warning(this, qApp->applicationDisplayName(), tr("Reset settings to default values?"),
                             QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel) != QMessageBox::Yes) return;

    setPort("");
    setBaud(115200);

    setIgnoreErrors(false);

    setQueryStateTime(40);
    setRapidSpeed(2000);
    setAcceleration(100);
    setSpindleSpeedMin(0);
    setSpindleSpeedMax(10000);
    setLaserPowerMin(0);
    setLaserPowerMax(100);
    setUnits(0);

    setArcLength(0.1);
    setArcDegreeMode(true);
    setArcDegree(5.0);

    setLineWidth(1.5);
    setAntialiasing(true);
    setMsaa(true);
    setSimplify(true);
    setSimplifyPrecision(0.0);
    setFps(60);
    setZBuffer(false);
    setGrayscaleSegments(false);
    setGrayscaleSCode(true);
    setDrawModeVectors(true);

    setToolType(1);
    setToolAngle(15.0);
    setToolDiameter(3.0);
    setToolLength(30.0);

    setShowProgramCommands(false);
    setAutoCompletion(true);

    ui->clpTool->setColor(QColor(255, 153, 0));

    ui->clpVisualizerBackground->setColor(QColor(255, 255, 255));
    ui->clpVisualizerText->setColor(QColor(0, 0, 0));

    ui->clpToolpathNormal->setColor(QColor(0, 0, 0));
    ui->clpToolpathDrawn->setColor(QColor(217, 217, 217));
    ui->clpToolpathHighlight->setColor(QColor(145, 130, 230));
    ui->clpToolpathZMovement->setColor(QColor(255, 0, 0));
    ui->clpToolpathStart->setColor(QColor(255, 0, 0));
    ui->clpToolpathEnd->setColor(QColor(0, 255, 0));

    setFontSize(9);

    // Shortcuts
    QMap<QString, QString> d;
    d["actFileNew"] = "Ctrl+N";
    d["actFileOpen"] = "Ctrl+O";
    d["actFileSave"] = "Ctrl+S";
    d["actFileSaveAs"] = "Ctrl+Shift+S";
    d["actJogXPlus"] = "Num+6";
    d["actJogXMinus"] = "Num+4";
    d["actJogYPlus"] = "Num+8";
    d["actJogYMinus"] = "Num+2";
    d["actJogZPlus"] = "Num+9";
    d["actJogZMinus"] = "Num+3";
    d["actJogStop"] = "Num+5";
    d["actJogStepNext"] = "Num+1";
    d["actJogStepPrevious"] = "Num+7";
    d["actJogFeedNext"] = "Num++";
    d["actJogFeedPrevious"] = "Num+-";
    d["actJogKeyboardControl"] = "ScrollLock";
    d["actSpindleOnOff"] = "Num+0";
    d["actSpindleSpeedPlus"] = "Num+*";
    d["actSpindleSpeedMinus"] = "Num+/";
    
    QTableWidget *table = ui->tblShortcuts;

    for (int i = 0; i < table->rowCount(); i++) {
        QString s = table->item(i, 0)->data(Qt::DisplayRole).toString();
        table->item(i, 2)->setData(Qt::DisplayRole, d.keys().contains(s) ? d[s] : "");
    }

    ui->txtStartCommands->clear();
    ui->txtEndCommands->clear();
    ui->txtToolChangeCommands->clear();
    ui->chkPauseToolChange->setChecked(true);
    setLanguage("en");

    emit settingsSetByDefault();
}

void frmSettings::on_cboFontSize_currentTextChanged(const QString &arg1)
{
    qApp->setStyleSheet(QString(qApp->styleSheet()).replace(QRegExp("font-size:\\s*\\d+"), "font-size: " + arg1));
}

void frmSettings::on_radDrawModeVectors_toggled(bool checked)
{
    ui->chkSimplify->setEnabled(checked);
    ui->lblSimpilyPrecision->setEnabled(checked && ui->chkSimplify->isChecked());
    ui->txtSimplifyPrecision->setEnabled(checked && ui->chkSimplify->isChecked());

    ui->radDrawModeRaster->setChecked(!checked);
}

void frmSettings::on_radDrawModeRaster_toggled(bool checked)
{
    ui->radDrawModeVectors->setChecked(!checked);
}

void frmSettings::on_radGrayscaleS_toggled(bool checked)
{
    ui->radGrayscaleZ->setChecked(!checked);
}

void frmSettings::on_radGrayscaleZ_toggled(bool checked)
{
    ui->radGrayscaleS->setChecked(!checked);
}