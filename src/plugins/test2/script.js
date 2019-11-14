function on_cmdTest_clicked() {
    main.sendCommand(ui.txtTest.text, -10, mainSettings.showUICommands);
}

function on_responseReceived(command, index, response)
{
    if (index == -10) {
        ui.txtResponse.plainText = response;
    }
}

function on_settings_aboutToSave()
{
    settings.txtTest.text = ui.txtTest.text;
}

function on_settings_loaded()
{
    ui.txtTest.text = settings.txtTest.text;
}

function on_settings_changed()
{
    ui.txtTest.text = settings.txtTest.text;
}

ui.cmdTest.clicked.connect(on_cmdTest_clicked);
main.responseReceived.connect(on_responseReceived);
main.settingsLoaded.connect(on_settings_loaded);
main.settingsAboutToSave.connect(on_settings_aboutToSave);
main.settingsChanged.connect(on_settings_changed);