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
// var storedName;
// var storedResolution;
// var storedZoom;
// var storedPosition;

// Ui
var uiWindow;
var uiSettings;

var DEVICE_STATE_IDLE = 1;
var DEVICE_STATE_JOG = 13;
var SENDER_STATE_STOPPED = 4;
var deviceState = null;
var senderState = null;
var canJog = false;
var jogging = false;
var joggingAxis = null;
var joggingSpeed = null;

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

    app.deviceStateChanged.connect(onDeviceStateChanged);
    app.responseReceived.connect(onResponseReceived);// (QString command, int tableIndex, QString response);
    app.senderStateChanged.connect(onSenderStateChanged); // (bool state);
    //app.statusReceived.connect(onStatusReceived); // (QString status);
}

var joggingQueue = [];

function queueNewJoggingCommand()
{
    var command = '$J=G21 G91 X-1 F' + Math.abs(joggingSpeed) + ";" + Math.random();
    if (app.sendCommand(command) == 0) {
        joggingQueue.push(command);

        return true;
    }

    return false;
}

function startJogging()
{
    if (!canJog || jogging) return;

    app.console("startJogging");

    if (queueNewJoggingCommand()) {
        queueNewJoggingCommand();
        jogging = true;
    }
}

function startOrUpdateJogging(x, y, z)
{
    if (!joggingAxis) {
        switch (true) {
            case (x != 0): joggingAxis = "X"; break;
            case (y != 0): joggingAxis = "Y"; break;
            case (z != 0): joggingAxis = "Z"; break;
            default:
                stopJogging();
                return;
        }
    }
    var newJoggingSpeed = joggingAxisPos(x, y, z) * 10;
    if (newJoggingSpeed < -200) newJoggingSpeed = -200;
    if (newJoggingSpeed > 200) newJoggingSpeed = 200;
    if (joggingSpeed != newJoggingSpeed) {
        app.console("speed to " + newJoggingSpeed + " from " + joggingSpeed);
        joggingSpeed = newJoggingSpeed;
        if (jogging) {
            app.console("restart...");
            app.sendRealtimeCommand(String.fromCharCode(0x85));
            joggingQueue = [];
        }
        setTimeout(function() {
        }, 5);
        jogging = false;
        app.console("new speed " + newJoggingSpeed);
        startJogging();
        // setInterval(function(timer) {
        //     jogging = false;
        //     if (deviceState == DEVICE_STATE_IDLE) {
        //         killInterval(timer);
        //         app.console("new speed " + newJoggingSpeed);
        //         startJogging();
        //     } else {
        //         app.console("wait for idle");
        //     }
        // }, 10);
    }
}

function stopJogging()
{
    if (!jogging) return;
    app.console("stopJogging");
    app.sendRealtimeCommand(String.fromCharCode(0x85));
    joggingQueue = [];
    jogging = false;
    joggingAxis = null;
    joggingSpeed = null;
    //     int bufferLength();
    // int commandsLength();
    // int queueLength();
    app.console("queue: " + app.queueLength() + " buffer: " + app.bufferLength() + " commands: " + app.commandsLength());
}

function updateCanJog()
{
    canJog = (deviceState == DEVICE_STATE_IDLE || deviceState == DEVICE_STATE_JOG)  && senderState == SENDER_STATE_STOPPED;
    app.debug("Can jog: " + canJog);

    if (!canJog && jogging) {
        stopJogging();
    }
}

function onSenderStateChanged(state)
{
    app.debug("Sender state changed: " + state);
    senderState = state;
    updateCanJog();
}

function onResponseReceived(command, tableIndex, response)
{
    if (command.substr(0, 3) != "$J=") {
        return;
    }

    for (var queueIndex in joggingQueue) {
        if (joggingQueue[queueIndex] == command) {
            //app.console("ack found");
            joggingQueue.splice(queueIndex, 1);
            break;
        }
    }

    //app.console(joggingQueue.length + " in queue");
    if (joggingQueue.length < 3 && jogging) {
        queueNewJoggingCommand();
    }
}

function onStatusReceived(status)
{
    //app.debug("Status received: " + status);
}

function onDeviceStateChanged(state)
{
    deviceState = state;
    app.console("Device state changed: " + state);
    updateCanJog();
}

function joggingAxisPos(x, y, z)
{
    switch (joggingAxis) {
        case "X": return x;
        case "Y": return y;
        case "Z": return z;
    }
    return 0;
}

function onPosChanged(x, y, z)
{
    //app.debug("Pos changed: " + x + ", " + y + ", " + z);
    if ((joggingAxis != null && joggingAxisPos(x, y, z) == 0) || (x == 0 && y == 0 && z == 0))  {
        stopJogging();
    } else {
        startOrUpdateJogging(x, y, z);
    }
}

function createWindowWidget()
{
    var f = new QFile(pluginPath + "/widget.ui");

    if (f.open(QIODevice.ReadOnly)) {
        uiWindow = loader.load(f);
    }

    return uiWindow;
}

