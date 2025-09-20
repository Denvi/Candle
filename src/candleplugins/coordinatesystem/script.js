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
var designerPluginsPath = app.path + "/designerplugins";
var loader = new QUiLoader();
var deviceState = -1;
var senderState = -1;
var currentCS = "G54";

// Ui
var uiPanel;
var uiSettings;

function init()
{
    loader.setWorkingDirectory(new QDir(pluginPath));
    loader.addPluginPath(designerPluginsPath);

    app.device.stateChanged.connect(onAppDeviceStateChanged);
    app.sender.stateChanged.connect(onAppSenderStateChanged);
    app.device.responseReceived.connect(onAppResponseReceived);
    app.settingsLoaded.connect(onAppSettingsLoaded);
}

function createPanelWidget()
{
    var f = new QFile(pluginPath + "/widget.ui");

    function onCsClicked(cs)
    {
        return function() {app.device.sendCommands(cs);};
    }

    function onZeroClicked(a, b)
    {
        return function() {app.device.sendCommand("".concat("G10 L20 P", currentCS.slice(-1) - 3, " ",
            a + (app.settings.axisAEnabled && b ? " " + b : "")));}
    }

    if (f.open(QIODevice.ReadOnly)) {
        uiPanel = loader.load(f);

        for (var i = 54; i <= 57; i++) {
            uiPanel["cmdG" + i].clicked.connect(onCsClicked("G" + i));
        }

        uiPanel.cmdX0.clicked.connect(onZeroClicked("X0"));
        uiPanel.cmdY0.clicked.connect(onZeroClicked("Y0"));
        uiPanel.cmdZ0.clicked.connect(onZeroClicked("Z0"));
        uiPanel.cmdA0.clicked.connect(onZeroClicked("A0"));
        uiPanel.cmdAll0.clicked.connect(onZeroClicked("X0 Y0 Z0", "A0"));
    }
    return uiPanel;
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
    if (command == "$G") {
        var rx = new RegExp("G5[4-9]");
        var s = response.match(rx);
        if (s) {
            uiPanel["cmd" + s[0]].checked = true;
            if (s[0] != currentCS) {
                currentCS = s[0];
            }
        }
    }
}

function onAppSettingsLoaded()
{
    uiPanel.cmdA0.visible = app.settings.axisAEnabled;
}