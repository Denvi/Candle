G-Pilot (formerly Candle)
-----------

What G stands for?

- G-code Pilot: G-code is a programming language used to control CNC machines, so "G-Pilot" may suggest that the program is used for piloting or controlling using G-code.
- Guided Pilot: "G-Pilot" may also suggest that the program provides guidance or leads the user through processes related to CNC machining, similar to how a pilot guides an airplane.
- Global Pilot: This may suggest that the program offers solutions on a global scale, able to handle various types of CNC machines and be a versatile tool for controlling them.
- Genius Pilot: "G-Pilot" may suggest that the program is smart or advanced, similar to a pilot with high piloting skills.
- Graphical Pilot: If the program offers a graphical interface for controlling CNC machines, the name "G-Pilot" may suggest that it is a graphics-based tool.

*This fork is based on the `experimental` branch. The main goal is to add joystick/joypad support. Other than that, I'm making improvements/bugfixes at my discretion.*

*Any help is welcome!*

What is G-Pilot?
-----------

GRBL controller application with G-Code visualizer written in Qt.

Supported functions:
* Controlling GRBL-based cnc-machine via console commands, buttons on form, numpad.
* Monitoring cnc-machine state.
* Loading, editing, saving and sending of G-code files to cnc-machine.
* Visualizing G-code files.
* Joystick/Joypad/Controller support.

System requirements for running "G-Pilot":
-------------------
* Windows/Linux x86(not tested att all!)
* CPU with SSE2 instruction set support
* Graphics card with OpenGL 2.0 support
* 120 MB free storage space

Build requirements:
------------------
Qt 5.12.12 with MinGW/GCC 64bit compiler

Downloads:
----------
No new releases yet. Sorry!

Older versions:

For GRBL v1.1 firmware

* Windows: [candle_1.1.7.zip](https://github.com/Denvi/Candle/releases/download/v1.1/Candle_1.1.7.zip)
* Linux: [candle_1.1.7.tar.gz](https://github.com/Denvi/Candle/releases/download/v1.1/Candle_1.1.7.tar.gz)

(for GRBL v0.9 and below use Candle 1.0)

"G-Pilot" main window:

![screenshot](/screenshots/screenshot_main.png)

Technical information for my use:
---------------------------------

To check .a and .dll versions I used objdump and readelf

SFML-2.6.1 compiled from sources. CMake was needed and the rest
happens in QTCreator 12. joystickplugin is created and SFML-2.6.1-Released.