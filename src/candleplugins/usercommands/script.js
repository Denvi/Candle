// This file is a part of "Candle" application.
// Copyright 2015-2021 Hayrullin Denis Ravilevich

script.importExtension("qt.core");
script.importExtension("qt.gui");
script.importExtension("qt.widgets");
script.importExtension("qt.custom");
script.importExtension("qt.uitools");

// Vars
var appPath = app.path;
var pluginPath = script.path;
var pluginName = script.name;
var designerPluginsPath = app.path + "/designerplugins";
var loader = new QUiLoader();
var buttonSize = 48;
var deviceState = -1;
var storedButtons = new Array();
var storedActions = new Array();
var embedIconPath = pluginPath + "/images";
var userIconPath = app.dataLocation + "/" + pluginName + "/images";

// Ui
var uiPanel;
var uiSettings;

function init()
{
    loader.setWorkingDirectory(new QDir(pluginPath));
    loader.addPluginPath(designerPluginsPath);

    app.settingsLoaded.connect(onAppSettingsLoaded);
    app.settingsSaved.connect(onAppSettingsSaved);
    app.settingsAboutToShow.connect(onAppSettingsAboutToShow);
    app.settingsAccepted.connect(onAppSettingsAccepted);
    app.settingsRejected.connect(onAppSettingsRejected);
    app.device.stateChanged.connect(onAppDeviceStateChanged);
}

function createPanelWidget()
{
    var f = new QFile(pluginPath + "/widget.ui");

    if (f.open(QIODevice.ReadOnly)) {
        uiPanel = loader.load(f);
    }
    return uiPanel;
}

function createSettingsWidget()
{
    var f = new QFile(pluginPath + "/settings.ui");

    if (f.open(QIODevice.ReadOnly)) {
        uiSettings = loader.load(f);

        var t = uiSettings.tblButtons;
        t.verticalHeader().defaultAlignment = Qt.AlignCenter;
        t.setItemDelegateForColumn(0, new CodeDelegate(t));
        t.setItemDelegateForColumn(1, new IconDelegate(t));
        t.setItemDelegateForColumn(2, new TypeDelegate(t));
        var d = new CodeDelegate(t);
        d.alignment = Qt.AlignLeft | Qt.AlignTop;
        d.adjustHeight = true;
        t.setItemDelegateForColumn(3, d);
        t.minimumHeight = t.verticalHeader().defaultSectionSize * 4 + t.horizontalHeader().height + t.frameWidth * 2;

        uiSettings.cmdUp.clicked.connect(onCmdUpClicked);
        uiSettings.cmdDown.clicked.connect(onCmdDownClicked);
        uiSettings.cmdAdd.clicked.connect(onCmdAddClicked);
        uiSettings.cmdRemove.clicked.connect(onCmdRemoveClicked);
        uiSettings.cmdRemoveAll.clicked.connect(onCmdRemoveAllClicked);
    }
    return uiSettings;
}

function onCmdAddClicked()
{
    var t = uiSettings.tblButtons;
    var r = t.rowCount++;

    var h = new QTableWidgetItem();
    h.setTextAlignment(Qt.AlignCenter);
    h.setText("...");

    t.setItem(r, 0, h);
    t.setItem(r, 1, new QTableWidgetItem());
    t.setItem(r, 2, new QTableWidgetItem("0"));
    t.setItem(r, 3, new QTableWidgetItem());

    t.verticalHeader().setFixedWidth(t.verticalHeader().sizeHint.width() + 11);
}

function onCmdRemoveClicked()
{
    var t = uiSettings.tblButtons;
    var r = t.currentRow();
    var c = t.currentColumn();

    t.removeRow(r);
    t.setCurrentCell(r <= (t.rowCount - 1) ? r : t.rowCount - 1, c);
}

function onCmdRemoveAllClicked()
{
    uiSettings.tblButtons.rowCount = 0;
}

function onCmdUpClicked()
{
    var t = uiSettings.tblButtons;
    var r = t.currentRow();
    var c = t.currentColumn();

    if (r > 0) {
        t.insertRow(r - 1);
        for (var i = 0; i < 4; i++) {
            t.setItem(r - 1, i, t.takeItem(r + 1, i));
        }
        t.removeRow(r + 1);
        t.setCurrentCell(r - 1, c);
    }
}

