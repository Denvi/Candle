script.importExtension("qt.gui");
script.importExtension("qt.widgets");

app.sendCommands([
    "G21G90F100",
    "G1X" + app.program.lowerBounds.x() + "Y" + app.program.lowerBounds.y(),
    "G1Y" + app.program.upperBounds.y(),
    "G1X" + app.program.upperBounds.x(),
    "G1Y" + app.program.lowerBounds.y(),
    "G1X" + app.program.lowerBounds.x(),
    "M2" // will respond when the toolpath is actually executed
]);
app.waitResponses();

QMessageBox.information(app.window, "", "Done");