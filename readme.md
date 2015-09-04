grblControl
-----------
GRBL controller application with G-Code visualizer written in Qt.

Supported functions:
* Controlling GRBL-based cnc-machine via console commands, buttons on form, numpad.
* Monitoring cnc-machine state.
* Loading, editing, saving and sending of G-code files to cnc-machine.
* Visualizing G-code files.

Downloads:
----------
* Windows: [grblControl_0.5.zip](https://github.com/Denvi/grblControl/releases/download/0.5/grblControl_0.5.zip)
* Linux: [grblControl_0.5.tar.gz](https://github.com/Denvi/grblControl/releases/download/0.5/grblControl_0.5.tar.gz)

Version 0.5 release:
--------------------
* Toolpath highlighting on g-code program table selection.

![screenshot](/screenshots/screenshot_toolpath_highlighting.png)

Version 0.4 release:
--------------------
G-code modification with heightmap.

Original file:
![screenshot](/screenshots/screenshot_heightmap_original.png)

Heightmap:
![screenshot](/screenshots/screenshot_heightmap_heightmap.png)

Bicubic interpolation:
![screenshot](/screenshots/screenshot_heightmap_heightmap_interpolation.png)

Modified file:
![screenshot](/screenshots/screenshot_heightmap_modified.png)

Version 0.3 release:
--------------------
* Recent files & commands lists added.
* Custom Z-probe commands supported now.
* Imperial units of GRBL reports support added.
* Main form compacted.

Visualizer only view:
![screenshot](/screenshots/screenshot_compact_visualizer.png)

Table only view:
![screenshot](/screenshots/screenshot_compact_table.png)

Live G-code editing:
![screenshot](/screenshots/screenshot_live_edit.png)

Version 0.2 release:
--------------------
* Jog/spindle control with numpad added:
* Feed override function added.
* "Spindle", "Feed", "Jog" groupboxes collapsible now.
* Visualizer works in "Check mode" now.
* Visualizer Z-buffer option added.
* Some bugs fixed.

![screenshot](/screenshots/screenshot.png)