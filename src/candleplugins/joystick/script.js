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

// Ui
var uiWindow;
var uiSettings;

var DEVICE_STATE_IDLE = 1;
var DEVICE_STATE_JOG = 13;
var SENDER_STATE_STOPPED = 4;
var DIR_NONE = null;
var DIR_LEFT = 1;
var DIR_RIGHT = 2;
var deviceState = null;
var senderState = null;
var canJog = false;
var jogging = false;
var joggingAxis = null;
var joggingSpeed = null;
var joggingDir = DIR_NONE;
var stoppingJogging = false;

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
}

var joggingQueue = [];

function queueNewJoggingCommand()
{
    var speed = Math.abs(joggingSpeed);
    var distance = 0.05 * (speed / 200);
    var command = "$J=G21 G91 " + joggingAxis + (joggingSpeed < 0 ? "-" : "") + distance.toFixed(2) + " F" + speed+ ";" + Math.random().toFixed(3);
    if (app.sendCommand(command) == 0) {
        joggingQueue.push(command);

        return true;
    }

    return false;
}

function startJogging()
{
    if (!canJog || jogging) return;

    app.console("Start jogging");

    if (queueNewJoggingCommand()) {
        //app.console("Command queued");
        joggingDir = joggingSpeed > 0 ? DIR_RIGHT : DIR_LEFT;
        jogging = true;
    }
}

function startOrUpdateJogging_(x, y, z)
{
    if (!joggingAxis) {
        switch (true) {
            case (x != 0): joggingAxis = "X"; break;
            case (y != 0): joggingAxis = "Y"; break;
            case (z != 0): joggingAxis = "Z"; break;
            default:
                stopJogging("Unknown axis");
                return;
        }
    }
    var newJoggingSpeed = limitJoggingSpeed(joggingAxisPos(x, y, z) * 20);
    if (joggingSpeed != newJoggingSpeed) {
//        app.console("speed to " + newJoggingSpeed + " from " + joggingSpeed);
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

function limitJoggingSpeed(speed)
{
    var max = 1500;
    if (speed < -max) return -max;
    if (speed > max) return max;
    return speed;
}

function startOrUpdateJogging(x, y, z)
{
    if (!joggingAxis) {
        switch (true) {
            case (x != 0): joggingAxis = "X"; break;
            case (y != 0): joggingAxis = "Y"; break;
            case (z != 0): joggingAxis = "Z"; break;
            default:
                stopJogging("Unknown axis");
                return;
        }
    }
    joggingSpeed = limitJoggingSpeed(joggingAxisPos(x, y, z) * 15);
    startJogging();
}

function stopJogging(info)
{
    if (!jogging || stoppingJogging) return;

    stoppingJogging = true;
    app.console("stopJogging, sending 0x85, " + info);
    app.sendRealtimeCommand(String.fromCharCode(0x85));
    setTimeout(function() {
        app.sendRealtimeCommand(String.fromCharCode(0x85));
        jogging = false;
        joggingQueue = [];
        joggingAxis = null;
        joggingSpeed = null;
        joggingDir = DIR_NONE;
        stoppingJogging = false;
    }, 50);
}

function updateCanJog()
{
    canJog = (deviceState == DEVICE_STATE_IDLE || deviceState == DEVICE_STATE_JOG)  && senderState == SENDER_STATE_STOPPED;
    app.debug("Can jog: " + canJog);

    if (!canJog && jogging) {
        stopJogging('Cannot jog now');
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
            joggingQueue.splice(queueIndex, 1);
            break;
        }
    }

    // zawsze tylko 1 komenda na której OK czekamy
    if (joggingQueue.length == 0 && jogging) {
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
    //app.console("Device state changed: " + state);
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
    var newJoggingAxisPos = joggingAxisPos(x, y, z);
    var newJoggingDir = newJoggingAxisPos > 0 ? DIR_RIGHT : (newJoggingAxisPos < 0 ? DIR_LEFT : DIR_NONE);
    // app.console("newJoggingAxisPos: " + newJoggingAxisPos + ", newJoggingDir: " + newJoggingDir);
    if ((joggingAxis != null && newJoggingAxisPos == 0) || (x == 0 && y == 0 && z == 0))  {
        stopJogging("Axis at center (1)");
    } else if (jogging && newJoggingDir == DIR_NONE) {
        stopJogging("Axis at center (2)");
    } else if (jogging && joggingDir != newJoggingDir) {
        stopJogging("Axis changed direction");
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

    return uiSettings;
}

function onAppSettingsSaved()
{
}

function onAppSettingsLoaded()
{
}

function onBtnPushed()
{
    app.console("Button pushed");
    app.debug("Button pushed a");
}

function onAppSettingsAboutToShow()
{
}

function onAppSettingsAccepted()
{
}

function onAppSettingsRejected()
{
}

function onAppSettingsDefault()
{
}

function applySettings()
{
}