function onCmdDownClicked()
{
    var t = uiSettings.tblButtons;
    var r = t.currentRow();
    var c = t.currentColumn();

    if (r < t.rowCount - 1) {
        t.insertRow(r + 2);
        for (var i = 0; i < 4; i++) {
            t.setItem(r + 2, i, t.takeItem(r, i));
        }
        t.removeRow(r);
        t.setCurrentCell(r + 1, c);
    }
}

function onAppSettingsLoaded()
{
    buttonSize = app.buttonSize;

    var settings = app.storage.group(pluginName);

    // Migrating old settings
    if (!settings.contains("buttons")) {
        settings = new QSettings(pluginPath + "/settings.ini", QSettings.IniFormat);
    }

    var b = settings.value("buttons");

    restoreButtonsTable(b);
    updateButtons();
    updateActions();
}

function onAppSettingsSaved()
{
    var settings = app.storage.group(pluginName);

    settings.setValue("buttons", storeButtonsTable());
}

function onAppSettingsAboutToShow()
{
    storedButtons = storeButtonsTable();
}

function onAppSettingsAccepted()
{
    updateButtons();
    updateActions();
}

function onAppSettingsRejected()
{
    restoreButtonsTable(storedButtons);
}

function onAppDeviceStateChanged(status)
{
    var t = uiSettings.tblButtons;
    var lay = uiPanel.verticalLayout.layButtons;

    for (var i = 0; i < t.rowCount; i++) {
        lay.itemAt(i).widget().setEnabled(status == 1);
    }

    for (var i = 0; i < storedActions.length; i++) {
        storedActions[i].setEnabled(status == 1);
    }

    deviceState = status;
}

function onButtonClicked(button)
{
    const type = uiSettings.tblButtons.item(button, 2).data(Qt.DisplayRole);
    const code = uiSettings.tblButtons.item(button, 3).data(Qt.DisplayRole);

    if (type == "0") {
        app.device.sendCommands(code);
    } else {
        eval(code);
    }
}

function storeButtonsTable()
{
    var t = uiSettings.tblButtons;
    var b = new Array();

    for (var i = 0; i < t.rowCount; i++) {
        var q = new Array();
        q.push(t.item(i, 0).data(Qt.DisplayRole));
        q.push(t.item(i, 1).data(Qt.DisplayRole));
        // Place code at index of 2
        q.push(t.item(i, 3).data(Qt.DisplayRole));
        q.push(t.item(i, 2).data(Qt.DisplayRole));
        b.push(q);
    }

    return b;
}

function restoreButtonsTable(b)
{
    var t = uiSettings.tblButtons;
    t.rowCount = 0;

    if (b) {
        for (var i = 0; i < b.length; i++) {
            t.insertRow(t.rowCount);
            for (var j = 0; j < b[i].length; j++) {
                var q = new QTableWidgetItem();
                q.setText(b[i][j]);
                if (j == 1) {
                    c = getIcon(b[i][j]);
                    q.setData(Qt.DecorationRole, c);
                }
                // Swap type/code indexes
                t.setItem(t.rowCount - 1, j == 3 ? 2 : (j == 2 ? 3 : j), q);
            }
            if (b[i].length < 4) {
                var q = new QTableWidgetItem();
                q.setText("0");
                t.setItem(t.rowCount - 1, 2, q);
            }
        }
        t.verticalHeader().setFixedWidth(t.verticalHeader().sizeHint.width() + 11);
    }
}

function updateButtons()
{
    var t = uiSettings.tblButtons;
    var lay = uiPanel.verticalLayout.layButtons;
    var k = lay.count();
    var c = t.rowCount;

    // Delete buttons
    for (var i = 0; i < k; i++) {
        var w = lay.takeAt(0).widget();
        w.deleteLater();
    }

    lay.update();

    // Create new buttons
    function onClicked(i)
    {
        return function() {onButtonClicked(i)};
    }

    for (var i = 0; i < c; i++) {
        var w = new StyledToolButton();
        w.minimumWidth = buttonSize;
        w.minimumHeight = buttonSize;
        w.sizePolicy = new QSizePolicy(QSizePolicy.Expanding, QSizePolicy.Fixed);
        w.iconSize = new QSize(buttonSize * 0.8, buttonSize * 0.8);

        w.icon = t.item(i, 1).data(Qt.DecorationRole);
        w.toolTip = t.item(i, 0).data(Qt.DisplayRole);
        w.clicked.connect(onClicked(i));

        w.enabled = (deviceState != -1);

        lay.addWidget(w, i / 4, i % 4);
    }

    if (c < 4) {
        for (var i = c; i < 4; i++) {
            var w = new StyledToolButton();
            w.minimumWidth = buttonSize;
            w.minimumHeight = buttonSize;
            w.sizePolicy = new QSizePolicy(QSizePolicy.Expanding, QSizePolicy.Fixed);
            w.enabled = false;
            lay.addWidget(w, i / 4, i % 4);
        }
    }

    lay.update();
}

