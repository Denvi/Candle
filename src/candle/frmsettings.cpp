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
#include <QDir>
#include <QLocale>
#include <QSpacerItem>
#include <QAction>

class CustomKeySequenceEdit : public QKeySequenceEdit
{
public:
    explicit CustomKeySequenceEdit(QWidget *parent = 0): QKeySequenceEdit(parent) {}
    ~CustomKeySequenceEdit() {}

protected:
    void keyPressEvent(QKeyEvent *pEvent) {
        QKeySequenceEdit::keyPressEvent(pEvent);
        QString s = keySequence().toString().split(", ").first();

        if (pEvent->modifiers() & Qt::KeypadModifier) s = "Num+" + s;

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

    for (int i = 0; i < ui->stackMain->count(); i++) {
        ui->listCategories->addItem(ui->stackMain->widget(i)->findChild<QGroupBox*>()->title());
    }

    ui->listCategories->setMinimumWidth(ui->listCategories->sizeHintForColumn(0) * 1.1);
    ui->listCategories->item(0)->setSelected(true);
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
        m_storedValues.insert(o, o->property("value").toDouble());

    foreach (QAbstractButton* o, this->findChildren<QAbstractButton*>())
        m_storedChecks.insert(o, o->isChecked());

    foreach (QComboBox* o, this->findChildren<QComboBox*>())
        m_storedCombos.insert(o, o->currentText());

    foreach (ColorPicker* o, this->findChildren<ColorPicker*>())
        m_storedColors.insert(o, o->color());

    foreach (QLineEdit* o, this->findChildren<QLineEdit*>())
        m_storedTextBoxes.insert(o, o->text());

    foreach (QPlainTextEdit* o, this->findChildren<QPlainTextEdit*>())
        m_storedPlainTexts.insert(o, o->toPlainText());

    return QDialog::exec();
}

void frmSettings::undo()
{
    for (auto it = m_storedValues.constBegin(); it != m_storedValues.constEnd(); it++)
        it.key()->setProperty("value", it.value());

    for (auto it = m_storedChecks.constBegin(); it != m_storedChecks.constEnd(); it++)
        it.key()->setChecked(it.value());

    for (auto it = m_storedCombos.constBegin(); it != m_storedCombos.constEnd(); it++)
        it.key()->setCurrentText(it.value());

    for (auto it = m_storedColors.constBegin(); it != m_storedColors.constEnd(); it++)
        it.key()->setColor(it.value());

    for (auto it = m_storedTextBoxes.constBegin(); it != m_storedTextBoxes.constEnd(); it++)
        it.key()->setText(it.value());

    for (auto it = m_storedPlainTexts.constBegin(); it != m_storedPlainTexts.constEnd(); it++)
        it.key()->setPlainText(it.value());
}

void frmSettings::addCustomSettings(QGroupBox *box)
{
    auto page = new QWidget();
    auto pageLayout = new QVBoxLayout();

    page->setLayout(pageLayout);
    pageLayout->addWidget(box);
    pageLayout->setMargin(0);

    ui->stackMain->addWidget(page);
    ui->listCategories->addItem(box->title());

    m_customSettings.append(box);
}

void frmSettings::on_listCategories_currentRowChanged(int currentRow)
{
    ui->stackMain->setCurrentIndex(currentRow);
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

bool frmSettings::useStartCommands()
{
    return ui->chkUseStartCommands->isChecked();
}

void frmSettings::setUseStartCommands(bool value)
{
    ui->chkUseStartCommands->setChecked(value);
}

QString frmSettings::startCommands()
{
    return ui->txtStartCommands->toPlainText();
}

void frmSettings::setStartCommands(QString commands)
{
    ui->txtStartCommands->setPlainText(commands);
}

bool frmSettings::useEndCommands()
{
    return ui->chkUseEndCommands->isChecked();
}

void frmSettings::setUseEndCommands(bool value)
{
    ui->chkUseEndCommands->setChecked(value);
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

bool frmSettings::toolChangeUseCommands()
{
    return ui->chkToolChangeUseCommands->isChecked();
}

void frmSettings::setToolChangeUseCommands(bool value)
{
    ui->chkToolChangeUseCommands->setChecked(value);
}

bool frmSettings::toolChangeUseCommandsConfirm()
{
    return ui->chkToolChangeUseCommandsConfirm->isChecked();
}

void frmSettings::setToolChangeUseCommandsConfirm(bool value)
{
    ui->chkToolChangeUseCommandsConfirm->setChecked(value);
}

bool frmSettings::toolChangePause()
{
    return ui->chkToolChangePause->isChecked();
}

void frmSettings::setToolChangePause(bool pause)
{
    ui->chkToolChangePause->setChecked(pause);
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

bool frmSettings::referenceXPlus()
{
    return ui->radReferenceXPlus->isChecked();
}

void frmSettings::setReferenceXPlus(bool value)
{
    ui->radReferenceXPlus->setChecked(value);
}

bool frmSettings::referenceYPlus()
{
    return ui->radReferenceYPlus->isChecked();
}

void frmSettings::setReferenceYPlus(bool value)
{
    ui->radReferenceYPlus->setChecked(value);
}

bool frmSettings::referenceZPlus()
{
    return ui->radReferenceZPlus->isChecked();
}

void frmSettings::setReferenceZPlus(bool value)
{
    ui->radReferenceZPlus->setChecked(value);
}

bool frmSettings::invertedSliderControls()
{
    return ui->chkInvertedSliderControls->isChecked();
}

void frmSettings::setInvertedSliderControls(bool value)
{
    ui->chkInvertedSliderControls->setChecked(value);
}

QTableWidget* frmSettings::shortcuts()
{
    return ui->tblShortcuts;
}

void frmSettings::setShortcuts(QList<QAction*> acts)
{
    QTableWidget *table = ui->tblShortcuts;

    table->clear();
    table->setColumnCount(3);
    table->setRowCount(acts.count());
    table->setHorizontalHeaderLabels(QStringList() << tr("Command") << tr("Text") << tr("Shortcuts"));

    table->verticalHeader()->setDefaultAlignment(Qt::AlignCenter);
    table->verticalHeader()->setFixedWidth(table->verticalHeader()->sizeHint().width() + 11);

    qSort(acts.begin(), acts.end(), [] (QAction *a1, QAction *a2) { return a1->objectName() < a2->objectName(); });
    for (int i = 0; i < acts.count(); i++) {
        table->setItem(i, 0, new QTableWidgetItem(acts.at(i)->objectName()));
        table->setItem(i, 1, new QTableWidgetItem(acts.at(i)->text().remove("&")));
        table->setItem(i, 2, new QTableWidgetItem(acts.at(i)->shortcut().toString()));

        table->item(i, 0)->setFlags(Qt::ItemIsEnabled);
        table->item(i, 1)->setFlags(Qt::ItemIsEnabled);
        table->item(i, 2)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable);
    }

    table->resizeColumnsToContents();
    table->setMinimumHeight(table->rowHeight(0) * 10
        + table->horizontalHeader()->height() + table->frameWidth() * 2);
    table->horizontalHeader()->setMinimumSectionSize(table->horizontalHeader()->sectionSize(2));
    table->horizontalHeader()->setStretchLastSection(true);
}

void frmSettings::showEvent(QShowEvent *se)
{
    Q_UNUSED(se)
}

void frmSettings::searchPorts()
{
    auto getPortNumber = [](const QString &portName)
    {
        QRegularExpression re("(\\d+)");
        auto match = re.match(portName);
        return match.hasMatch() ? match.captured(1).toInt() : -1;
    };

    auto ports = QSerialPortInfo::availablePorts();
    std::sort(
        ports.begin(),
        ports.end(),
        [getPortNumber](const QSerialPortInfo &a, const QSerialPortInfo &b)
        {
            return getPortNumber(a.portName()) > getPortNumber(b.portName());
        });

    ui->cboPort->clear();
    foreach (QSerialPortInfo info, ports)
    {
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

    setDefaultSettings();
    emit settingsSetByDefault();
}

void frmSettings::setDefaultSettings()
{
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

    setInvertedSliderControls(false);

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
    ui->chkToolChangePause->setChecked(false);
    ui->chkToolChangeUseCommands->setChecked(false);
    ui->chkToolChangeUseCommandsConfirm->setChecked(false);
    setLanguage("en");
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