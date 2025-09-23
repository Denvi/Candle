// This file is a part of "Candle" application.
// Copyright 2015-2025 Hayrullin Denis Ravilevich

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

// Ui
var uiPanel;

function init()
{
    loader.setWorkingDirectory(new QDir(pluginPath));
    loader.addPluginPath(designerPluginsPath);
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
    // Direct CTRL+X command send
    app.device.sendCommand(String.fromCharCode(24), -100, false, true);
}