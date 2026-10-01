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
* Windows/Linux (Ubuntu)/macOS/Raspberry Pi OS (Trixie)
* CPU with SSE2 instruction set support on x86, or an ARM CPU (including Apple silicon on macOS)
* Graphics card with OpenGL 2.0 support
* 120 MB free storage space

Downloads
----------
Latest release versions:

* [Releases](https://github.com/Denvi/Candle/releases)

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

Build instructions (Windows)
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

Build instructions (Ubuntu, Raspberry Pi OS Trixie, Fedora 43)
------------------

* Install packages

For Ubuntu, Raspberry Pi OS Trixie users:

```
sudo apt update
sudo apt install cmake build-essential qtbase5-dev libqt5serialport5-dev qtscript5-dev qttools5-dev libqt5websockets5-dev qtmultimedia5-dev
```

For Fedora users:

```
sudo dnf update
sudo dnf group install development-tools
sudo dnf install cmake qt5-qtbase-devel qt5-qtserialport-devel qt5-qtscript-devel qt5-qttools-static qt5-qttools-devel qt5-qtwebsockets-devel qt5-qtmultimedia-devel
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

Build instructions (macOS, Intel and Apple silicon)
------------------

Use Xcode 16.4 with the macOS 15 SDK. Qt 5's OpenGL configuration requires
legacy AGL headers that are absent from the macOS 26 SDK. Select the developer
directory for this shell (adjust the path to your Xcode installation), then
install the build tools:

```sh
export DEVELOPER_DIR=/Applications/Xcode_16.4.app/Contents/Developer
brew install cmake ninja automake autoconf-archive pkgconf
git clone https://github.com/microsoft/vcpkg.git "$HOME/vcpkg"
"$HOME/vcpkg/bootstrap-vcpkg.sh" -disableMetrics
git clone https://github.com/Denvi/Candle.git
cd Candle
```

CMake 3.28 or newer is required to read the presets. On Apple silicon, use a
native ARM64 terminal and ARM64 Homebrew installation, then build and package:

```sh
cmake --preset osx-arm64-release
cmake --build --preset osx-arm64-release --parallel 4
cmake --install build-arm64 --config Release
build-arm64/vcpkg_installed/arm64-osx-dynamic-release/tools/qt5/bin/macdeployqt build-arm64/Candle/Candle.app
find build-arm64/Candle/Candle.app -type f ! -path '*/Contents/MacOS/candle' -print0 | while IFS= read -r -d '' binary; do
    if file "$binary" | grep -q 'Mach-O'; then
        codesign --force --sign - "$binary"
    fi
done
codesign --force --deep --sign - build-arm64/Candle/Candle.app
codesign --verify --deep --strict build-arm64/Candle/Candle.app
open build-arm64/Candle/Candle.app
```

The preset builds Qt 5 and its dependencies with vcpkg; the first build can take
some time. If vcpkg is elsewhere, add
`-DCMAKE_TOOLCHAIN_FILE=/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake` to the
configure command. On an Intel Mac, replace `arm64` with `x64` in the preset and
triplet names, and replace `build-arm64` with `build` in the paths above.

The **Release / Mac (x64, ARM64)** workflow produces separate
`candle-<version>-macos-x64.dmg` and `candle-<version>-macos-arm64.dmg` artifacts.
These builds are ad-hoc signed, not notarized with an Apple Developer identity.

Before creating new issue
------
Candle works with CNC controlled by GRBL firmware, many problems can be solved by using proper version of GRBL, using proper configuration.

Please read GRBL wiki: 
- GRBL v0.9-: https://github.com/grbl/grbl/wiki
- GRBL v1.1: https://github.com/gnea/grbl/wiki
