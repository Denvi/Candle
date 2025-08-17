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
var settings = new QSettings(pluginPath + "/settings.ini", QSettings.IniFormat);
var deviceState = -1;
var senderState = -1;
var holdSent = false;

// Ui
var uiPanel;

function init()
{
    loader.setWorkingDirectory(new QDir(pluginPath));
    loader.addPluginPath(designerPluginsPath);

    app.deviceStateChanged.connect(onAppDeviceStateChanged);
    app.senderStateChanged.connect(onAppSenderStateChanged);
    app.responseReceived.connect(onAppResponseReceived);
}

function createPanelWidget()
{
    var f = new QFile(pluginPath + "/widget.ui");

    if (f.open(QIODevice.ReadOnly)) {
        uiPanel = loader.load(f);
        uiPanel.cmdStop.backgroundColor = new QColor(0xffff0000);
        uiPanel.cmdStop.clicked.connect(onButtonClicked);
    }
    return uiPanel;
}

function onButtonClicked()
{
    app.sendCommand("!", -100, false);
    holdSent = true;
}

function onAppDeviceStateChanged(status)
{    
    deviceState = status;
    if (holdSent && (status == 5)) {
        holdSent = false;
        app.sendCommand(String.fromCharCode(24), -100, false);
    }
    if (holdSent && (status == 0)) holdSent = false;
}

function onAppSenderStateChanged(status)
{
    senderState = status;
}

function onAppResponseReceived(command, index, response)
{ 
}
