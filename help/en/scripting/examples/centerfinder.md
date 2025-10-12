# Center finder

Below is a sample script that locates the center of a hole.

Before running, jog the tool inside the hole; preliminary zeroing is not required.

To let the user cancel the “search radius” prompt and abort the script early, the code is wrapped in an IIFE.

```js
script.importExtension("qt.core");   // access to Qt globals
script.importExtension("qt.widgets"); // access to QInputDialog

(function () {
    /* ---------- 1. Get search radius ---------- */
    const settings     = app.storage.group("HoleCenterFinder"); // settings group for this script
    const storedRadius = settings.value("radius", 10);          // last used value (default 10 mm)

    const radius = QInputDialog.getDouble(
        app.window,                     // parent window
        "Hole center finder",           // dialog title
        "Find radius",                  // field label
        storedRadius, 0.0, 100.0, 0,    // value, min, max, decimals
        Qt.Dialog                       // flags
    );
    if (!radius) return;                // user pressed Cancel

    settings.setValue("radius", radius); // remember the entered value

    /* ---------- 2. Remember current position ---------- */
    const startX = app.device.work.x;
    const startY = app.device.work.y;

    /* ---------- 3. Find center along Y ---------- */
    // First touch: move forward by the given radius
    app.device.sendCommand("G91G38.2F100Y" + radius);
    app.device.waitResponses();         // wait for probe hit
    const probeY = app.device.probe.y;  // record touch coordinate

    // Return to start Y, then move back by the same radius
    app.device.sendCommands([
        "G90G0Y" + startY,      // rapid return in absolute mode
        "G91G38.2Y-" + radius   // relative move in reverse direction
    ]);
    app.device.waitResponses();

    // Move to the midpoint between the two touches
    app.device.sendCommand("G90G53G0Y" + (app.device.probe.y + probeY) / 2);

    /* ---------- 4. Find center along X (same idea) ---------- */
    app.device.sendCommand("G91G38.2X" + radius);
    app.device.waitResponses();
    const probeX = app.device.probe.x;

    app.device.sendCommands([
        "G90G0X" + startX,
        "G91G38.2X-" + radius
    ]);
    app.device.waitResponses();

    // Final move to the absolute hole center
    app.device.sendCommand("G90G53G0X" + (app.device.probe.x + probeX) / 2);
})();
```