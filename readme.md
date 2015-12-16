grblControl
-----------
GRBL controller application with G-Code visualizer written in Qt.

Supported functions:
* Controlling GRBL-based cnc-machine via console commands, buttons on form, numpad.
* Monitoring cnc-machine state.
* Loading, editing, saving and sending of G-code files to cnc-machine.
* Visualizing G-code files.

Version 0.8 release:
--------------------
* You can save files, transformed according to heightmap.
* Console window have adjustable size now.
* Added "Degree" minimum arc size to parser settings.
* Some minor bugs fixed.

Downloads:
----------
* Windows: [grblControl_0.8.1.zip](https://github.com/Denvi/grblControl/releases/download/v0.8.1/grblControl_0.8.1.zip)
* Linux: [grblControl_0.8.1.tar.gz](https://github.com/Denvi/grblControl/releases/download/v0.8.1/grblControl_0.8.1.tar.gz)

Translations will be available from here: [translations](https://github.com/Denvi/grblControl/tree/0.8/translations)

Previous versions:

0.8:
* Windows: [grblControl_0.8.zip](https://github.com/Denvi/grblControl/releases/download/v0.8/grblControl_0.8.zip)
* Linux: [grblControl_0.8.tar.gz](https://github.com/Denvi/grblControl/releases/download/v0.8/grblControl_0.8.tar.gz)

0.7:
* Windows: [grblControl_0.7.zip](https://github.com/Denvi/grblControl/releases/download/0.7/grblControl_0.7.zip)
* Linux: [grblControl_0.7.tar.gz](https://github.com/Denvi/grblControl/releases/download/0.7/grblControl_0.7.tar.gz)

0.6:
* Windows: [grblControl_0.6.zip](https://github.com/Denvi/grblControl/releases/download/0.6/grblControl_0.6.zip)
* Linux: [grblControl_0.6.tar.gz](https://github.com/Denvi/grblControl/releases/download/0.6/grblControl_0.6.tar.gz)

0.5.2:
* Windows 7: [grblControl_0.5.2.zip](https://github.com/Denvi/grblControl/releases/download/0.5.2/grblControl_0.5.2.zip)
* Windows XP: [grblControl_0.5.2_xp.zip](https://github.com/Denvi/grblControl/releases/download/0.5.2/grblControl_0.5.2_xp.zip)
* Linux: [grblControl_0.5.2.tar.gz](https://github.com/Denvi/grblControl/releases/download/0.5.2/grblControl_0.5.2.tar.gz)


Version 0.7 release:
--------------------
* Drag & Drop mechanism support added. You can drop files & plain text to main program window to open them.
* "Abort" button added. File transfer can be interrupted without loss of work coordinates offsets now.
* M2, M30, M18, M19 commands support added.
* French translation added.
* Some bugs fixed.

Version 0.6 release:
--------------------
* Improved visualizer performance.
* Some appearance settings added.

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
