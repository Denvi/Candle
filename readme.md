Candle
-----------
GRBL controller application with G-Code visualizer written in Qt.

Supported functions:
* Controlling GRBL-based cnc-machine via console commands, buttons on form, numpad.
* Monitoring cnc-machine state.
* Loading, editing, saving and sending of G-code files to cnc-machine.
* Visualizing G-code files.

System requirements for running "Candle":
-------------------
* Windows/Linux x86
* CPU with SSE2 instruction set support
* Graphics card with OpenGL 2.0 support
* 120 MB free storage space

Build requirements:
------------------

Qt 5.4.2 with MinGW/GCC compiler

### Linux

Also install [GLib](https://gitlab.gnome.org/GNOME/glib) and [QT5SerialPort](https://wiki.qt.io/Qt_Serial_Port).

On Ubuntu for example run:

```bash
sudo apt update && sudo apt install libglib2.0-0 libqt5serialport5-dev
```

Downloads:
----------
Experimental versions:

* [Version 1.2b release](https://github.com/Denvi/Candle/releases/tag/v1.2b)


For GRBL v1.1 firmware

* Windows: [candle_1.1.7.zip](https://github.com/Denvi/Candle/releases/download/v1.1/Candle_1.1.7.zip)
* Linux: [candle_1.1.7.tar.gz](https://github.com/Denvi/Candle/releases/download/v1.1/Candle_1.1.7.tar.gz)

(for GRBL v0.9 and below use Candle 1.0)

Before creating new issue:
------
Candle works with CNC controlled by GRBL firmware, many problems can be solved by using proper version of GRBL, using proper configuration.

Please read GRBL wiki:
- GRBL v0.9-: https://github.com/grbl/grbl/wiki
- GRBL v1.1: https://github.com/gnea/grbl/wiki

"Candle" main window:
![screenshot](/screenshots/screenshot_heightmap_original.png)