function setInterval(callback, delay) {
    var timer = new QTimer();
    timer.interval = delay;
    timer.timeout.connect(this, function() {
        callback(timer);
    });
    timer.start();
    return timer;
}

function killInterval(timer) {
    timer.stop();
    timer.deleteLater();
}

function setTimeout(callback, delay) {
    var timer = new QTimer();
    timer.interval = delay;
    timer.singleShot = true;
    timer.timeout.connect(this, function() {
        timer.deleteLater(timer);
        callback();
    });
    timer.start();
    return timer;
}

function createSettingsWidget()
{
    var f = new QFile(pluginPath + "/settings.ui");

    if (f.open(QIODevice.ReadOnly)) {
        uiSettings = loader.load(f);
    }

    uiWindow.joystickMain.buttonPushed.connect(onBtnPushed);
    uiWindow.joystickMain.posChanged.connect(onPosChanged); // (this->posx, this->posy, this->posz);

    // setInterval(function() { app.debug('t'); }, 500);
    // setTimeout(function() { app.debug('ta'); }, 1500);

    return uiSettings;
}

function onAppSettingsSaved()
{
    settings.setValue("name", uiSettings.cboCameraName.currentText);
    settings.setValue("resolution", uiSettings.cboCameraResolution.currentText);
    settings.setValue("zoom", uiSettings.txtCameraZoom.text);
    settings.setValue("position", uiSettings.txtCameraPosition.text);
    // settings.setValue("aimPosition", uiSettings.txtCameraAimPosition.text);
    // settings.setValue("aimSize", uiSettings.txtCameraAimSize.value);
    // settings.setValue("aimLineWidth", uiSettings.txtCameraAimLineWidth.value);
    // settings.setValue("aimColor", uiSettings.colCameraAimColor.colorInt);
}

function onAppSettingsLoaded()
{
    // // Load settings
    // uiSettings.cboCameraName.addItems(uiWindow.camMain.availableCameras);
    // uiSettings.cboCameraName.currentText = settings.value("name");
    // uiSettings.cboCameraResolution.currentText = settings.value("resolution", "1280x720");
    // uiSettings.txtCameraZoom.text = settings.value("zoom", 1);
    // uiSettings.txtCameraPosition.text = settings.value("position", "0, 0");
    // uiSettings.txtCameraAimPosition.text = settings.value("aimPosition", "0, 0");
    // uiSettings.txtCameraAimSize.value = settings.value("aimSize", 20);
    // uiSettings.txtCameraAimLineWidth.value = settings.value("aimLineWidth", 1);
    // uiSettings.colCameraAimColor.colorInt = settings.value("aimColor", -65536);

    // // Apply settings
    // applySettings();

    // // Update resolutions list
    // var r = uiSettings.cboCameraResolution.currentText;
    // uiSettings.cboCameraResolution.addItems(uiWindow.camMain.availableResolutions);
    // uiSettings.cboCameraResolution.currentText = r;

    // // Connect signals/slots
    // uiWindow.camMain.posChanged.connect(onPosChanged);
    // uiWindow.camMain.aimPosChanged.connect(onAimPosChanged);
    // uiWindow.camMain.aimSizeChanged.connect(onAimSizeChanged);
    // uiWindow.camMain.aimLineWidthChanged.connect(onAimLineWidthChanged);
    // uiWindow.camMain.aimColorChanged.connect(onAimColorChanged);
    // uiWindow.camMain.zoomChanged.connect(onZoomChanged);
    // uiSettings.cboCameraName.currentTextChanged.connect(onCameraNameChanged);
}

function onBtnPushed()
{
    app.console("Button pushed");
    app.debug("Button pushed a");
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

    // Pv ing
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

// function onCameraNameChanged(name)
// {
//     // Update camera
//     uiWindow.camMain.cameraName = name;

//     // Update resolutions list
//     var r = uiSettings.cboCameraResolution.currentText;
//     uiSettings.cboCameraResolution.clear();
//     uiSettings.cboCameraResolution.addItems(uiWindow.camMain.availableResolutions);
//     uiSettings.cboCameraResolution.currentText = r;
// }

// function onPosChanged(pos)
// {
//     uiSettings.txtCameraPosition.text = pos.join(", ");
// }

// function onAimPosChanged(aimPos)
// {
//     p = [parseFloat(aimPos[0].toFixed(3)), parseFloat(aimPos[1].toFixed(3))];
//     uiSettings.txtCameraAimPosition.text = p.join(", ");
// }

// function onAimSizeChanged(aimSize)
// {
//     uiSettings.txtCameraAimSize.text = aimSize;
// }

// function onAimLineWidthChanged(aimLineWidth)
// {
//     uiSettings.txtCameraAimLineWidth.text = aimLineWidth;
// }

// function onAimColorChanged(aimColor)
// {
//     uiSettings.colCameraAimColor.colorInt = aimColor;
// }

// function onZoomChanged(zoom)
// {
//     uiSettings.txtCameraZoom.text = zoom.toFixed(3);
// }