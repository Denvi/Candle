function on_cmdTest_clicked() {
    main.sendCommand("$#", -10, settings.showUICommands);
}

function on_responseReceived(command, index, response)
{
    if (index == -10) {
        ui.txtResponse.plainText = response;
    }
}

ui.cmdTest.clicked.connect(on_cmdTest_clicked);
main.responseReceived.connect(on_responseReceived);