Candle
-----------
GRBL controller application with G-Code visualizer written in Qt.

![screenshot](/screenshots/screenshot_main_window.png)

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

Downloads
----------
Latest release versions:

* [Version 10.10 release](https://github.com/Denvi/Candle/releases/tag/v10.10)

Nightly build versions:

[![Nightly / Windows (x64)](https://github.com/Denvi/Candle/actions/workflows/nightly-windows.yml/badge.svg)](https://github.com/Denvi/Candle/actions/workflows/nightly-windows.yml)

* [Nightly](https://github.com/Denvi/Candle/releases/tag/nightly)

Previous versions:

For GRBL v1.1 firmware

* Windows: [candle_1.1.7.zip](https://github.com/Denvi/Candle/releases/download/v1.1/Candle_1.1.7.zip)
* Linux: [candle_1.1.7.tar.gz](https://github.com/Denvi/Candle/releases/download/v1.1/Candle_1.1.7.tar.gz)

For GRBL v0.9 and below

* Windows: [candle_1.0.11.zip](https://github.com/Denvi/Candle/releases/download/v1.0/Candle_1.0.11.zip)
* Linux: [candle_1.0.11.tar.gz](https://github.com/Denvi/Candle/releases/download/v1.0/Candle_1.0.11.tar.gz)

Build instructions (windows)
------------------

* Install cmake
* Install vcpkg

```
git clone https://github.com/microsoft/vcpkg.git
vcpkg\bootstrap-vcpkg.bat
```

* Set environment variable

```
CMAKE_TOOLCHAIN_FILE={PATH_TO_VCPKG}/scripts/buildsystems/vcpkg.cmake
```

* Get Candle sources

```
git clone https://github.com/Denvi/Candle.git
cd Candle
```

* Install packages

```
vcpkg install
```

* Build and install

```
mkdir build; cd build
cmake .. -DCMAKE_INSTALL_PREFIX="$(pwd)/Candle"
cmake --build . --config=Release
cmake --install .
```

Executable can be found in `build/Candle` directory.

Build instructions (ubuntu)
------------------

* Install packages

```
sudo apt update
sudo apt install cmake build-essential qtbase5-dev libqt5serialport5-dev qtscript5-dev qttools5-dev libqt5websockets5-dev qtmultimedia5-dev
```

* Get Candle sources

```
git clone https://github.com/Denvi/Candle.git
cd Candle
```

* Build and install

```
mkdir build && cd build
cmake .. -DCMAKE_INSTALL_PREFIX="~/programs/Candle"
cmake --build . --config=Release
cmake --install .
```

Executable can be found in `~/programs/Candle` directory.

Before creating new issue
------
Candle works with CNC controlled by GRBL firmware, many problems can be solved by using proper version of GRBL, using proper configuration.

Please read GRBL wiki: 
- GRBL v0.9-: https://github.com/grbl/grbl/wiki
- GRBL v1.1: https://github.com/gnea/grbl/wiki