function updateActions()
{
    var t = uiSettings.tblButtons;

    function onTriggered(i)
    {
        return function() {onButtonClicked(i)};
    }

    var l = storedActions.length;
    var n = t.rowCount;

    for (var i = n; i < l; i++) {
        var a = storedActions.pop();
        app.removeAction(a);
        a.deleteLater();
    }

    for (var i = l; i < n; i++) {
        var a = new QAction(qsTr("User button") + " " + (i + 1), uiPanel);
        a.objectName = "actUserCommandsButton" + (i + 1);
        a.triggered.connect(onTriggered(i));
        storedActions.push(a);
        app.addAction(a);
    }

    for (var i = 0; i < storedActions.length; i++) {
        storedActions[i].setEnabled(deviceState != -1);
    }
}

function setTimeout(func, interval)
{
    const timer = new QTimer();

    timer.interval = interval;
    timer.singleShot = true;
    timer.timeout.connect(func);
    timer.start();
}

function getIconList()
{
    const embedImages = (new QDir(embedIconPath)).entryList(QDir.Filters(QDir.Files));
    const userEntryList = (new QDir(userIconPath)).entryList(QDir.Filters(QDir.Files));
    const userImages = new Array();

    for (var i = 0; i < userEntryList.length; i++)
        userImages.push("*" + userEntryList[i]);

    return embedImages.concat(userImages);
}

function getIcon(name)
{
    return new QIcon(name[0] !== "*" ? embedIconPath + "/" + name : userIconPath + "/" + name.substring(1));
}

function addUserIcon(row, col) {
    var path = QFileDialog.getOpenFileName(app.window, qsTr("Open"), "", qsTr("Images (*.png *.ico *.jpg)"));
    if (path) {
        const fileName = new QFileInfo(path).fileName();
        const iconPath = userIconPath + "/" + fileName;
        (new QDir()).mkpath(userIconPath);
        QFile.copy(path, iconPath);
        uiSettings.tblButtons.model().setData(uiSettings.tblButtons.model().index(row, col), "*" + fileName);
        uiSettings.tblButtons.model().setData(uiSettings.tblButtons.model().index(row, col), new QIcon(iconPath),
            Qt.DecorationRole);
    }
}

// Icon cell delegate
function IconDelegate(parent)
{
    QStyledItemDelegate.call(this, parent);
}

IconDelegate.prototype = new QStyledItemDelegate();

IconDelegate.prototype.createEditor = function(parent, option, index)
{
    const b = new QComboBox(parent);
    const l = getIconList();
    const row = index.row();
    const col = index.column();

    for (var i = 0; i < l.length; i++) {
        b.addItem(getIcon(l[i]), l[i]);
    }
    b.addItem("...");

    b.currentTextChanged.connect(function(value) {
        if (value === "...")
            setTimeout(function() { addUserIcon(row, col) }, 0);
    });

    return b;
}

IconDelegate.prototype.setEditorData = function(editor, index)
{
    editor.currentText = index.data();
}

IconDelegate.prototype.setModelData = function(editor, model, index)
{
    if (editor.currentText && editor.currentText != "...") {
        model.setData(index, editor.currentText);
        model.setData(index, editor.itemIcon(editor.currentIndex), Qt.DecorationRole);
    } else {
        model.setData(index, "");
        model.setData(index, 0, Qt.DecorationRole);
    }
}

IconDelegate.prototype.updateEditorGeometry = function(editor, option, index)
{
    editor.geometry = option.rect();
}

