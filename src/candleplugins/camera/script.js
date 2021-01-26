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
var storedName;
var storedResolution;
var storedZoom;
var storedPosition;
var storedAimPosition;
var storedAimSize;
var storedAimLineWidth;
var storedAimColor;

// Ui
var uiWindow;
var uiSettings;

function init()
{
    loader.setWorkingDirectory(new QDir(pluginPath));
    loader.addPluginPath(appPath);
    loader.addPluginPath(pluginPath + "/plugins")
    
    app.settingsLoaded.connect(onAppSettingsLoaded);
    app.settingsSaved.connect(onAppSettingsSaved);
    app.settingsAboutToShow.connect(onAppSettingsAboutToShow);
    app.settingsAccepted.connect(onAppSettingsAccepted);
    app.settingsRejected.connect(onAppSettingsRejected);
    app.settingsSetByDefault.connect(onAppSettingsDefault);
}

function createWindowWidget()
{
    var f = new QFile(pluginPath + "/widget.ui");

    if (f.open(QIODevice.ReadOnly)) {        
        uiWindow = loader.load(f);
    }
    return uiWindow;
}

function createSettingsWidget()
{
    var f = new QFile(pluginPath + "/settings.ui");

    if (f.open(QIODevice.ReadOnly)) {        
        uiSettings = loader.load(f);
        
    }
    return uiSettings;
}

function onAppSettingsSaved()
{
    settings.setValue("name", uiSettings.cboCameraName.currentText);
    settings.setValue("resolution", uiSettings.cboCameraResolution.currentText);
    settings.setValue("zoom", uiSettings.txtCameraZoom.text);
    settings.setValue("position", uiSettings.txtCameraPosition.text);
    settings.setValue("aimPosition", uiSettings.txtCameraAimPosition.text);
    settings.setValue("aimSize", uiSettings.txtCameraAimSize.value);
    settings.setValue("aimLineWidth", uiSettings.txtCameraAimLineWidth.value);
    settings.setValue("aimColor", uiSettings.colCameraAimColor.colorInt);
}

function onAppSettingsLoaded()
{
    // Load settings
    uiSettings.cboCameraName.addItems(uiWindow.camMain.availableCameras);
    uiSettings.cboCameraName.currentText = settings.value("name");
    uiSettings.cboCameraResolution.currentText = settings.value("resolution", "1280x720");
    uiSettings.txtCameraZoom.text = settings.value("zoom", 1);
    uiSettings.txtCameraPosition.text = settings.value("position", "0, 0");
    uiSettings.txtCameraAimPosition.text = settings.value("aimPosition", "0, 0");
    uiSettings.txtCameraAimSize.value = settings.value("aimSize", 20);
    uiSettings.txtCameraAimLineWidth.value = settings.value("aimLineWidth", 1);
    uiSettings.colCameraAimColor.colorInt = settings.value("aimColor", -65536);

    // Apply settings
    applySettings();

    // Update resolutions list
    var r = uiSettings.cboCameraResolution.currentText;
    uiSettings.cboCameraResolution.addItems(uiWindow.camMain.availableResolutions);
    uiSettings.cboCameraResolution.currentText = r;

    // Connect signals/slots
    uiWindow.camMain.posChanged.connect(onPosChanged);
    uiWindow.camMain.aimPosChanged.connect(onAimPosChanged);
    uiWindow.camMain.aimSizeChanged.connect(onAimSizeChanged);
    uiWindow.camMain.aimLineWidthChanged.connect(onAimLineWidthChanged);
    uiWindow.camMain.aimColorChanged.connect(onAimColorChanged);
    uiWindow.camMain.zoomChanged.connect(onZoomChanged);
    uiSettings.cboCameraName.currentTextChanged.connect(onCameraNameChanged);
}

