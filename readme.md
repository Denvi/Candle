Candle
-----------
GRBL controller application with G-Code visualizer written in Qt.

Supported functions:
* Controlling GRBL-based cnc-machine via console commands, buttons on form, numpad.
* Monitoring cnc-machine state.
* Loading, editing, saving and sending of G-code files to cnc-machine.
* Visualizing G-code files.

Version 1.1 pre-release:
--------------------

* Moving to Grbl v1.1 firmware

Downloads:
----------
* Windows: [candle_1.1.5.zip](https://github.com/Denvi/Candle/releases/download/v1.1/Candle_1.1.5.zip)
* Linux: [candle_1.1.5.tar.gz](https://github.com/Denvi/Candle/releases/download/v1.1/Candle_1.1.5.tar.gz)


Version 1.0 release:
--------------------

* Added "Grayscale segments"-option and "Raster"-mode to visualize laser jobs.
* Added "User commands"-panel.
* Significantly improved performance of:
 * File loading.
 * G-code program modification by heightmap.
 * "Autoscroll"-feature.
* Programs with about 5 million lines can be loaded now.

Downloads:
----------
* Windows: [candle_1.0.9.zip](https://github.com/Denvi/Candle/releases/download/v1.0/Candle_1.0.9.zip)
* Linux: [candle_1.0.9.tar.gz](https://github.com/Denvi/Candle/releases/download/v1.0/Candle_1.0.9.tar.gz)

Build requirements:
------------------
Qt 5.4.2 with MinGW/GCC compiler

Previous versions:
-----------------
0.9
* Windows: [candle_0.9.zip](https://github.com/Denvi/Candle/releases/download/v0.9/Candle_0.9.zip)
* Linux: [candle_0.9.tar.gz](https://github.com/Denvi/Candle/releases/download/v0.9/Candle_0.9.tar.gz)

0.8.4
* Windows: [grblControl_0.8.4.zip](https://github.com/Denvi/grblControl/releases/download/v0.8.4/grblControl_0.8.4.zip)
* Linux: [grblControl_0.8.4.tar.gz](https://github.com/Denvi/grblControl/releases/download/v0.8.4/grblControl_0.8.4.tar.gz)

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


Version 0.9 release:
--------------------
* "Restore origin" function has "move tool in plane/space" setting now.
* "Safe position" function can be customized with command list.
* Visualizer works with OpenGL/Angle/Software renderer.
* Some bugs fixed.

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

--------------------
Support the "grblControl" project. If you'd like to donate, all proceeds will be used to help fund supporting hardware and testing equipment. Thank you.

[![Donate](https://www.paypalobjects.com/en_US/i/btn/btn_donate_LG.gif)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=NQG6CB4VGTVZE) / [![Donate](https://www.paypalobjects.com/ru_RU/i/btn/btn_donate_LG.gif)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=6GRUNTKF2M4BU) 
