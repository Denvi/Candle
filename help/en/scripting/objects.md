# Objects

| Object              | Property/Method          | Type     | Arguments             | Return Value     | Description                                                                         |
|---------------------|--------------------------|----------|-----------------------|------------------|-------------------------------------------------------------------------------------|
| `app`               | `addAction(action)`      | Function | `QAction` object      | –                | Adds an action to the application; shortcuts can be attached.                       |
|                     | `removeAction(action)`   | Function | `QAction` object      | –                | Removes a previously added action.                                                  |
|                     | `newFile()`              | Function | –                     | –                | Creates a new G-code program.                                                       |
|                     | `loadFile(fileName)`     | Function | file name string      | –                | Loads a G-code program from a file.                                                 |
|                     | `loadFile(commands)`     | Function | array of commands     | –                | Loads a G-code program from a list of commands.                                     |
|                     | `saveFile()`             | Function | –                     | –                | Saves the current G-code program.                                                   |
|                     | `saveFile(fileName)`     | Function | file name string      | –                | Saves the G-code program to the specified file.                                     |
|                     | `buttonSize`             | Value    | –                     | -                | Standard button size for program panels.                                            |
|                     | `dataLocation`           | Value    | –                     | –                | Application data directory path.                                                    |
|                     | `profileName`            | Value    | –                     | –                | Name of the active settings profile.                                                |
|                     | `path`                   | Value    | –                     | –                | Absolute installation path of the program.                                          |
|                     | `device`                 | Object   | –                     | –                | Object for interacting with the CNC controller.                                     |
|                     | `program`                | Object   | –                     | –                | Object for working with the loaded G-code program.                                  |
|                     | `sender`                 | Object   | –                     | –                | Object controlling the sending of the G-code program to the CNC controller.         |
|                     | `storage`                | Object   | –                     | –                | Object for working with persistent data storage.                                    |
|                     | `window`                 | Object   | –                     | –                | Main application window object.                                                     |
|                     | `settingsAboutToLoad()`  | Signal   | –                     | –                | Before settings are loaded.                                                         |
|                     | `settingsLoaded()`       | Signal   | –                     | –                | After settings have been loaded.                                                    |
|                     | `settingsAboutToSave()`  | Signal   | –                     | –                | Before settings are saved.                                                          |
|                     | `settingsSaved()`        | Signal   | –                     | –                | After settings have been written to disk.                                           |
|                     | `settingsAboutToShow()`  | Signal   | –                     | –                | Right before the Settings dialog is shown.                                          |
|                     | `settingsAccepted()`     | Signal   | –                     | –                | When user accepts changes in the Settings dialog.                                   |
|                     | `settingsRejected()`     | Signal   | –                     | –                | When user cancels changes in the Settings dialog.                                   |
|                     | `settingsSetByDefault()` | Signal   | –                     | –                | When settings are reset to default values.                                          |
|                     | `pluginsLoaded()`        | Signal   | –                     | –                | After all extensions have been loaded.                                              |
|                     | `settings`               | Object   | –                     | –                | The global settings object (see below).                                             |
| `app.device`        | `storeParserState()`     | Function | –                     | –                | Saves the current parser state.                                                     |
|                     | `restoreParserState()`   | Function | –                     | –                | Restores the previously saved parser state.                                         |
|                     | `waitResponses()`        | Function | –                     | –                | Waits for all previously sent commands to be acknowledged by the controller.        |
|                     | `bufferLength`           | Value    | –                     | –                | Total size of commands currently in the controller buffer.                          |
|                     | `commandLength`          | Value    | –                     | –                | Number of commands currently in the controller buffer.                              |
|                     | `queueLength`            | Value    | –                     | –                | Number of commands queued for sending to the controller.                            |
|                     | `machine`                | Value    | –                     | –                | Current machine coordinates.                                                        |
|                     | `probe`                  | Value    | –                     | –                | Last received probe contact coordinates.                                            |
|                     | `state`                  | Value    | –                     | –                | Current CNC controller state.                                                       |
|                     | `work`                   | Value    | –                     | –                | Current work coordinates.                                                           |
|                     | `stateChanged`           | Signal   | State                 | –                | Current CNC controller state changed.                                               |
| `app.program`       | `lowerBounds`            | Value    | –                     | –                | Lower bounds of the loaded program.                                                 |
|                     | `upperBounds`            | Value    | –                     | –                | Upper bounds of the loaded program.                                                 |
| `app.sender`        | `state`                  | Value    | –                     | –                | Current state of the program sender.                                                |
|                     | `stateChanged`           | Signal   | State                 | –                | Sender state changed.                                                               |
| `app.settings`      | `port`                   | Value    | –                     | –                | "Connection – Port" setting.                                                        |
|                     | `baud`                   | Value    | –                     | –                | "Connection – Baud".                                                                |
|                     | `queryStateTime`         | Value    | –                     | –                | "Connection – Status query period".                                                 |
|                     | `spindleSpeedMin`        | Value    | –                     | –                | "Machine information – Spindle speed min".                                          |
|                     | `spindleSpeedMax`        | Value    | –                     | –                | "Machine information – Spindle speed max".                                          |
|                     | `laserPowerMin`          | Value    | –                     | –                | "Machine information – Laser power min".                                            |
|                     | `laserPowerMax`          | Value    | –                     | –                | "Machine information – Laser power max".                                            |
|                     | `axisAEnabled`           | Value    | –                     | –                | "Machine information – Enable A-axis" setting.                                      |
|                     | `axisAX`                 | Value    | –                     | –                | "Machine information – A-axis direction – X" setting.                               |
|                     | `arcLength`              | Value    | –                     | –                | "Arc approximation segments size – by length".                                      |
|                     | `arcDegree`              | Value    | –                     | –                | "Arc approximation segments – by angle".                                            |
|                     | `arcDegreeMode`          | Value    | –                     | –                | Arc approximation segments ‑ by angle mode toggle.                                  |
|                     | `startCommands`          | Value    | –                     | –                | "Sender – Use program start commands".                                              |
|                     | `endCommands`            | Value    | –                     | –                | "Sender – Use program end commands".                                                |
|                     | `toolChangeCommands`     | Value    | –                     | –                | "Sender – Use tool change commands".                                                |
|                     | `ignoreErrors`           | Value    | –                     | –                | "Sender – Ignore error responses".                                                  |
|                     | `autoLine`               | Value    | –                     | –                | "Sender – Automatically set parser state before sending from selected line".        |
|                     | `pauseToolChange`        | Value    | –                     | –                | "Sender – Pause sender on M6 command.                                               |
|                     | `lineWidth`              | Value    | –                     | –                | "Visualizer – Line width".                                                          |
|                     | `antialiasing`           | Value    | –                     | –                | "Visualizer – Smoothing".                                                           |
|                     | `msaa`                   | Value    | –                     | –                | "Visualizer – MSAA".                                                                |
|                     | `fps`                    | Value    | –                     | –                | "Visualizer – FPS lock".                                                            |
|                     | `vsync`                  | Value    | –                     | –                | "Visualizer – V‑Sync".                                                              |
|                     | `zBuffer`                | Value    | –                     | –                | "Visualizer – Z‑buffer".                                                            |
|                     | `drawModeVectors`        | Value    | –                     | –                | "Visualizer – Program draw mode" (0 raster, 1 vectors).                             |
|                     | `simplify`               | Value    | –                     | –                | "Visualizer – Simplify geometry".                                                   |
|                     | `simplifyPrecision`      | Value    | –                     | –                | "Visualizer – Simplify geometry - Precision".                                       |
|                     | `grayscaleSegments`      | Value    | –                     | –                | "Visualizer – Grayscale segments".                                                  |
|                     | `grayscaleSCode`         | Value    | –                     | –                | "Visualizer – Grayscale segments - By 'S'‑code".                                    |
|                     | `toolType`               | Value    | –                     | –                | "Tool model – Type" (0 flat, 1 conic).                                              |
|                     | `toolAngle`              | Value    | –                     | –                | "Tool model – Angle".                                                               |
|                     | `toolDiameter`           | Value    | –                     | –                | "Tool model – Diameter".                                                            |
|                     | `toolLength`             | Value    | –                     | –                | "Tool model – Length".                                                              |
|                     | `showProgramCommands`    | Value    | –                     | –                | "Console – Show G‑code program commands".                                           |
|                     | `showUICommands`         | Value    | –                     | –                | "Console – Show UI commands".                                                       |
|                     | `autoCompletion`         | Value    | –                     | –                | "Console – Command auto‑completion".                                                |
|                     | `fontSize`               | Value    | –                     | –                | "User interface – Font size".                                                       |
|                     | `language`               | Value    | –                     | –                | "User interface – Language" (ISO 639‑1).                                            |
|                     | `units`                  | Value    | –                     | –                | CNC units (0 metric, 1 imperial).                                                   |
|                     | `rapidSpeed`             | Value    | –                     | –                | Rapid movement speed.                                                               |
|                     | `acceleration`           | Value    | –                     | –                | Acceleration.                                                                       |
|                     | `machineBounds`          | Value    | –                     | –                | CNC movement bounds.                                                                |
|                     | `homingEnabled`          | Value    | –                     | –                | Homing enabled flag.                                                                |
|                     | `softLimitsEnabled`      | Value    | –                     | –                | Soft limits enabled flag.                                                           |
| `app.storage`       | `group(key)`             | Function | group key string      | group object     | Returns a data group object from storage by key.                                    |
|                     | `setValue(key, value)`   | Function | key string, value     | –                | Stores a value under the given full key.                                            |
|                     | `value(key)`             | Function | key string            | value            | Retrieves a value by full key.                                                      |
|                     | `contains(key)`          | Function | key string            | boolean          | Checks whether a value exists for the given full key.                               |
|                     | `remove(key)`            | Function | key string            | –                | Removes the value associated with the full key.                                     |
| `app.storage.group` | `group(key)`             | Function | sub-group key string  | group object     | Returns a sub-group object.                                                         |
|                     | `setValue(key, value)`   | Function | key string, value     | –                | Stores a value under the given key within the group.                                |
|                     | `value(key)`             | Function | key string            | value            | Retrieves a value by key within the group.                                          |
|                     | `contains(key)`          | Function | key string            | boolean          | Checks whether a key exists within the group.                                       |
|                     | `remove(key)`            | Function | key string            | –                | Removes the key-value pair within the group.                                        |
|                     | `childKeys()`            | Function | –                     | array of strings | Returns all keys directly under this group.                                         |
|                     | `childGroups()`          | Function | –                     | array of strings | Returns all sub-group names under this group.                                       |
| **vars**            | `Mx`, `My`, `Mz`         | Value    | –                     | –                | Current machine coordinates X/Y/Z.                                                  |
|                     | `Wx`, `Wy`, `Wz`         | Value    | –                     | –                | Current workpiece coordinates X/Y/Z.                                                |
|                     | `G54x`, …, `G59z`        | Value    | –                     | –                | Coordinate‑system offsets for G54–G59.                                              |
|                     | `CS`                     | Value    | –                     | –                | Current coordinate system string ("G54"…"G59").                                     |
|                     | `x`, `y`, `z`            | Value    | –                     | –                | Offset of current system’s X/Y/Z.                                                   |
|                     | `G92x`, …, `G92z`        | Value    | –                     | –                | Workpiece offsets.                                                                  |
|                     | `G28x`, …, `G30z`        | Value    | –                     | –                | Saved positions for G28/G30 commands.                                               |
|                     | `TLOx`, …, `TLOz`        | Value    | –                     | –                | Tool‑offsets X/Y/Z.                                                                 |
|                     | `PRBx`, `PRBy`, `PRBz`   | Value    | –                     | –                | Probe contact coordinates.                                                          |
|                     | `tool`                   | Value    | –                     | –                | Current tool number.                                                                |
| `script`            | `importExtension(name)`  | Function | extension name string | –                | Loads another JavaScript extension; the list of available extensions is in Table 9. |
|                     | `path`                   | Value    | –                     | –                | Absolute path to this extension folder.                                             |

