# Z-probe

A common example of zeroing the Z-axis.  
Since probing may occur while a program is running (e.g. after a tool change), the script saves and later restores the CNC’s operating modes.

Feed values below are given in mm/min, so the script explicitly selects G94. Without it, a controller left in G93 (inverse time) mode would run the probe moves far too fast.

The offset from the actual tool position to the surface after probing can be baked into the G92 command.  
In this sample the offset is assumed to be zero.

```js
// Save current parser state (absolute/relative positioning, planes, units, etc.)
app.device.storeParserState();

// Run the precision surface-probe cycle:
app.device.sendCommands([
    "G21G91G94",     // 1. Relative positioning (G91), metric units (G21), mm/min feed (G94)
    "G38.2Z-30F100", // 2. Fast probe: plunge 30 mm at 100 mm/min
    "G0Z1",          // 3. Retract 1 mm after first touch
    "G38.2Z-2F10",   // 4. Slow probe: move another 2 mm at 10 mm/min
    "G92Z0",         // 5. Set current Z position as the new zero (zero Z)
    "G91G0Z5"        // 6. Safe retract: lift 5 mm above the new zero
]);

// Wait until all commands are executed and acknowledged
app.device.waitResponses();

// Restore original parser state
app.device.restoreParserState();
```