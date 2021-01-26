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
var loader = new QUiLoader();
var settings = new QSettings(pluginPath + "/settings.ini", QSettings.IniFormat);
var deviceState = -1;
var senderState = -1;
var currentCS = "G54";
var currentOffsets = "";

// Ui
var uiPanel;
var uiSettings;

function init()
{
    loader.setWorkingDirectory(new QDir(pluginPath));
    loader.addPluginPath(appPath);

    app.deviceStateChanged.connect(onAppDeviceStateChanged);
    app.senderStateChanged.connect(onAppSenderStateChanged);
    app.responseReceived.connect(onAppResponseReceived);
    app.settingsLoaded.connect(onAppSettingsLoaded);
}

function createPanelWidget()
{
    var f = new QFile(pluginPath + "/widget.ui");

    function onCsClicked(cs)
    {
        return function() {app.sendCommands(cs);};
    }

    function onZeroClicked(a)
    {
        return function() {app.sendCommand("".concat("G10 L20 P", currentCS.slice(-1) - 3, " ", a));}
    }

    if (f.open(QIODevice.ReadOnly)) {
        uiPanel = loader.load(f);

        for (var i = 54; i <= 57; i++) {
            uiPanel["cmdG" + i].clicked.connect(onCsClicked("G" + i));
        }

        uiPanel.cmdX0.clicked.connect(onZeroClicked("X0"));
        uiPanel.cmdY0.clicked.connect(onZeroClicked("Y0"));
        uiPanel.cmdZ0.clicked.connect(onZeroClicked("Z0"));
        uiPanel.cmdAll0.clicked.connect(onZeroClicked("X0 Y0 Z0"));
    }
    return uiPanel;
}

function onAppSettingsLoaded()
{
    var u = app.settings.units;
    var b = u ? 999 : 9999;

    uiPanel.txtOffsetX.decimals = u ? 4 : 3;
    uiPanel.txtOffsetY.decimals = u ? 4 : 3;
    uiPanel.txtOffsetZ.decimals = u ? 4 : 3;

    uiPanel.txtOffsetX.mimimum = -b;
    uiPanel.txtOffsetX.maximum = b;
    uiPanel.txtOffsetY.mimimum = -b;
    uiPanel.txtOffsetY.maximum = b;
    uiPanel.txtOffsetZ.mimimum = -b;
    uiPanel.txtOffsetZ.maximum = b;
}

function onAppDeviceStateChanged(status)
{
    uiPanel.setEnabled((status == 1) && (senderState == 4));
    
    deviceState = status;
}

function onAppSenderStateChanged(status)
{
    uiPanel.setEnabled((status == 4) && (deviceState == 1));

    senderState = status;
}

function onAppResponseReceived(command, index, response)
{
    function displayOffsets(r) {
        var gx = new RegExp(currentCS + ":([\\d\\.\\-]+),([\\d\\.\\-]+),([\\d\\.\\-]+)");
        var s = r.match(gx);
        if (s) {
            for (var i = 0; i < s.length; i++) {
                uiPanel.txtOffsetX.value = parseFloat(s[1]);
                uiPanel.txtOffsetY.value = parseFloat(s[2]);
                uiPanel.txtOffsetZ.value = parseFloat(s[3]);
            }
        }
    }

    if (command == "$G") {
        var rx = new RegExp("G5[4-9]");
        var s = response.match(rx);
        if (s) {
            uiPanel["cmd" + s[0]].checked = true;
            if (s[0] != currentCS) {
                currentCS = s[0];
                displayOffsets(currentOffsets);
            }
        }
    }

    if (command == "$#") {
        currentOffsets = response;
        displayOffsets(currentOffsets);
    }
}