## Sending‑state enumerations

| State | Description                                                                                           |
|-------|-------------------------------------------------------------------------------------------------------|
| -1    | Unknown state                                                                                        |
| 0     | Sending program                                                                                    |
| 1     | Transition to pause state                                                                          |
| 2     | Pause in progress                                                                                  |
| 3     | Program finished – all CP commands sent                                                            |
| 4     | Transfer completed – controller processed all CP commands                                         |
| 5     | Manual tool change                                                                                 |

## Controller state enumerations

| State | Description                                                                                           |
|-------|--------------------------------------------------------------------------------------------------------|
| -1    | Unknown state                                                                                        |
| 1     | Ready to receive commands                                                                            |
| 2     | Alarm                                                                                                 |
| 3     | Running                                                                                               |
| 4     | Searching home position                                                                             |
| 5     | End of "Hold" mode transition                                                                       |
| 6     | In "Hold" mode                                                                                    |
| 8     | CP verification mode                                                                                |
| 9     | Door closed, ready to resume                                                                        |
| 10    | Door open, CNC stopped                                                                              |
| 11    | Door open, pausing or parking                                                                        |
| 12    | Door closed, resuming work or returning from parking                                                |
| 13    | Movement state                                                                                       |
| 14    | Sleep mode                                                                                           |