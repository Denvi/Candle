script.importExtension("qt.core");
script.importExtension("qt.widgets");

(function () {
    // Restore previously entered radius
    const settings = app.storage.group("HoleCenterFinder");    
    const storedRadius = settings.value("radius", 10);

    const radius = QInputDialog.getDouble(app.window, "Hole center finder", "Find radius", storedRadius, 0.0, 100.0, 0, Qt.Dialog);
    if (!radius) return;

    // Store radius
    settings.setValue("radius", radius);

    // Store start position
    const startX = app.device.work.x;
    const startY = app.device.work.y;

    // Find center on Y-axis
    app.device.sendCommand("G91G38.2F100Y" + radius);
    app.device.waitResponses();
    const probeY = app.device.probe.y;

    app.device.sendCommands([
        "G90G0Y" + startY,
        "G91G38.2Y-" + radius
    ]);
    app.device.waitResponses();
    app.device.sendCommand("G90G53G0Y" + (app.device.probe.y + probeY) / 2);

    // Find center on X-axis
    app.device.sendCommand("G91G38.2X" + radius);
    app.device.waitResponses();
    const probeX = app.device.probe.x;

    app.device.sendCommands([
        "G90G0X" + startX,
        "G91G38.2X-" + radius
    ]);
    app.device.waitResponses();
    app.device.sendCommand("G90G53G0X" + (app.device.probe.x + probeX) / 2);
})();