IconDelegate.prototype.paint = function(painter, option, index)
{
    var q = index.data(Qt.DecorationRole);

    if (option.state() & QStyle.State_Selected) {
        painter.fillRect(option.rect(), new QColor(0xcdcdff));
    }

    if (q) {
        q.paint(painter, option.rect());
    }

    if (option.state() & QStyle.State_HasFocus) {
        var p = new QPen();
        p.setStyle(Qt.DotLine);
        painter.setPen(p);
        painter.drawRect(option.rect().adjusted(1, 0, -2, -1));
    }
}

// Code cell delegate
function CodeDelegate(parent)
{
    QStyledItemDelegate.call(this, parent);

    this.alignment = Qt.AlignCenter;
    this.adjustHeight = false;
}

CodeDelegate.prototype = new QStyledItemDelegate();

CodeDelegate.prototype.createEditor = function(parent, option, index)
{
    var t = uiSettings.tblButtons;

    if (t.item(index.row(), 2).data(Qt.DisplayRole) == "0") {
        return new QTextEdit(parent);
    } else {
        return new ScriptEdit(parent);
    }
}

CodeDelegate.prototype.setEditorData = function(editor, index)
{
    editor.plainText = index.data();

    var c = editor.textCursor();
    c.movePosition(QTextCursor.End);
    editor.setTextCursor(c);
}

CodeDelegate.prototype.setModelData = function(editor, model, index)
{
    model.setData(index, editor.plainText);
}

CodeDelegate.prototype.updateEditorGeometry = function(editor, option, index)
{
    var r = option.rect();

    if (this.adjustHeight) {
        var t = this.parent();
        r.setTop(0);
        r.setHeight(t.height - t.horizontalHeader().height - t.frameWidth * 2);
    }

    editor.geometry = r;
}

CodeDelegate.prototype.paint = function(painter, option, index)
{
    var q = index.data();

    if (option.state() & QStyle.State_Selected) {
        painter.fillRect(option.rect(), new QColor(0xcdcdff));
    }

    if (q) {
        var m = new QFontMetrics(option.font());
        var r = option.rect().adjusted(4, 4, -4, -4);
        var l = q.split("\n");
        var n = l.length;
        var k = Math.min(parseInt(r.height() / m.lineSpacing()), n);
        var s = "";

        for (var i = 0; i < k; i++) {
            if ((i == (k - 1)) && (k < n)) s += "..."; else s += l[i];
            if (i < (k - 1)) s += "\n";
        }

        painter.drawText(r, this.alignment | 0, s, r);
    }

    if (option.state() & QStyle.State_HasFocus) {
        var p = new QPen();
        p.setStyle(Qt.DotLine);
        painter.setPen(p);
        painter.drawRect(option.rect().adjusted(1, 0, -2, -1));
    }
}

// Type cell delegate
function TypeDelegate(parent)
{
    QStyledItemDelegate.call(this, parent);

    this.alignment = Qt.AlignCenter;
}

TypeDelegate.prototype = new QStyledItemDelegate();

TypeDelegate.prototype.createEditor = function(parent, option, index)
{
    var b = new QComboBox(parent);

    b.addItem(qsTr("G-code"));
    b.addItem(qsTr("Script"));

    return b;
}

TypeDelegate.prototype.setEditorData = function(editor, index)
{
    editor.currentIndex = index.data();
}

TypeDelegate.prototype.setModelData = function(editor, model, index)
{
    model.setData(index, editor.currentIndex);
}

TypeDelegate.prototype.updateEditorGeometry = function(editor, option, index)
{
    editor.geometry = option.rect();
}

TypeDelegate.prototype.paint = function(painter, option, index)
{
    var q = index.data() == "0" ? qsTr("G-code") : qsTr("Script");

    if (option.state() & QStyle.State_Selected) {
        painter.fillRect(option.rect(), new QColor(0xcdcdff));
    }

    if (q) {
        var r = option.rect().adjusted(4, 4, -4, -4);
        painter.drawText(r, this.alignment | 0, q, r);
    }

    if (option.state() & QStyle.State_HasFocus) {
        var p = new QPen();
        p.setStyle(Qt.DotLine);
        painter.setPen(p);
        painter.drawRect(option.rect().adjusted(1, 0, -2, -1));
    }
}