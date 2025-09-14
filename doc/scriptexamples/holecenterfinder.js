script.importExtension("qt.widgets");

(function () {
    const radius = parseFloat(QInputDialog.getText(0, "Hole center finder", "Find radius", 0, "10"));
    if (!radius) return;

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