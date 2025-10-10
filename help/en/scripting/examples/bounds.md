# Boundary trace

```js
// Load Qt modules so we can show a completion dialog
script.importExtension("qt.gui");
script.importExtension("qt.widgets");

// Build and immediately send a list of G-codes to the controller:
// G21 = metric mode, G90 = absolute positioning, F100 = 100 mm/min feed-rate
// Next four lines form a rectangular contour that follows the work-area bounds
// M2 = proper program end; the controller will reply when the whole path is done
app.device.sendCommands([
    "G21G90F100",
    "G1X" + app.program.lowerBounds.x() + "Y" + app.program.lowerBounds.y(),
    "G1Y" + app.program.upperBounds.y(),
    "G1X" + app.program.upperBounds.x(),
    "G1Y" + app.program.lowerBounds.y(),
    "G1X" + app.program.lowerBounds.x(),
    "M2" // response sent after actual motion finish
]);

// Wait until the controller confirms all commands (including M2) are executed
app.device.waitResponses();

// Show a modal "Done" message to the user
QMessageBox.information(app.window, "", "Done");
```