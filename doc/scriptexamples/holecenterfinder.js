script.importExtension("qt.core");
script.importExtension("qt.widgets");

(function () {
    // Restore previously entered radius
    const settings = new QSettings();
    settings.beginGroup("HoleCenterFinder");
    const storedRadius = settings.value("radius", 10);

    const radius = QInputDialog.getDouble(app.window, "Hole center finder", "Find radius", storedRadius, 0.0, 100.0, 0, Qt.Dialog);
    if (!radius) return;

    // Store radius
    settings.setValue("radius", radius);

    // Store start position
    const startX = vars.Wx;
    const startY = vars.Wy;

    // Find center on Y-axis
    app.sendCommand("G91G38.2F100Y" + radius);
    app.waitResponses();
    const probeY = vars.PRBy;

    app.sendCommands([
        "G90G0Y" + startY,
        "G91G38.2Y-" + radius
    ]);
    app.waitResponses();
    app.sendCommand("G90G53G0Y" + (vars.PRBy + probeY) / 2);

    // Find center on X-axis
    app.sendCommand("G91G38.2X" + radius);
    app.waitResponses();
    const probeX = vars.PRBx;

    app.sendCommands([
        "G90G0X" + startX,
        "G91G38.2X-" + radius
    ]);
    app.waitResponses();
    app.sendCommand("G90G53G0X" + (vars.PRBx + probeX) / 2);
})();