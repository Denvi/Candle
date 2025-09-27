<style type="text/css" rel="stylesheet">
img[src*='#center'] {
    display: block;
    margin: auto;
}
.center {
    text-align: center;
}
table {
    width: 100%;
}
</style>

# Program "Candle"

[1 Purpose of the program](#1-purpose-of-the-program)  
[2 Program requirements](#2-program-requirements)  
[2.1 Hardware requirements](#21-hardware-requirements)  
[2.2 Software requirements](#22-software-requirements)  
[3 Program execution](#3-program-execution)  
[3.1 Installation](#31-installation)  
[3.2 Running](#32-running)  
[3.3 Main window](#33-main-window)  
[3.3.1 Main menu](#331-main-menu)  
[3.3.2 Windows](#332-windows)  
[3.3.2.1 Window "G-code program"](#3321-window-g-code-program)  
[3.3.2.2 Window "Visualizer"](#3322-window-visualizer)  
[3.3.2.3 Window "Camera"](#3323-window-camera)  
[3.3.2.4 Window "Console"](#3324-window-console)  
[3.3.2.5 Windows "Device", "Modification", "User"](#3325-windows-device-modification-user)  
[3.3.3 Instrument panels](#333-instrument-panels)  
[3.3.3.1 Panel "State"](#3331-panel-state)  
[3.3.3.2 Panel "Control"](#3332-panel-control)  
[3.3.3.3 Panel "Coordinate system"](#3333-panel-coordinate-system)  
[3.3.3.4 Panel "Spindle"](#3334-panel-spindle)  
[3.3.3.5 Panel "Jog"](#3335-panel-jog)  
[3.3.3.6 Panel "Overriding"](#3336-panel-overriding)  
[3.3.3.7 Panel "Heightmap"](#3337-panel-heightmap)  
[3.3.3.8 Panel "User commands"](#3338-panel-user-commands)  
[3.4 Settings window](#34-settings-window)  
[3.5 Preparing the program for operation](#35-preparing-the-program-for-operation)  
[3.6 Loading the control program](#36-loading-the-control-program)  
[3.7 Creating a height map](#37-creating-a-height-map)  
[3.8 Executing the control program](#38-executing-the-control-program)  
[3.9 Shutting down the program](#39-shutting-down-the-program)  
[4 Operator messages](#4-operator-messages)  
[5 Extension development](#5-extension-development)  
[5.1 Extension configuration file](#51-extension-configuration-file)  
[5.2 Script file](#52-script-file)  
[5.3 Translation file](#53-translation-file)  
[Appendix A: Controller settings](#appendix-a-controller-settings)  
[Appendix B: Controller settings (grblHAL)](#appendix-b-controller-settings-grblhal)  
[Appendix C: Controller errors](#appendix-c-controller-errors)  
[Appendix D: G-code command table](#appendix-d-g-code-command-table)  


# 1 Purpose of the program

The “Candle” program (hereinafter referred to as the *program*) is intended for controlling CNC machines equipped with a GRBL controller using a PC.

It allows operation of 3‑axis milling machines and laser plotters.

**Main functions of the program**

- Loading, editing, saving control programs (hereinafter – CP).  
- Visualizing CP.  
- Scanning a surface roughness map, correcting CP according to the specified map.  
- Transmitting CP to CNC.  
- Displaying CNC status.  
- Manual control of CNC.

# 2 Program requirements

## 2.1 Hardware requirements  

For proper operation the PC must have the following characteristics:

* processor supporting the SSE2 instruction set;  
* graphics adapter supporting OpenGL 2.0 or higher;  
* display resolution 1280×720;  
* an available USB or RS‑232 port for connecting the PC to the CNC controller;  
* at least 20 MB of free storage space.

## 2.2 Software requirements  

The program requires a Windows 7 (or newer) operating system, with an OpenGL driver installed and, when the CNC is connected via USB, a USB‑UART converter driver.

# 3 Program execution

## 3.1 Installation  

The program is distributed as an archive:

* `candle_v.v.v_x86.zip` for 32‑bit processors;  
* `candle_v.v.v_x64.zip` for 64‑bit processors, where **v.v.v** denotes the version number.

To install, extract the archive into a working folder (e.g., `D:\`). A directory named `Candle` containing all necessary files will be created.

After extraction, create a shortcut to the executable `D:\Candle\candle.exe` for quick launch.

## 3.2 Running  

Run the program by executing `candle.exe` from the installation folder or via the shortcut created earlier.

## 3.3 Main window  

When launched, the main window should appear on the display as shown in Figure 1.

![Main window of the program](images_en/mainwindow.png#center)
<p class="center">Figure 1 – Main window of the program</p>

The main window consists of a top menu, a set of windows, and instrument panels:

* **“G‑code program”** – primary window showing the list of commands in the current CP.  
* **“Visualizer”** – graphical representation of CP.  
* **“Camera”** – camera image.  
* **“Console”** – window for sending commands to the GRBL CNC controller and displaying responses.  
* **“Device”** – window with panels for controlling the CNC.  
* **“Modification”** – window with panels for correcting CP.  
* **“User”** – window with user‑defined panels.

Each window has a title area containing the window name, “Detach”, and “Close” buttons; the content area holds input elements, information displays, and toolbars.

All windows except the “G‑code program” can be moved by dragging the left mouse button (LMB) on their title bar. While moving, the main window’s layout updates dynamically to indicate the future position of the dragged window.

Windows may be detached from the main window by clicking the “Detach” button in the title bar and closed via the “Close” button. Detached windows can be re‑attached to the main window by dragging their title; closed windows can be reopened through the corresponding item in the main menu **View → Windows**.

Window sizes are changed by pressing LMB on the border of a window and dragging it in the desired direction.

## 3.3.1 Main menu

The program’s main menu gives access to its core functions.  
It is divided into groups and items, whose descriptions are shown in Table 1.

| Group | Item          | Description                                          |
|-------|---------------|------------------------------------------------------|
| File  | New           | Create a new CP                                     |
|       | Open          | Load a CP file                                      |
|       | Recent files  | Load one of the most recent CP files                |
|       | Save          | Write changes to the current CP file                 |
|       | Save As       | Write the CP to a specified file                     |
|       | Exit          | Exit the program                                    |
| View  | Windows       | Choose which windows are displayed                  |
|       | Panels        | Choose which panels are displayed                   |
|       | Lock windows  | Disable/enable moving of windows                    |
|       | Lock panels   | Disable/enable moving of panels                      |
| Service | Settings     | Open the program’s settings window                  |
| Help  | Documentation | Open the program documentation                       |
|       | About program | Open the dialog with information about the program  |

## 3.3.2 Windows

### 3.3.2.1 Window “G-code program”

The current CP is displayed in the **“G‑code program”** window shown in Figure 2.

![Window “G‑code program”](images_en/g-codeprogram.png#center)
<p class="center">Figure 2 – “G‑code program” window</p>

Each row of the table corresponds to a line of the CP and contains the following columns:

* **“#”** – CP line number.  
* **“Command”** – The command itself.  
* **“State”** – Current state of the command: “In queue”, “Sent”, “Processed”, or “Skipped”.  
* **“Response”** – Response from the GRBL controller to the sent command.

The CP can be edited; the following functions are supported:

| Function | How it works |
|----------|--------------|
| Change a command in a selected row | Double‑click the cell in the *Command* column or press `<F2>` while the cell is highlighted. Confirm with `<Enter>` or `<Tab>`, cancel with `<Esc>`. |
| Add new rows | Select the row before which the new one should be inserted, then choose **“Insert line”** from the context menu (right‑click in the table) or press the `<Ins>` key. |
| Delete selected rows | Use **“Delete lines”** from the context menu or press `<Del>`. |

Below the table are controls for loading and sending CP to the CNC controller:

| Button   | Action |
|----------|--------|
| **Open** | Opens a file‑selection dialog; upon confirmation, loads the chosen CP. |
| **Reset** | Clears all selections in the table, sets the first line as current, and resets command states. |
| **Send**  | Starts the transmission of the CP to the CNC controller. |
| **Pause** | Pauses the transmission process. |
| **Stop**  | Stops the transmission. |

> **Note** – When “Pause” or “Stop” is activated, the actual CNC halt occurs only after the controller’s command input buffer has been emptied. For an immediate stop use the **“Hold”** and **“Reset”** commands from the *Control* panel.

There is a **"Scroll"** checkbox to the left of these buttons that enables automatic scrolling of the table during CP transmission. If the CP is actively being sent while the user manually scrolls, this checkbox resets automatically.

#### 3.3.2.2 Window “Visualizer”

The graphical representation of the CP is displayed in the window **"Visualizer"** (Figure 3).

![Window “Visualizer”](images_en/visualizer.png#center)
<p class="center">Figure 3 – Window “Visualizer”</p>

In this window five functional areas can be identified:

- **Central or main area**, where the CP tool trajectory is rendered as a three‑dimensional (3D) projection.  
- **Controller status** in the upper‑left corner.  
- **View‑control buttons** in the upper‑right corner.  
- **Processing limits information** in the lower‑left corner.  
- **Auxiliary information** in the lower‑right corner.

The CP tool trajectory is represented by a set of line segments:

- Solid black lines denote portions of linear and circular interpolation.  
- Dashed black lines indicate accelerated moves.  
- Red lines represent vertical movements.

When the CP is sent to the CNC controller, some segments change color according to the following rules: the part already processed by the CNC is colored grey; the portion that has been transmitted to the CNC is colored violet.

Three circle markers are overlaid on the trajectory:

- **Red marker** – start of the trajectory.  
- **Green marker** – end of the trajectory.  
- **Purple marker** – segment corresponding to the command highlighted in the "G‑code program" window table.

In the main area the origin is shown as a red rectangle in the X–Y plane, with axes colored: X – red, Y – green, Z – blue. A conditional representation of the tool appears as an orange wireframe model.

**Navigation in the main area**

- Rotate the 3D projection by holding the left‑mouse button (LMB) on the main area and moving the cursor, or click one of the view buttons in the upper‑right corner (“Top”, “Front”, “Left”, “Isometric”).  
- Move the projection within the area by pressing LMB while holding the `<Shift>` key and dragging.  
- Scale the projection using the mouse wheel or by clicking the **Fit** button in the upper‑right corner.

In the upper‑left corner the current CNC controller state is displayed: the interpreter status string, the current feed and spindle speed values, and the states of CNC components (spindle, cooling system).

The status string has the form:

<p class="center">[GC:G1 G54 G17 G21 G90 G94 M3 M9 T0 F75 S8000]</p>

It shows the interpreter’s current mode for all 12 modal groups, tool number, feed rate and spindle speed. The groups and possible modes are listed in Table 2.

### Table 2 – CNC controller interpreter operating modes

| Modal group | Modes |
|-------------|-------|
| **Movement** | G0, G1, G2, G3, G38.2, G38.3, G38.4, G38.5, G80 |
| **Coordinate system** | G54, G55, G56, G57, G58, G59 |
| **Workplane** | G17, G18, G19 |
| **Distance mode** | G90, G91 |
| **IJK circular interpolation** | G91.1 |
| **Feed rate** | G93, G94 |
| **Units of measurement** | G20, G21 |
| **Tool radius compensation** | G40 |
| **Tool length compensation** | G43.1, G49 |
| **Program motion control** | M0, M1, M2, M30 |
| **Spindle state** | M3, M4, M5 |
| **Cooling system state** | M7, M8, M9 |

The CNC component status string appears as:

<p class="center">AS: SFM</p>

- **S** indicates spindle rotation clockwise; it is replaced by **C** when rotating counter‑clockwise and omitted when the spindle stops.  
- **F** appears when water cooling is active; **M** denotes air cooling.

The CP processing limits shown in the lower‑left corner list the minimum and maximum coordinates for each axis, as well as the dimensions of the machining zone (excluding tool diameter).

In the lower‑right corner, the current operating time under the loaded CP is displayed, along with an estimated total runtime based on the CP.

Below this area a line presents command‑queue information: the total number of commands sent and currently being processed by the CNC controller; the count of processed commands; and the number of injected commands (commands sent in addition to the CP) present in the queue.

The same section also shows auxiliary data: the total number of vertices forming the 3D projection, and the frames‑per‑second rate at which the projection is being built.

#### 3.3.2.3 Window “Camera”

The image from the camera connected to the PC is displayed in the **“Camera”** window (Figure 4).

![Window “Camera”](images_en/camera.png#center)
<p class="center">Figure 4 – Camera window</p>

View navigation inside the window is performed by holding the left mouse button (LMB) and moving the cursor in the desired direction; zooming is controlled with the mouse wheel.

The window contains reticle elements: a vertical line, a horizontal line, and a circle whose centre lies at the intersection of the two lines. The intersection point can be moved by pressing LMB while holding the **Shift** key on the keyboard and dragging the cursor in the desired direction.

Parameters such as camera image resolution, color and thickness of the reticle elements are available in the program’s settings window.

#### 3.3.2.4 Window “Console”

For manual CNC control, as well as for configuring and displaying controller status information, the **“Console”** window is provided (Figure 5).

![Window “Console”](images_en/console.png#center)
<p class="center">Figure 5 – Console window</p>

At the bottom of the window there is a command‑entry field and two buttons: **Send Command** and **Clear Console**. At the top a multiline output area shows replies from the controller.

To send a command to the CNC controller, type it into the entry field and press the **Enter** key or click **Send Command**. After the controller processes the command, the command and its reply are displayed above in the following format:

<p class="center">Command < Response</p>

If the program setting *“Show UI commands”* is enabled, all commands sent to the controller by toolbar controls will appear in the output area. When *“Show G‑code program commands”* is turned on, every command from the CP that is transmitted to the controller will also be shown.

The output field can be cleared by clicking **Clear Console**.

#### 3.3.2.5 Windows “Device”, “Modification”, “User”

Instrument panels containing controls and status information of the CNC are located in the **“Device”**, **“Modification”**, and **“User”** windows.

The name of each window indicates the functional purpose of the panels it contains, but this does not restrict their composition – all panels can be freely moved both within a given window and between windows.

Movement is performed by dragging a panel’s title bar with LMB. While dragging, the window shows the future position of the panel as a blue line.

Most instrument panels are collapsible to save screen space. In the expanded state a panel’s header displays a “‑” sign to its left; in the collapsed state it shows a “≡”. Panels can be collapsed or expanded by clicking their title bar with LMB.

Header text is normally black, but when critical functions of a panel are activated it turns red.

At program startup some panels appear inactive and become active only after the CNC is connected to the PC.

## 3.3.3 Instrument panels

### 3.3.3.1 Panel “State”

The **State** panel (Figure 6) displays the current work‑ and machine‑coordinates, as well as the operating mode of the CNC controller.  
Coordinates are shown in output fields arranged horizontally in the order: **X, Y, Z**.

#### Controller operating modes (field *“Status”*)

| Mode | Description |
|------|-------------|
| **Idle** | The controller is ready to receive commands. |
| **Alarm** | An emergency state. |
| **Run** | Executing a control program (CP). |
| **Home** | Searching for the home position. |
| **Hold**  | Motion is paused, awaiting further continue/reset commands. |
| **Check**  | Incoming G‑code is interpreted without actual tool movement. |
| **Door**  | Door‑sensor triggered mode. |
| **Jog**  | Executing special jogging commands. |
| **Sleep** | Low‑power standby mode. |

In the same field, states that are not related to the controller’s operating mode are shown:

- **Not connected** – when the serial port cannot be opened for the CNC.
- **Port opened** – the serial port is open, but no communication with the GRBL controller has been established.

The background color of the *Status* field may change depending on the state.

![Panel “State”](images_en/status.png#center)
<p class="center">Figure 6 – Panel “State”</p>

### 3.3.3.2 Panel “Control”

The **Control** panel contains a set of buttons that send basic GRBL commands (Figure 7).  
Table 3 lists the button, the command it sends (command code), and its description in the order they appear on the panel – left to right, top to bottom.

![Panel “Control”](images_en/control.png#center)
<p class="center">Figure 7 – Panel “Control”</p>

**Table 3 – Control Panel Buttons**

| Button | Command | Description |
|--------|---------|-------------|
| **Home** | `$H` | Search for the home position. |
| **Hold** | `!` or `~` | Stop current motion (`!`) or resume movement (`~`). |
| **Reset** | `0x18` | Software reset of the controller. |
| **Unlock** | `$X` | Force unlock from alarm state. |
| **Check** | `$C` or `0x18` | Enable (`$C`) / disable (`0x18`) CP check mode. |
| **Sleep** | `$SLP` | Put the controller into low‑power mode. |
| **Door** | `0x84` | Force the controller into door‑triggered mode. |
| **Flood** | `0xA0` | Toggle water cooling system on/off. |

> Note: When disabling CP check mode, a software reset command is sent followed by restoration of the controller state and work‑coordinate offsets.

### 3.3.3.3 Panel “Coordinate System”

Figure 8 shows the panel for managing the CNC coordinate system (CS).

![Panel “Coordinate System”](images_en/coordinatesystem.png#center)
<p class="center">Figure 8 – Panel “Coordinate System”</p>

The upper part of the panel displays the offsets for the active CS on axes **X, Y** and **Z**.  
Below are buttons to select a CS and to reset the current coordinates on one or all axes for the active CS.

### 3.3.3.4 Panel “Spindle”

On the spindle‑control panel (Figure 9) you will find:

- An input field for setting / displaying the desired spindle speed.
- A horizontal slider for adjusting the spindle speed.
- A button to turn on/off the spindle.

![Panel “Spindle”](images_en/spindle.png#center)
<p class="center">Figure 9 – Panel “Spindle”</p>

The spindle speed can be set either by typing a number into the field or by using the slider.  
Text in the input field may appear **black** if the current spindle speed matches the desired value, or **red** otherwise.

The slider’s knob is a gray circle with a dark outline; the marker – a lighter‑colored circle indicating the current speed.

During CP transmission to the controller the spindle speed can be altered via the above controls using injected G‑code `S`, or through the “Correction” panel’s override function.  
Spindle on/off during transmission is possible only while the controller is in *Hold* mode.

### 3.3.3.5 Panel “Jog”

The **Jog** panel contains controls for moving the CNC tool:

- Arrow buttons for axes **X** (left/right), **Y** (up/down) and **Z** (up/down on the right side).
- A central **Stop** button that force‑stops motion.
- A drop‑down list **Step**, where you can set the jog step size.
- A drop‑down list **Feed**, selecting the jog feed rate.
- A checkbox **Keyboard Control** to enable keyboard jogging from the PC.

![Panel “Jogging”](images_en/jogging.png#center)
<p class="center">Figure 10 – Panel “Jog”</p>

The *Step* and *Feed* lists provide predefined values but allow entry of arbitrary numbers.  
Values entered right before **Keyboard Control** is enabled are remembered and can be reused on subsequent program launches.

Each button, as well as changing the *Step* and *Feed* values, may have hotkeys defined in the program’s **Settings** window.  Keyboard control must be turned on for these shortcuts to work.

### 3.3.3.6 Panel “Overriding”

Figure 11 shows the **Overriding** panel.  
It contains controls similar to those on the spindle panel but overrides feed rate, idle speed and spindle speed during CP transmission.

The only difference is that the spindle button has been replaced by a corresponding checkbox.

![Panel “Overriding”](images_en/overriding.png#center)
<p class="center">Figure 11 – Panel “Overriding”</p>

### 3.3.3.7 Panel “Heightmap”

The **Heightmap** panel (Figure 12) is responsible for creating, loading, scanning a surface roughness map and subsequently correcting the CP to level the part’s curvature when machining with a CNC.  
This feature is useful for PCB milling and engraving.

![Panel “Height Map”](images_en/heightmap.png#center)
<p class="center">Figure 12 – Panel “Heightmap”</p>

The panel provides controls to:

- Create, load and enable the height‑map mode.
- Define a rectangular map area.
- Set the number of probe points along **X** and **Y** axes.
- Specify the working height above the surface and probing depth.
- Set feed rate.
- Choose grid line count for CP partitioning on **X** and **Y**.

CP correction based on the active height map is performed by enabling the **Use heightmap** checkbox.

More detailed information on using the height‑map feature can be found in § [3.7 “Creating a Height Map”](#37-creating-a-height-map) of this manual.

### 3.3.3.8 Panel “User commands”

To extend program functionality for CNC control, a **User commands** panel is provided (Figure 13).  
Each button on the panel sends pre‑defined commands to the GRBL controller when pressed.

![Panel “User commands”](images_en/usercommands.png#center)
<p class="center">Figure 13 – Panel “User commands”</p>

Command configuration occurs in the program’s **Settings** window.  Within the *User commands* group, a table lists each command and allows you to:

- Add, delete or reorder commands.
- Set a tooltip shown when hovering over the button.
- Assign an icon to the button.
- Define one or more G‑code commands that are sent to the controller upon clicking the button.

The program includes a limited set of icons; additional user‑defined icons can be added by placing image files in `candleplugins/usercommands/images` inside the installation folder.

A command may consist of a single G‑code line or multiple lines, one per cell row under **G‑code**.  
Within G‑code commands you can embed JavaScript snippets enclosed in braces `{}`. For example:

- Reset work‑coordinate X and store the offset in variable `storedG92x`

```javascript
G92X0
{var storedG92x = vars.G92x}
```

- Restore X offset after a controller reset

```javascript
G92X{vars.Mx - storedG92x - vars.x}
```

- Launch the Notepad application

```javascript
{script.importExtension("qt.core")}
{var p = new QProcess()}
{p.start("notepad", [])}
```

For a full discussion of using JavaScript within the program, see § [5 Extension development](#5-extension-development) in this manual.

## 3.4 Settings window

The program settings are available in the **Settings** dialog (Figure 14), invoked by selecting “Settings” from the **Service** menu of the application.

![Settings window](images_en/settings.png#center)
<p class="center">Figure 14 – Settings window</p>

The dialog contains three areas: a left panel with a list of setting groups, a right panel with controls for the selected group, and a bottom bar with buttons to reset settings to defaults, confirm changes, or cancel them.

Below is information about all available program settings: group, parameter, description, permissible values, and default value.

| Group                      | Parameter                                 | Description                                                                                                   | Permissible values                                              | Default value         |
|----------------------------|-------------------------------------------|---------------------------------------------------------------------------------------------------------------|-----------------------------------------------------------------|-----------------------|
| **Connection**             | **Port**                                  | Serial port used to connect to the CNC controller                                                             | Path to device                                                | None                  |
|                            | **Baud**                                 | Baud rate for serial communication                                                                          | 9600, 14400, 19200, 38400, 57600, 115200, any integer value      | 115200                |
|                            | **Status query period**                        | Time between status requests to the controller                                                              | 10–9999 ms                                                   | 100                   |
| **Machine information**    | **Spindle speed min.**                    | Minimum spindle rotation speed (used by the “Spindle” panel)                                                  | 0–99 999 RPM                                                 | 0                     |
|                            | **Spindle speed max.**                    | Maximum spindle rotation speed                                                                               | 0–99 999 RPM                                                 | 10 000                |
|                            | **Laser power min.**                      | Minimum laser power (used for half‑tone raster visualisation of CP)                                            | 0–99 999                                                    | 0                     |
|                            | **Laser power max.**                      | Maximum laser power                                                                                           | 0–99 999                                                    | 100                   |
| **Parser**                 | **Arc approximation segment size – by length**          | Length of segments that split arcs in CP when displayed in the “Visualizer” and during height‑map creation   | 0.1–99 mm (0 = disabled)                                     | 0.1 (disabled)       |
|                            | **Arc approximation segment size – by angle**           | Angle used to subdivide arcs in CP for the same purposes                                                     | 0–180°                                                       | 5 ° (enabled)        |
| **Sender**           | **Use program start commands**                | G‑code commands sent to the CNC controller before transmitting the CP                                       | Set of G‑code commands (JavaScript allowed)                    | None                  |
|                            | **Use program end commands**                  | G‑code commands sent after the CP has been transmitted                                                     | Same as above                                                | None                  |
|                            | **Use tool change commands**                  | G‑code commands sent when processing tool‑change instructions                                               | Same as above                                                | None                  |
|                            | **Ignore error responses**     | Flag that determines whether to abort CP transmission when the controller reports an error                   | Enabled, Disabled                                            | Disabled              |
|                            | **Automatically set parser state before sending from selected line** | Enable sending of parser‑configuration commands before transmitting the CP from a chosen line                 | Enabled, Disabled                                            | Enabled               |
|                            | **Pause sender on M6 command** | Control whether to pause CP transmission while processing tool‑change instructions                         | Enabled, Disabled                                            | Enabled               |
| **Visualizer**             | **Line width**                        | Thickness of 3D projection lines in the visualiser                                                          | 1–9                                                           | 1.5                   |
|                            | **Smoothing**                             | Enable line smoothing for the 3D projection                                                               | Enabled, Disabled                                            | Enabled               |
|                            | **MSAA**                                  | Multi‑sample anti‑aliasing for the 3D projection                                                            | Enabled, Disabled                                            | Enabled               |
|                            | **FPS lock**                            | FPS of the 3D projection rendering                                                                           | 30, 60, 120, any integer                                     | 60                    |
|                            | **V-sync**                                | Enable vertical sync                                                                                        | Enabled, Disabled                                            | Disabled              |
|                            | **Z-buffer**                          | Enable depth‑buffering for line overlap control                                                              | Enabled, Disabled                                            | Disabled              |
|                            | **Program draw mode**                        | Method of CP projection: “Vector” (lines) or “Raster” (points)                                              | Vectors, Raster                                                | Vector                |
|                            | **Simplify geometry**                     | Limit the minimum segment size when rendering the CP                                                      | Enabled, Disabled                                            | Enabled               |
|                            | **Simplify geometry – Precision**         | Minimum segment length used for simplification (0 = only segments on a single line are converted)            | 0–99 mm                                                       | 0                     |
|                            | **Grayscale segments**                     | Enable point colorization in raster rendering                                                             | Enabled, Disabled                                            | Disabled              |
|                            | **Grayscale segments – by 'S' code**        | Color points according to the ‘S’ G‑code value                                                            | Enabled, Disabled                                            | Enabled               |
|                            | **Grayscale segments – by 'Z' code**        | Color points according to the ‘Z’ G‑code value                                                            | Enabled, Disabled                                            | Disabled              |
| **Colors**                 | **Visualizer – Background**               | Background color in the “Visualizer” window                                                               | Any color                                                    | White                 |
|                            | **Visualizer – Text**                     | Text color in the “Visualizer” window                                                                     | Any color                                                    | Black                 |
|                            | **Visualizer – Tool**                     | Color of the tool model in the “Visualizer”                                                              | Any color                                                    | Orange                |
|                            | **Toolpath – Normal**                  | Color of the main trajectory paths in the CP projection                                                   | Any color                                                    | Black                 |
|                            | **Toolpath – Drawn**                | Color of parts already processed by the CNC when sending the CP                                         | Any color                                                    | Gray                  |
|                            | **Toolpath – Highlight**                | Color of lines sent to the CNC; color of the marker for the selected CP line                           | Any color                                                    | Purple                |
|                            | **Toolpath – Z-movement**              | Color of vertical trajectory moves                                                                       | Any color                                                    | Red                   |
|                            | **Toolpath – Start point**                    | Color of the start marker for the CP                                                                      | Any color                                                    | Red                   |
|                            | **Toolpath – End point**                      | Color of the end marker for the CP                                                                        | Any color                                                    | Green                 |
| **Tool model**             | **Type**                                  | Tool model type in the “Visualizer”                                                                       | Flat, Conic                                                 | Conical               |
|                            | **Angle**                                 | Cone angle of the conical tool model                                                                    | 0–180°                                                       | 15 °                  |
|                            | **Diameter**                              | Diameter of the tool model                                                                               | 0–99 mm                                                      | 3 mm                  |
|                            | **Length**                                | Length of the tool model                                                                                | 0–999 mm                                                     | 30 mm                 |
| **Shortcuts**        | –                                         | Key combinations for fast invocation of program functions                                               | Any key combination                                          | None                  |
| **Console**                | **Show G‑code program commands**          | Show G‑code commands of the CP in the “Console” during transmission to the controller                    | Enabled, Disabled                                            | Disabled              |
|                            | **Show UI commands**                   | Show commands sent via instrument panel elements                                                          | Enabled, Disabled                                            | Enabled               |
|                            | **Command auto‑completion**                 | Auto‑finish a command when entering it in the “Console” field based on previously typed text             | Enabled, Disabled                                            | Enabled               |
| **User interface**         | **Font size**                             | Size of UI font                                                                                           | 8, 9, 10, 11, 12 pt or any integer                          | 9                     |
|                            | **Language**                    | Language used for UI labels                                                                              | American English, Russian (list can be extended)               | American English      |
| **Camera**                 | **Name**                                  | Name of the camera whose image is shown in the “Camera” window                                            | List of available cameras or any custom name                  | None                  |
|                            | **Resolution**                            | Image resolution displayed from the camera                                                               | Supported resolutions list or any custom resolution           | 1280×720              |
|                            | **Position**                              | Horizontal/vertical offset of the camera image in the “Camera” window                                      | Any offset in points                                         | 0, 0                  |
|                            | **Zoom**                                 | Scaling factor for the camera image                                                                      | Any number                                                   | 1                     |
|                            | **Aim position**                    | Relative offset of targeting elements horizontally/vertically                                            | Offset between 0 and 1 in relative units                      | 0, 0                  |
|                            | **Aim size**                        | Diameter of the targeting circle                                                                        | 1–100                                                         | 20                    |
|                            | **Aim color**                       | Color of targeting elements                                                                            | Any color                                                   | Red                   |
|                            | **Aim line width**                        | Thickness of crosshair lines                                                                             | 0–100                                                         | 1                     |
| **User commands**          | –                                         | Table of commands for the “User commands” panel                                                          | Any set of commands                                          | Test commands         |

## 3.5 Preparing the program for operation

Before working with the program, perform the following steps:

- Launch the program.  
- Connect and start the CNC machine.  
- Configure the port and baud rate for connection to the CNC controller.  
- Verify the connection to the controller. If the connection is correct, the **“Status”** field in the **“State”** panel should display **“Idle”**.  
- Check the controller settings.

To verify the settings, enter the command `$$` in the input field of the **“Console”** window and send it to the controller.  
The correct operation of the program depends on the following settings (see [Appendix A: Controller settings](#appendix-a-controller-settings)):

- `$5`, `$6` affect the homing and probe functions.  
- `$10` must include the machine coordinate output in its mask, feed & speed, pin state, work coordinate offsets, overrides; a working value example is `1` (`511` for grblHAL).  
- `$22` determines whether limit switches are used during homing; a working value example is `1`.  
- `$23` sets the direction of axis movement during homing.  
- `$30`, `$31` set the spindle speed range and may correspond to the **“Spindle speed min”**, **“Spindle speed max”** settings in the program.  
- `$100`…`$102` define the actual axis travel per commanded unit.  
- `$110`…`$112` – maximum axis travel speeds.  
- `$120`…`$122` – axis acceleration values.  
- `$130`…`$132` define the work area size; used in jogging commands.

To set new values, send commands of the form `$CODE=VALUE` to the controller, e.g. `$10=1`.  
After changing controller settings, it is recommended to reset the controller by pressing the **“Reset”** button on the **“Control”** panel.

## 3.6 Loading the control program

As an example we will use the PCB track-milling G-code (see file **“level_shifter.gcode”** in folder **“doc/programexamples”**), because it touches most of the program’s features.

Load the G-code via the **“Open”** command in the **“File”** menu or by clicking the **“Open”** button in the **“G-code program”** window. After selecting the file and confirming, the **“Visualizer”** window will show the toolpath, machining boundaries, and estimated runtime.

Preparation for running the G-code includes:

- Clamping the workpiece on the table (for milling it is usually placed on a **“sacrificial”** table).  
- Homing the machine (**“Home”** button on the **“Control”** panel).  
- Installing the tool.  
- Setting the work coordinate system zero.

Use the **“Jog”** panel buttons to position the tool at the desired X and Y zero point on the workpiece, then zero the work coordinates for X and Y.

Note: you can zero the work zero either with the axis-zero buttons on the **“User Commands”** panel or on the **“Coordinate System”** panel.  
- With **“User Commands”**, work coordinates are **NOT** restored after a controller reset or emergency stop.  
- With **“Coordinate System”**, values are stored in non-volatile memory and survive power cycles.  

The user decides, but it is recommended to use the **“Coordinate System”** panel for X and Y; for Z you may use **“User Commands”**, because Z depends on the current tool length and is usually set immediately before running the G-code.

Set the Z work zero manually (as with X and Y) or by using the probe command on the **“User Commands”** panel. Connect and configure the probe according to the CNC machine manual.

## 3.7 Creating a height map

Because PCB milling is performed at depths of a few hundredths of a millimetre, it is recommended to first scan the surface irregularities and modify the original G-code accordingly.

Required steps:

- Make sure the Z work zero is on the surface of the workpiece.  
- Click the **“Create”** button on the **“Heightmap”** panel.  
- Click **“Auto”** to set the map boundaries; ensure the G-code stays within them.  
- Define the height-map reference point. You will have to re-zero Z at this exact point before running the G-code. If several G-codes are used for one workpiece, make sure this point remains probe-accessible after intermediate operations.  
- Configure the probing grid: set the number of probe points (e.g. 3 × 4), safe Z height (Zt = 5), probe depth (Zb = –1), and feed rate (F = 50).  
- Configure the interpolation grid; values should be at least 10× the number of probe points. This affects machining accuracy on the workpiece surface.  
- Press the **“Probe”** button in the **“Heightmap”** window and wait for the probing to finish.  
- If several G-codes are used for the same workpiece, save the map via **“File ▸ Save”** while the height-map editor is open. For subsequent G-codes load the saved map with the **“Open”** button on the **“Heightmap”** panel.  
- Press **“Edit”** on the **“Heightmap”** panel to exit the editor.  
- Enable the **“Use heightmap”** flag to modify the G-code.  
- Set the Z work zero for the obtained height map: raise the tool to a safe height, press **“Origin”** on the **“Heightmap”** panel to move to the reference XY point, then set Z manually or with the probe command from **“User Commands”**.

## 3.8 Executing the control program

Start execution by pressing the **“Send”** button in the **“G-code program”** window.

After clicking **“Send”**, the **“State”** panel should show **“Run”**.

When finished, a message window will appear.

During execution the following commands are available:

- **“Pause”** in the **“G-code program”** window – pauses sending G-code to the controller.  
- **“Abort”** in the same window – stops sending G-code to the controller.  
- **“Hold”** on the **“Control”** panel – instantly pauses command execution by the controller (unlike **“Pause”**). While on hold, the **“Spindle on/off”** button on the **“Spindle”** panel is also available. Resume by pressing **“Hold”** again.  
- **“Reset”** on the **“Control”** panel – instantly stops command execution and halts G-code transmission.  
- Feed-rate, rapid-traverse, and spindle-speed override via the **“Overriding”** panel.

## 3.9 Shutting down the program

To exit the program:

- Ensure no G-code is being sent to the controller.  
- Power off the machine.  
- Close the program via **“File ▸ Exit”** or any other window-manager means.

# 4 Operator Messages

During operation the program may show pop-up messages to the operator:

- End-of-program window with runtime info and an OK button.  
- G-code transmission-error window with **“Skip”** (continue) and **“Abort”** buttons.  
- Warning on attempting to close the program while G-code is still being transmitted.  
- Confirmation window when sending parser-setup commands after a long-press of the **“Send”** button in the **“G-code program”** window, if the option **“Automatically set parser state before sending from selected line”** is enabled in program settings.  
- Other auxiliary dialogs.

# 5 Extension development

The program supports extensions that add new features and UI elements.  
Each extension is a folder placed in the **candleplugins** directory of the installation folder and contains several files:

- `config.ini` – text file describing the extension.
- `script.js` – JavaScript code implementing the extension logic.
- Supporting resources (Qt Designer `.ui` files, translation files, images, etc.).

The default installation already includes three extensions:

| Extension name        | Purpose                                              |
|-----------------------|------------------------------------------------------|
| `camera`              | “Camera” panel functionality                        |
| `coordinatessytem`    | “Coordinate system” panel functionality             |
| `usercommands`        | “User commands” panel functionality                |

The set of extensions can grow over time.

## 5.1 Extension Configuration File

The configuration file must contain two text keys in the **General** group:

| Key   | Description                                    |
|-------|------------------------------------------------|
| title | Window or panel header title                   |
| name  | Unique extension identifier (no spaces)         |

Example for the *Coordinate system* plugin (`config.ini`):

```ini
[General]
title="Coordinate system"
name="CoordinateSystemPlugin"
```

## 5.2 Script File

The script must be written in **JavaScript** and implement the required functionality.  
An extension can provide UI panels for the “Device”, “Modification”, “User” windows, a dedicated window in the main program area, settings panel, or none of them.

When the main program loads an extension it calls its functions in the order listed below:

| Function             | Arguments | Return Value          | Description                                           |
|----------------------|-----------|-----------------------|-------------------------------------------------------|
| `init()`             | –         | –                     | Extension initialisation routine                     |
| `createPanelWidget()`| –         | `QWidget` object      | Create a panel widget for “Device”, “Modification” or “User” windows |
| `createWindowWidget()`| –       | `QWidget` object      | Create a standalone window in the main program area   |
| `createSettingsWidget()`| –    | `QWidget` object      | Create a settings widget (appears in the Settings dialog) |

The following global objects are available to the script.  
All names and signatures are kept identical; only the descriptions are translated.

### 5.2.1 Global objects

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
| `app.settings`      | `port`                   | Value    | –                     | –                | “Connection – Port” setting.                                                        |
|                     | `baud`                   | Value    | –                     | –                | “Connection – Baud”.                                                                |
|                     | `queryStateTime`         | Value    | –                     | –                | “Connection – Status query period”.                                                 |
|                     | `spindleSpeedMin`        | Value    | –                     | –                | “Machine information – Spindle speed min”.                                          |
|                     | `spindleSpeedMax`        | Value    | –                     | –                | “Machine information – Spindle speed max”.                                          |
|                     | `laserPowerMin`          | Value    | –                     | –                | “Machine information – Laser power min”.                                            |
|                     | `laserPowerMax`          | Value    | –                     | –                | “Machine information – Laser power max”.                                            |
|                     | `axisAEnabled`           | Value    | –                     | –                | “Machine information – Enable A-axis” setting.                                      |
|                     | `axisAX`                 | Value    | –                     | –                | “Machine information – A-axis direction – X” setting.                               |
|                     | `arcLength`              | Value    | –                     | –                | “Arc approximation segments size – by length”.                                      |
|                     | `arcDegree`              | Value    | –                     | –                | “Arc approximation segments – by angle”.                                            |
|                     | `arcDegreeMode`          | Value    | –                     | –                | Arc approximation segments ‑ by angle mode toggle.                                  |
|                     | `startCommands`          | Value    | –                     | –                | “Sender – Use program start commands”.                                              |
|                     | `endCommands`            | Value    | –                     | –                | “Sender – Use program end commands”.                                                |
|                     | `toolChangeCommands`     | Value    | –                     | –                | “Sender – Use tool change commands”.                                                |
|                     | `ignoreErrors`           | Value    | –                     | –                | “Sender – Ignore error responses”.                                                  |
|                     | `autoLine`               | Value    | –                     | –                | “Sender – Automatically set parser state before sending from selected line”.        |
|                     | `pauseToolChange`        | Value    | –                     | –                | “Sender – Pause sender on M6 command.                                               |
|                     | `lineWidth`              | Value    | –                     | –                | “Visualizer – Line width”.                                                          |
|                     | `antialiasing`           | Value    | –                     | –                | “Visualizer – Smoothing”.                                                           |
|                     | `msaa`                   | Value    | –                     | –                | “Visualizer – MSAA”.                                                                |
|                     | `fps`                    | Value    | –                     | –                | “Visualizer – FPS lock”.                                                            |
|                     | `vsync`                  | Value    | –                     | –                | “Visualizer – V‑Sync”.                                                              |
|                     | `zBuffer`                | Value    | –                     | –                | “Visualizer – Z‑buffer”.                                                            |
|                     | `drawModeVectors`        | Value    | –                     | –                | “Visualizer – Program draw mode” (0 raster, 1 vectors).                             |
|                     | `simplify`               | Value    | –                     | –                | “Visualizer – Simplify geometry”.                                                   |
|                     | `simplifyPrecision`      | Value    | –                     | –                | “Visualizer – Simplify geometry - Precision”.                                       |
|                     | `grayscaleSegments`      | Value    | –                     | –                | “Visualizer – Grayscale segments”.                                                  |
|                     | `grayscaleSCode`         | Value    | –                     | –                | “Visualizer – Grayscale segments - By 'S'‑code”.                                    |
|                     | `toolType`               | Value    | –                     | –                | “Tool model – Type” (0 flat, 1 conic).                                              |
|                     | `toolAngle`              | Value    | –                     | –                | “Tool model – Angle”.                                                               |
|                     | `toolDiameter`           | Value    | –                     | –                | “Tool model – Diameter”.                                                            |
|                     | `toolLength`             | Value    | –                     | –                | “Tool model – Length”.                                                              |
|                     | `showProgramCommands`    | Value    | –                     | –                | “Console – Show G‑code program commands”.                                           |
|                     | `showUICommands`         | Value    | –                     | –                | “Console – Show UI commands”.                                                       |
|                     | `autoCompletion`         | Value    | –                     | –                | “Console – Command auto‑completion”.                                                |
|                     | `fontSize`               | Value    | –                     | –                | “User interface – Font size”.                                                       |
|                     | `language`               | Value    | –                     | –                | “User interface – Language” (ISO 639‑1).                                            |
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
|                     | `CS`                     | Value    | –                     | –                | Current coordinate system string (“G54”…“G59”).                                     |
|                     | `x`, `y`, `z`            | Value    | –                     | –                | Offset of current system’s X/Y/Z.                                                   |
|                     | `G92x`, …, `G92z`        | Value    | –                     | –                | Workpiece offsets.                                                                  |
|                     | `G28x`, …, `G30z`        | Value    | –                     | –                | Saved positions for G28/G30 commands.                                               |
|                     | `TLOx`, …, `TLOz`        | Value    | –                     | –                | Tool‑offsets X/Y/Z.                                                                 |
|                     | `PRBx`, `PRBy`, `PRBz`   | Value    | –                     | –                | Probe contact coordinates.                                                          |
|                     | `tool`                   | Value    | –                     | –                | Current tool number.                                                                |
| `script`            | `importExtension(name)`  | Function | extension name string | –                | Loads another JavaScript extension; the list of available extensions is in Table 9. |
|                     | `path`                   | Value    | –                     | –                | Absolute path to this extension folder.                                             |

### 5.2.2 Sending‑state enumerations (Table 7)

| State | Description                                                                                           |
|-------|-------------------------------------------------------------------------------------------------------|
| -1    | Unknown state                                                                                        |
| 0     | Sending program                                                                                    |
| 1     | Transition to pause state                                                                          |
| 2     | Pause in progress                                                                                  |
| 3     | Program finished – all CP commands sent                                                            |
| 4     | Transfer completed – controller processed all CP commands                                         |
| 5     | Manual tool change                                                                                 |

### 5.2.3 Controller state enumerations (Table 8)

| State | Description                                                                                           |
|-------|--------------------------------------------------------------------------------------------------------|
| -1    | Unknown state                                                                                        |
| 1     | Ready to receive commands                                                                            |
| 2     | Alarm                                                                                                 |
| 3     | Running                                                                                               |
| 4     | Searching home position                                                                             |
| 5     | End of “Hold” mode transition                                                                       |
| 6     | In “Hold” mode                                                                                    |
| 8     | CP verification mode                                                                                |
| 9     | Door closed, ready to resume                                                                        |
| 10    | Door open, CNC stopped                                                                              |
| 11    | Door open, pausing or parking                                                                        |
| 12    | Door closed, resuming work or returning from parking                                                |
| 13    | Movement state                                                                                       |
| 14    | Sleep mode                                                                                           |

### 5.2.4 Extension script list (Table 9)

| Name          | Description                                            |
|---------------|--------------------------------------------------------|
| `qt.core`     | Core Qt objects                                      |
| `qt.custom`   | Custom UI elements – see Table 10                     |
| `qt.gui`      | GUI Qt objects                                       |
| `qt.multimedia` | Multimedia Qt objects                               |
| `qt.network`  | Network‑supporting Qt objects                        |
| `qt.opengl`   | OpenGL‑supporting Qt objects                         |
| `qt.printsupport` | Print‑supporting Qt objects                     |
| `qt.sql`      | Database‑supporting Qt objects                       |
| `qt.uitools`  | Tools for dynamic UI creation                        |
| `qt.xml`      | XML‑supporting Qt objects                            |
| `qt.widgets`  | Standard Qt widgets                                  |

### 5.2.5 Custom UI elements (Table 10)

| Object type     | Base class | Purpose                                      | Property         | Type   | Arguments | Return value | Description                                                                 |
|-----------------|------------|----------------------------------------------|------------------|--------|-----------|---------------|-----------------------------------------------------------------------------|
| `ColorPicker`   | `QWidget` | Color selection                             | `colorInt`       | Value  | –         | –             | 32‑bit color code in AARRGGBB format.                                      |
|                 |            |                                              | `colorSelected` | Signal | Color     | –             | Emitted when user selects a color.                                        |
| `Slider`        | `QSlider` | Slider with current value display           | `currentValue`   | Value  | –         | –             | Current slider value.                                                      |
| `SliderBox`     | `QWidget` | Slider + line edit + enable flag              | `value`          | Value  | –         | –             | Parameter setting.                                                        |
|                 |            |                                              | `currentValue`   | Value  | –         | –             | Current value.                                                             |
|                 |            |                                              | `minimum`        | Value  | –         | –             | Minimum allowed value.                                                    |
|                 |            |                                              | `maximum`        | Value  | –         | –             | Maximum allowed value.                                                    |
|                 |            |                                              | `sliderPosition` | Value  | –         | –             | Slider position.                                                          |
|                 |            |                                              | `ratio`          | Value  | –         | –             | Ratio of line‑edit value to slider position.                              |
|                 |            |                                              | `title`          | Value  | –         | –             | Parameter name.                                                           |
|                 |            |                                              | `suffix`         | Value  | –         | –             | Units of measurement.                                                     |
|                 |            |                                              | `isCheckable`    | Value  | –         | –             | Whether a check box is shown.                                             |
|                 |            |                                              | `isChecked`      | Value  | –         | –             | Current check state.                                                      |
|                 |            |                                              | `valueUserChanged` | Signal | –     | –             | Emitted when user changes the value.                                      |
|                 |            |                                              | `valueChanged`   | Signal | –         | –             | Emitted when value changes internally.                                    |
|                 |            |                                              | `toggled`        | Signal | State     | –             | Emitted on toggle of check flag.                                          |
|                 |            |                                              | `click`          | Function | –       | –             | Programmatic toggle.                                                      |
| `StyledToolButton` | `QToolButton` | Toolbar button                              | `backgroundColor` | Value  | –         | –             | Button background color (`QColor`).                                      |
|                 |            |                                              | `foregroundColor` | Value  | –         | –             | Text color.                                                               |
|                 |            |                                              | `highlightColor` | Value  | –         | –             | Highlight border color.                                                   |

## 5.3 Translation file

Each extension may provide a translation file for its UI strings.  
The filename format is:

```
translation_xx.qm
```

where **xx** is the two‑letter language code.

Compiled `.qm` files are produced from source `.ts` files using Qt Linguist or the `lrelease` command that ships with the Qt framework.

For details on creating translation files, see the Qt documentation:  
[Qt Linguist Manual](https://doc.qt.io/qt-5/qtlinguist-index.html).

# Appendix A: Controller settings

| Code | Description                                           | Valid values                                                     | Example value |
|------|-------------------------------------------------------|------------------------------------------------------------------|---------------|
| 0    | Step pulse duration for stepper drivers, microseconds |                                                                  | `10`          |
| 1    | Timeout for turning off stepper drivers, milliseconds |                                                                  | `25`          |
| 2    | Bit mask of step signal inversion                     | bit 0 – X, bit 1 – Y, bit 2 – Z                                  | `0`           |
| 3    | Bit mask of direction signal inversion                | bit 0 – X, bit 1 – Y, bit 2 – Z                                  | `0`           |
| 4    | Enable signal inversion flag                          | `0` low active, `1` high active                                  | `0`           |
| 5    | End‑stop inversion flag                               | `0` low active, `1` high active                                  | `0`           |
| 6    | Probe signal inversion flag                           | `0` low active, `1` high active                                  | `0`           |
| 10   | Bit mask of status output                             | bit 0 – work coords, bit 1 – machine coords, bit 2 – buffer info | `3`           |
| 11   | Junction deviation parameter (mm)                     |                                                                  | `0.01`        |
| 12   | Max arc‑to‑segment approximation error (mm)           |                                                                  | `0.002`       |
| 13   | Output units in inches flag                           | `0` mm, `1` inch                                                 | `0`           |
| 20   | Software limits enable flag                           | `0` off, `1` on                                                  | `0`           |
| 21   | Hardware limits enable flag                           | `0` off, `1` on                                                  | `0`           |
| 22   | Homing enabled flag                                   | `0` off, `1` on                                                  | `0`           |
| 23   | Bit mask of homing direction inversion                | bit 0 – X, bit 1 – Y, bit 2 – Z                                  | `0`           |
| 24   | Homing speed (mm/s)                                   |                                                                  | `25`          |
| 25   | Initial homing speed (mm/s)                           |                                                                  | `250`         |
| 26   | End‑stop debounce time (ms)                           |                                                                  | `250`         |
| 27   | Home offset distance after end‑stops (mm)             |                                                                  | `1`           |
| 30   | Max spindle speed (rev/s)                             |                                                                  | `10000`       |
| 31   | Min spindle speed (rev/s)                             |                                                                  | `0`           |
| 32   | Laser mode flag (no stop on “S” command)              | `0` off, `1` on                                                  | `0`           |
| 100  | Steps per mm for X axis                               |                                                                  | `200`         |
| 101  | Steps per mm for Y axis                               |                                                                  | `200`         |
| 102  | Steps per mm for Z axis                               |                                                                  | `200`         |
| 110  | Max feed rate X (mm/s)                                |                                                                  | `2000`        |
| 111  | Max feed rate Y (mm/s)                                |                                                                  | `2000`        |
| 112  | Max feed rate Z (mm/s)                                |                                                                  | `2000`        |
| 120  | Acceleration X (mm/s²)                                |                                                                  | `200`         |
| 121  | Acceleration Y (mm/s²)                                |                                                                  | `200`         |
| 122  | Acceleration Z (mm/s²)                                |                                                                  | `200`         |
| 130  | Max X travel from home (software limit)               |                                                                  | `200`         |
| 131  | Max Y travel from home                                |                                                                  | `200`         |
| 132  | Max Z travel from home                                |                                                                  | `200`         |

# Appendix B: Controller settings (grblHAL)

| Code | Description                                | Valid values                                                                                                                                                                                                                                                                                                                                                                                | Example value   |
|------|--------------------------------------------|---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|-----------------|
| 0   | Step pulse time (µs)                       | min: 3.5 µs                                                                                                                                                                                                                                                                                                                                                                                 | 10 µs           |
| 1   | Step idle delay (ms)                       | 0 ‑ 65535 ms                                                                                                                                                                                                                                                                                                                                                                                | 250 ms          |
| 2   | Step pulse invert – axismask               | 0 – X‑axis (1)<br>1 – Y‑axis (2)<br>2 – Z‑axis (4)<br>3 – A‑axis (8)<br>4 – B‑axis (16)<br>5 – C‑axis (32)                                                                                                                                                                                                                                                                                  | 5 ( X + Z )     |
| 3   | Step direction invert – axismask           | 0 – X‑axis (1)<br>1 – Y‑axis (2)<br>2 – Z‑axis (4)<br>3 – A‑axis (8)<br>4 – B‑axis (16)<br>5 – C‑axis (32)                                                                                                                                                                                                                                                                                  | 0               |
| 4   | Invert stepper enable output(s) – axismask | 0 – X‑axis (1)<br>1 – Y‑axis (2)<br>2 – Z‑axis (4)<br>3 – A‑axis (8)<br>4 – B‑axis (16)<br>5 – C‑axis (32)                                                                                                                                                                                                                                                                                  | 2 (Y‑axis)      |
| 5   | Invert limit inputs – axismask             | 0 – X‑axis (1)<br>1 – Y‑axis (2)<br>2 – Z‑axis (4)<br>3 – A‑axis (8)<br>4 – B‑axis (16)<br>5 – C‑axis (32)                                                                                                                                                                                                                                                                                  | 0               |
| 6   | Invert probe input – bitfield              | 0 – Probe (1)                                                                                                                                                                                                                                                                                                                                                                               | 1               |
| 9   | PWM spindle options – bitfield             | 0 – Enable (1)<br>1 – RPM controls spindle enable signal (2)<br>2 – Disable laser mode capability (4)                                                                                                                                                                                                                                                                                       | 3 (bits 0 + 1)  |
| 10  | Status‑report options – bitfield           | 0 – Position in machine coordinate (1)<br>1 – Buffer state (2)<br>2 – Line numbers (4)<br>3 – Feed & speed (8)<br>4 – Pin state (16)<br>5 – Work coordinate offset (32)<br>6 – Overrides (64)<br>7 – Probe coordinates (128)<br>8 – Buffer sync on WCO change (256)<br>9 – Parser state (512)<br>10 – Alarm substatus (1024)<br>11 – Run substatus (2048)<br>12 – Enable when homing (4096) | 31 (bits 0‑4)   |
| 11  | Junction deviation (mm)                    | ≥ 0                                                                                                                                                                                                                                                                                                                                                                                         | 0.02 mm         |
| 12  | Arc tolerance (mm)                         | ≥ 0                                                                                                                                                                                                                                                                                                                                                                                         | 0.1 mm          |
| 13  | Report in inches – boolean                 | 0 – mm (0)<br>1 – inches (1)                                                                                                                                                                                                                                                                                                                                                                | 0               |
| 14  | Invert control inputs – bitfield           | 1 – Feed hold (2)<br>2 – Cycle start (4)<br>6 – E‑Stop (64)                                                                                                                                                                                                                                                                                                                                 | 66 (bits 1 + 6) |
| 15  | Invert coolant outputs – bitfield          | 0 – Flood (1)<br>1 – Mist (2)                                                                                                                                                                                                                                                                                                                                                               | 1               |
| 16  | Invert spindle signals – bitfield          | 0 – Spindle enable (1)<br>1 – Spindle direction (2)<br>2 – PWM (4)                                                                                                                                                                                                                                                                                                                          | 0               |
| 17  | Pull‑up disable control inputs – bitfield  | 1 – Feed hold (2)<br>2 – Cycle start (4)<br>6 – E‑Stop (64)                                                                                                                                                                                                                                                                                                                                 | 0               |
| 18  | Pull‑up disable limit inputs – axismask    | 0 – X‑axis (1)<br>1 – Y‑axis (2)<br>2 – Z‑axis (4)<br>3 – A‑axis (8)<br>4 – B‑axis (16)<br>5 – C‑axis (32)                                                                                                                                                                                                                                                                                  | 0               |
| 19  | Pull‑up disable probe input – bitfield     | 0 – Probe (1)                                                                                                                                                                                                                                                                                                                                                                               | 0               |
| 20  | Soft limits enable – boolean               | 0 – disabled (0)<br>1 – enabled (1)                                                                                                                                                                                                                                                                                                                                                         | 1               |
| 21  | Hard limits enable – bitfield              | 0 – Enable (1)<br>1 – Strict mode (2)<br>2 – Disable for rotary axes (4)                                                                                                                                                                                                                                                                                                                    | 3 (bits 0 + 1)  |
| 22  | Homing cycle – bitfield                    | 0 – Enable (1)<br>1 – Enable single axis commands (2)<br>2 – Homing on startup required (4)<br>3 – Set machine origin to 0 (8)<br>4 – Two switches share one input (16)<br>5 – Allow manual (32)<br>6 – Override locks (64)<br>9 – Per axis feedrates (512)                                                                                                                                 | 7 (bits 0‑2)    |
| 23  | Homing direction invert – axismask         | 0 – X‑axis (1)<br>1 – Y‑axis (2)<br>2 – Z‑axis (4)<br>3 – A‑axis (8)<br>4 – B‑axis (16)<br>5 – C‑axis (32)                                                                                                                                                                                                                                                                                  | 0               |
| 24  | Homing locate feed rate (mm/min)           | ≥ 0                                                                                                                                                                                                                                                                                                                                                                                         | 100             |
| 25  | Homing search seek rate (mm/min)           | ≥ 0                                                                                                                                                                                                                                                                                                                                                                                         | 300             |
| 26  | Homing switch debounce delay (ms)          | ≥ 0                                                                                                                                                                                                                                                                                                                                                                                         | 5               |
| 27  | Homing switch pull‑off distance (mm)       | ≥ 0                                                                                                                                                                                                                                                                                                                                                                                         | 1.0             |
| 28  | G73 retract distance (mm)                  | ≥ 0                                                                                                                                                                                                                                                                                                                                                                                         | 0.5             |
| 29  | Pulse delay (µs)                           | 0 ‑ 20 µs                                                                                                                                                                                                                                                                                                                                                                                   | 5               |
| 30  | Maximum spindle speed (RPM)                | ≥ 0                                                                                                                                                                                                                                                                                                                                                                                         | 12000           |
| 31  | Minimum spindle speed (RPM)                | ≥ 0                                                                                                                                                                                                                                                                                                                                                                                         | 1000            |
| 32  | Mode of operation – enum                   | 0 – Normal (0)<br>1 – Laser mode (1)<br>2 – Lathe mode (2)                                                                                                                                                                                                                                                                                                                                  | 0               |
| 33  | Spindle PWM frequency (Hz)                 | ≥ 0                                                                                                                                                                                                                                                                                                                                                                                         | 20000           |
| 34  | Spindle PWM off value (%)                  | 0 ‑ 100                                                                                                                                                                                                                                                                                                                                                                                     | 0               |
| 35  | Spindle PWM min value (%)                  | 0 ‑ 100                                                                                                                                                                                                                                                                                                                                                                                     | 10              |
| 36  | Spindle PWM max value (%)                  | 0 ‑ 100                                                                                                                                                                                                                                                                                                                                                                                     | 100             |
| 37  | Steppers to keep enabled – axismask        | 0 – X‑axis (1)<br>1 – Y‑axis (2)<br>2 – Z‑axis (4)<br>3 – A‑axis (8)<br>4 – B‑axis (16)<br>5 – C‑axis (32)                                                                                                                                                                                                                                                                                  | 0               |
| 39  | Enable legacy RT commands – boolean        | 0 – disabled (0)<br>1 – enabled (1)                                                                                                                                                                                                                                                                                                                                                         | 0               |
| 40  | Limit jog commands – boolean               | 0 – disabled (0)<br>1 – enabled (1)                                                                                                                                                                                                                                                                                                                                                         | 1               |
| 43  | Homing passes                              | 1 ‑ 128                                                                                                                                                                                                                                                                                                                                                                                     | 4               |
| 44  | Axes homing – first pass – axismask        | 0 – X‑axis (1)<br>1 – Y‑axis (2)<br>2 – Z‑axis (4)<br>3 – A‑axis (8)<br>4 – B‑axis (16)<br>5 – C‑axis (32)                                                                                                                                                                                                                                                                                  | 7 (X + Y + Z)   |
| 45  | Axes homing – second pass – axismask       | (see $44)                                                                                                                                                                                                                                                                                                                                                                                   | 0               |
| 46  | Axes homing – third pass – axismask        | (see $44)                                                                                                                                                                                                                                                                                                                                                                                   | 0               |
| 47  | Axes homing – fourth pass – axismask       | (see $44)                                                                                                                                                                                                                                                                                                                                                                                   | 0               |
| 62  | Sleep enable – boolean                     | 0 – disabled (0)<br>1 – enabled (1)                                                                                                                                                                                                                                                                                                                                                         | 0               |
| 63  | Feed‑hold actions – bitfield               | 0 – Disable laser during hold (1)<br>1 – Restore spindle and coolant state on resume (2)                                                                                                                                                                                                                                                                                                    | 2               |
| 64  | Force init alarm – boolean                 | 0 – no (0)<br>1 – yes (1)                                                                                                                                                                                                                                                                                                                                                                   | 0               |
| 65  | Probing options – bitfield                 | 0 – Allow feed override (1)<br>1 – Apply soft limits (2)                                                                                                                                                                                                                                                                                                                                    | 3               |
| 100 | X‑axis travel resolution (steps/mm)        | > 0                                                                                                                                                                                                                                                                                                                                                                                         | 250             |
| 101 | Y‑axis travel resolution (steps/mm)        | > 0                                                                                                                                                                                                                                                                                                                                                                                         | 250             |
| 102 | Z‑axis travel resolution (steps/mm)        | > 0                                                                                                                                                                                                                                                                                                                                                                                         | 250             |
| 103 | A‑axis travel resolution (steps/mm)        | > 0                                                                                                                                                                                                                                                                                                                                                                                         | 250             |
| 110 | X‑axis max rate (mm/min)                   | ≥ 0                                                                                                                                                                                                                                                                                                                                                                                         | 5000            |
| 111 | Y‑axis max rate (mm/min)                   | ≥ 0                                                                                                                                                                                                                                                                                                                                                                                         | 5000            |
| 112 | Z‑axis max rate (mm/min)                   | ≥ 0                                                                                                                                                                                                                                                                                                                                                                                         | 3000            |
| 113 | A‑axis max rate (mm/min)                   | ≥ 0                                                                                                                                                                                                                                                                                                                                                                                         | 2000            |
| 120 | X‑axis acceleration (mm/s²)                | ≥ 0                                                                                                                                                                                                                                                                                                                                                                                         | 100             |
| 121 | Y‑axis acceleration (mm/s²)                | ≥ 0                                                                                                                                                                                                                                                                                                                                                                                         | 100             |
| 122 | Z‑axis acceleration (mm/s²)                | ≥ 0                                                                                                                                                                                                                                                                                                                                                                                         | 80              |
| 123 | A‑axis acceleration (mm/s²)                | ≥ 0                                                                                                                                                                                                                                                                                                                                                                                         | 60              |
| 130 | X‑axis max travel (mm)                     | ≥ 0                                                                                                                                                                                                                                                                                                                                                                                         | 300             |
| 131 | Y‑axis max travel (mm)                     | ≥ 0                                                                                                                                                                                                                                                                                                                                                                                         | 300             |
| 132 | Z‑axis max travel (mm)                     | ≥ 0                                                                                                                                                                                                                                                                                                                                                                                         | 200             |
| 133 | A‑axis max travel (mm)                     | ≥ 0                                                                                                                                                                                                                                                                                                                                                                                         | 360             |
| 341 | Tool‑change mode – enum                    | 0 – Normal (0)<br>1 – Manual touch off (1)<br>2 – Manual touch off @ G59.3 (2)<br>3 – Automatic touch off @ G59.3 (3)<br>4 – Ignore M6 (4)                                                                                                                                                                                                                                                  | 0               |
| 342 | Tool‑change probing distance (mm)          | ≥ 0                                                                                                                                                                                                                                                                                                                                                                                         | 5               |
| 343 | Tool‑change locate feed rate (mm/min)      | ≥ 0                                                                                                                                                                                                                                                                                                                                                                                         | 200             |
| 344 | Tool‑change search seek rate (mm/min)      | ≥ 0                                                                                                                                                                                                                                                                                                                                                                                         | 600             |
| 345 | Tool‑change probe pull‑off rate (mm/min)   | ≥ 0                                                                                                                                                                                                                                                                                                                                                                                         | 100             |
| 346 | Tool‑change options – bitfield             | 0 – Restore position after M6 (1)<br>1 – Change tool at G30 (2)<br>2 – Fast probe pull off (4)                                                                                                                                                                                                                                                                                              | 3               |
| 370 | Invert I/O Port inputs – bitfield          | 0 – Aux 0 (1)                                                                                                                                                                                                                                                                                                                                                                               | 0               |
| 376 | Rotary axes – bitfield                     | 0 – A‑Axis (1)                                                                                                                                                                                                                                                                                                                                                                              | 0               |
| 384 | Disable G92 persistence – boolean          | 0 – enabled (0)<br>1 – disabled (1)                                                                                                                                                                                                                                                                                                                                                         | 0               |
| 394 | Spindle‑on delay (s)                       | 0.5 ‑ 20                                                                                                                                                                                                                                                                                                                                                                                    | 1.0             |
| 398 | Planner buffer blocks                      | 30 ‑ 1000 – reboot required                                                                                                                                                                                                                                                                                                                                                                 | 200             |
| 481 | Autoreport interval (ms)                   | 100 ‑ 1000 – reboot required                                                                                                                                                                                                                                                                                                                                                                | 250             |
| 484 | Unlock required after E‑Stop – boolean     | 0 – no (0)<br>1 – yes (1)                                                                                                                                                                                                                                                                                                                                                                   | 1               |
| 486 | Lock coordinate systems – bitfield         | 0 – G59.1 (1)<br>1 – G59.2 (2)<br>2 – G59.3 (4)                                                                                                                                                                                                                                                                                                                                             | 0               |
| 538 | Fast rotary go‑to G28 – bitfield           | 0 – A‑Axis (1)                                                                                                                                                                                                                                                                                                                                                                              | 0               |
| 539 | Spindle‑off delay (s)                      | 0.5 ‑ 20                                                                                                                                                                                                                                                                                                                                                                                    | 1.0             |
| 673 | Coolant‑on delay (s)                       | 0.5 ‑ 20                                                                                                                                                                                                                                                                                                                                                                                    | 0.5             |
| 676 | Reset actions – bitfield                   | 0 – Clear homed status if position was lost (1)<br>1 – Clear offsets (except G92) (2)                                                                                                                                                                                                                                                                                                       | 3               |
| 680 | Stepper enable delay (ms)                  | 0 ‑ 250                                                                                                                                                                                                                                                                                                                                                                                     | 20              |

# Appendix C: Controller errors

| Error Code | Name                          | Description                                                                                   |
|------------|-------------------------------|-----------------------------------------------------------------------------------------------|
| 1          | Expected G-code word          | Grbl expected a valid command (like G1, M3, etc.) but didn't find one. This is often due to a blank or malformed line |
| 2          | Bad number format             | A number in the command was invalid or improperly formatted                                 |
| 3          | Invalid statement             | The line contains an unknown or unsupported command                                         |
| 4          | Negative value                | A negative value was used where it isn't allowed, such as a feed rate or spindle speed       |
| 5          | Homing not enabled            | A homing cycle ($H) was requested but homing is not enabled in the settings                 |
| 6          | Minimum step pulse time violated | A step pulse was issued faster than the configured minimum time ($0)                        |
| 7          | EEPROM read fail              | Grbl could not read its settings from EEPROM. May indicate hardware issues                  |
| 8          | Not idle                      | A command was issued that requires the machine to be idle, but motion or another operation is in progress |
| 9          | G-code lockout                | A G-code command was blocked due to machine state. Common after a reset or alarm            |
| 10         | Homing not set                | The machine requires homing to establish its position before executing the command          |
| 11         | Line overflow                 | A G-code line was too long for Grbl’s internal buffer. Shorten your lines                   |
| 12         | Step rate too high            | Grbl could not generate step pulses fast enough for the commanded movement                  |
| 13         | Safety door open              | A command was blocked because the safety door is open                                       |
| 14         | Build info overflow           | The build info string exceeded the allowed character limit                                  |
| 15         | Setting disabled              | A command depends on a setting (like homing or soft limits) that is disabled                |
| 16         | Negative value in settings    | A setting value was set to a negative number, which is invalid                              |
| 17         | Invalid jog command           | A jog command is improperly formatted or unsupported                                        |
| 20         | Unsupported command           | The command is not supported by Grbl’s G-code parser                                        |
| 21         | Modal group violation         | Two conflicting commands from the same modal group (e.g. two motion modes) were used together |
| 22         | Undefined feed rate           | A motion command was issued without a feed rate being set                                   |
| 23         | Axis command conflict         | Two axis words used inappropriately together, such as in arcs or jogs                       |
| 24         | Invalid target                | The target position is invalid — for example, in an arc that can’t be generated             |
| 25         | Invalid arc radius            | Arc command contains a radius value that doesn't make geometric sense                       |
| 26         | Invalid G-code word           | A word was used in the wrong context or is not allowed for the active command               |
| 27         | Invalid line number           | A line number was used incorrectly or exceeds limits                                        |
| 28         | Value word repeated           | A G-code word was used more than once on the same line                                      |
| 29         | G59.x WCS error               | A G59.1, G59.2, or G59.3 work coordinate system was used but isn’t supported                |
| 30         | G53 with offset               | G53 motion cannot be used with G54–G59 offsets                                              |
| 31         | Invalid real value            | A floating-point value is invalid (e.g. NaN, too many decimal places, etc.)                 |
| 32         | Arc axis missing              | An arc command is missing a required axis word                                              |
| 33         | Arc format error              | Arc command has incorrect or conflicting data (e.g., missing radius and offset)             |
| 34         | No axis word in motion        | A motion command was issued without specifying any axis to move                             |
| 35         | G2/G3 not allowed             | Arc motions (G2/G3) are not allowed in certain states, like jogging                         |
| 36         | Unused words                  | Extra G-code words were found that don’t apply to the current command                       |

# Appendix D: G-code command table

| Command | Description                                                   | Example                                   |
|---------|---------------------------------------------------------------|-------------------------------------------|
| `G0`    | Rapid positioning                                            | `G0 X10 Y20 Z30`                         |
| `G1`    | Linear interpolation                                         | `G1 X0 Y0 Z0 F100`                       |
| `G2`    | Clockwise circular interpolation                            | `G2 X10 Y0 R5 F100`                      |
| `G3`    | Counter‑clockwise circular interpolation                    | `G3 X10 Y0 R5 F100`                      |
| `G4`    | Program delay, P – seconds                                  | `G4 P0.5`                                 |
| `G10`   | Set coordinate offsets                                      | `G10 L2 X10`, `G10 L20 X0`                |
| `G17`   | Select XY plane for circular interpolation                  | `G17`                                     |
| `G18`   | Select ZX plane                                              | `G18`                                     |
| `G19`   | Select YZ plane                                              | `G19`                                     |
| `G20`   | Switch to inch units                                         | `G20`                                     |
| `G21`   | Switch to metric units                                       | `G21`                                     |
| `G28`   | Return to home position                                      | `G28 G91 X0 Y0 Z0`                        |
| `G28.1`  | Set current position as new home                            | `G28.1`                                   |
| `G30`   | Return to tool‑change position                              | `G30 G91 Z0`                              |
| `G30.1`  | Set current position as tool‑change position                 | `G30.1`                                   |
| `G38.2`  | Probe towards workpiece, error on no contact                | `G38.2 G91 X10 F10`                       |
| `G38.3`  | Probe towards workpiece                                      | `G38.3 G91 X10 F10`                       |
| `G38.4`  | Probe away from workpiece, error on lost contact            | `G38.4 G91 X-10 F10`                      |
| `G38.5`  | Probe away from workpiece                                   | `G38.5 G91 X-10 F10`                      |
| `G40`    | Cancel tool radius compensation                              | `G40`                                     |
| `G43.1`  | Tool length compensation                                    | `G43.1 Z0.5`                              |
| `G49`    | Cancel tool length compensation                              | `G49`                                     |
| `G53`    | Use machine (absolute) coordinates                          | `G53 G90 G0 X0 Y0`                        |
| `G54…G59`| Select coordinate system                                    | `G55`                                     |
| `G61`    | Enable precise stop mode                                      | `G1 G61 X10 F100`                         |
| `G80`    | Cancel cycles                                                  | `G80`                                     |
| `G90`    | Use absolute coordinates                                      | `G1 G90 X10 Y10 Z0`                       |
| `G91`    | Use relative coordinates                                      | `G1 G91 X10`                              |
| `G91.1`  | Use I,J,K for circular interpolation                         | `G91.1`                                   |
| `G92`    | Set work coordinate offsets                                  | `G92 X0 Y0`                               |
| `G92.1`  | Reset work coordinate offsets                                 | `G92.1`                                   |
| `G93`    | Feed in reverse time units (1/F min)                          | `G93`                                     |
| `G94`    | Feed in mm/min                                                | `G94`                                     |
| `M0`     | Pause program                                                 | `M0`                                      |
| `M1`     | Optional pause                                               | `M1`                                      |
| `M2`     | End program                                                  | `M2`                                      |
| `M3`     | Spindle clockwise                                         | `M3`                                      |
| `M4`     | Spindle counter‑clockwise                                   | `M4`                                      |
| `M5`     | Stop spindle                                                | `M5`                                      |
| `M7`     | Water coolant on                                            | `M7`                                      |
| `M8`     | Air coolant on                                              | `M8`                                      |
| `M9`     | Coolant off                                                 | `M9`                                      |
| `M30`    | End program and rewind                                     | `M30`                                     |