function onAppSettingsAboutToShow()
{
    storedName = uiSettings.cboCameraName.currentText;
    storedResolution = uiSettings.cboCameraResolution.currentText;
    storedZoom = uiSettings.txtCameraZoom.text;
    storedPosition = uiSettings.txtCameraPosition.text;
    storedAimPosition = uiSettings.txtCameraAimPosition.text;
    storedAimSize = uiSettings.txtCameraAimSize.value;
    storedAimLineWidth = uiSettings.txtCameraAimLineWidth.value;
    storedAimColor = uiSettings.colCameraAimColor.colorInt;
}

function onAppSettingsAccepted()
{
    applySettings();
}

function onAppSettingsRejected()
{
    applySettings();
}

function onAppSettingsDefault()
{
    uiSettings.cboCameraName.currentText = "";
    uiSettings.cboCameraResolution.currentText = "";
    uiSettings.txtCameraZoom.text = "1.0";
    uiSettings.txtCameraPosition.text = "0, 0";
    uiSettings.txtCameraAimPosition.text = "0, 0";
    uiSettings.txtCameraAimSize.value = "20";
    uiSettings.txtCameraAimLineWidth.value = "1";
    uiSettings.colCameraAimColor.colorInt = -65536;
}

function applySettings()
{
    // Resolution
    if (uiSettings.cboCameraResolution.currentText != "") {
        var l = uiSettings.cboCameraResolution.currentText.split("x");
        uiWindow.camMain.resolution = [parseInt(l[0]), parseInt(l[1])];
    }
    
    // Zoom
    if (uiSettings.txtCameraZoom.text == "") uiSettings.txtCameraZoom.text = "1.0";
    uiWindow.camMain.zoom = parseFloat(uiSettings.txtCameraZoom.text);

    // Padding
    if (uiSettings.txtCameraPosition.text == "") uiSettings.txtCameraPosition.text = "0, 0";
    l = uiSettings.txtCameraPosition.text.split(",");
    uiWindow.camMain.pos = [parseInt(l[0]), parseInt(l[1])];

    // Aim position
    if (uiSettings.txtCameraAimPosition.text == "") uiSettings.txtCameraAimPosition.text = "0, 0";
    l = uiSettings.txtCameraAimPosition.text.split(",");
    uiWindow.camMain.aimPos = [parseFloat(l[0]), parseFloat(l[1])];

    // Aim size
    uiWindow.camMain.aimSize = parseInt(uiSettings.txtCameraAimSize.value);

    // Aim line width
    uiWindow.camMain.aimLineWidth = parseInt(uiSettings.txtCameraAimLineWidth.value);
    
    // Aim color
    uiWindow.camMain.aimColor = parseInt(uiSettings.colCameraAimColor.colorInt);

    // Update camera
    uiWindow.camMain.cameraName = uiSettings.cboCameraName.currentText;
}

function onCameraNameChanged(name)
{
    // Update camera
    uiWindow.camMain.cameraName = name;
    
    // Update resolutions list
    var r = uiSettings.cboCameraResolution.currentText;
    uiSettings.cboCameraResolution.clear();
    uiSettings.cboCameraResolution.addItems(uiWindow.camMain.availableResolutions);
    uiSettings.cboCameraResolution.currentText = r;
}

function onPosChanged(pos)
{
    uiSettings.txtCameraPosition.text = pos.join(", ");
}

function onAimPosChanged(aimPos)
{
    p = [parseFloat(aimPos[0].toFixed(3)), parseFloat(aimPos[1].toFixed(3))];
    uiSettings.txtCameraAimPosition.text = p.join(", ");
}

function onAimSizeChanged(aimSize)
{
    uiSettings.txtCameraAimSize.text = aimSize;
}

function onAimLineWidthChanged(aimLineWidth)
{
    uiSettings.txtCameraAimLineWidth.text = aimLineWidth;
}

function onAimColorChanged(aimColor)
{
    uiSettings.colCameraAimColor.colorInt = aimColor;
}

function onZoomChanged(zoom)
{
    uiSettings.txtCameraZoom.text = zoom.toFixed(3);
}