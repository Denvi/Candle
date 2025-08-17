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


# Table of contents
[1 Purpose of the program](#1-purpose-of-the-program)  
[2 Program requirements](#2-program-requirements)  
&nbsp;&nbsp;&nbsp;&nbsp;[2.1 Hardware requirements](#21-hardware-requirements)  
&nbsp;&nbsp;&nbsp;&nbsp;[2.2 Software requirements](#22-software-requirements)  
[3 Program execution](#3-program-execution)  
&nbsp;&nbsp;&nbsp;&nbsp;[3.1 Installation](#31-installation)  
&nbsp;&nbsp;&nbsp;&nbsp;[3.2 Running](#32-running)  
&nbsp;&nbsp;&nbsp;&nbsp;[3.3 Main window](#33-main-window)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[3.3.1 Main menu](#331-main-menu)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[3.3.2 Windows](#332-windows)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[3.3.2.1 Window "G-code program"](#3321-window-gcode-program)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[3.3.2.2 Window "Visualizer"](#3322-window-visualizer)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[3.3.2.3 Window "Camera"](#3323-window-camera)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[3.3.2.4 Window "Console"](#3324-window-console)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[3.3.2.5 Windows "Device", "Modification", "User"](#3325-windows-device-modification-user)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[3.3.3 Instrument panels](#333-instrument-panels)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[3.3.3.1 Panel "Status"](#3331-panel-status)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[3.3.3.2 Panel "Control"](#3332-panel-control)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[3.3.3.3 Panel "Coordinate system"](#3333-panel-coordinate-system)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[3.3.3.4 Panel "Spindle"](#3334-panel-spindle)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[3.3.3.5 Panel "Jogging"](#3335-panel-jogging)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[3.3.3.6 Panel "Correction"](#3336-panel-correction)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[3.3.3.7 Panel "Height map"](#3337-panel-height-map)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[3.3.3.8 Panel "User commands"](#3338-panel-user-commands)  
&nbsp;&nbsp;&nbsp;&nbsp;[3.4 Settings window](#34-settings-window)  
&nbsp;&nbsp;&nbsp;&nbsp;[3.5 Preparing the program for operation](#35-preparing-the-program-for-operation)  
&nbsp;&nbsp;&nbsp;&nbsp;[3.6 Loading the control program](#36-loading-the-control-program)  
&nbsp;&nbsp;&nbsp;&nbsp;[3.7 Creating a height map](#37-creating-a-height-map)  
&nbsp;&nbsp;&nbsp;&nbsp;[3.8 Executing the control program](#38-executing-the-control-program)  
[4 Operator messages](#4-operator-messages)  
[5 Extension development](#5-extension-development)  
&nbsp;&nbsp;&nbsp;&nbsp;[5.1 Extension configuration file](#51-extension-configuration-file)  
&nbsp;&nbsp;&nbsp;&nbsp;[5.2 Script file](#52-script-file)  
&nbsp;&nbsp;&nbsp;&nbsp;[5.3 Translation file](#53-translation-file)  
[Appendix A: Controller settings](#appendix-a-controller-settings)  
[Appendix B: G-code command table](#appendix-b-g-code-command-table)  

----

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
| View  | Windows       | Choose which windows are displayed                  |
|       | Panels        | Choose which panels are displayed                   |
|       | Lock windows  | Disable/enable moving of windows                    |
|       | Lock panels   | Disable/enable moving of panels                      |
| Service | Settings     | Open the program’s settings window                  |
| Help  | Contents      | Launch the help system                               |
|       | About program | Open the dialog with information about the program  |

## 3.3.2 Windows

### 3.3.2.1 Window “G‑code program”

The current CP is displayed in the **“G‑code program”** window shown in Figure 2.

![Window “G‑code program”](images_en/g-codeprogram.png#center)
<p class="center">Figure 2 – “G‑code program” window</p>

Each row of the table corresponds to a line of the CP and contains the following columns:

* **“№”** – CP line number.  
* **“Command”** – The command itself.  
* **“State”** – Current state of the command: “Queued”, “Sent”, “Processed”, or “Missed”.  
* **“Response”** – Response from the GRBL controller to the sent command.

The CP can be edited; the following functions are supported:

| Function | How it works |
|----------|--------------|
| Change a command in a selected row | Double‑click the cell in the *Command* column or press `<F2>` while the cell is highlighted. Confirm with `<Enter>` or `<Tab>`, cancel with `<Esc>`. |
| Add new rows | Select the row before which the new one should be inserted, then choose **“Insert row”** from the context menu (right‑click in the table) or press the `<Ins>` key. |
| Delete selected rows | Use **“Delete rows”** from the context menu or press `<Del>`. |

Below the table are controls for loading and sending CP to the CNC controller:

| Button   | Action |
|----------|--------|
| **Open** | Opens a file‑selection dialog; upon confirmation, loads the chosen CP. |
| **Reset** | Clears all selections in the table, sets the first line as current, and resets command states. |
| **Send**  | Starts the transmission of the CP to the CNC controller. |
| **Pause** | Pauses the transmission process. |
| **Stop**  | Stops the transmission. |

> **Note** – When “Pause” or “Stop” is activated, the actual CNC halt occurs only after the controller’s command input buffer has been emptied. For an immediate stop use the **“Hold”** and **“Reset”** commands from the *Control* panel.

To the left of these buttons lies a flag that enables automatic scrolling of the table during CP transmission. If the CP is actively being sent while the user manually scrolls, this flag resets automatically.

#### 3.3.2.2 Window “Visualizer”

The graphical representation of the CP is displayed in the **Window "Visualizer"** (Figure 3).

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

When the CP is sent to the CNC controller, some segments change colour according to the following rules: the part already processed by the CNC is coloured grey; the portion that has been transmitted to the CNC is coloured violet.

Three circle markers are overlaid on the trajectory:

- **Red marker** – start of the trajectory.  
- **Green marker** – end of the trajectory.  
- **Purple marker** – segment corresponding to the command highlighted in the "G‑code program" window table.

In the main area the origin is shown as a red rectangle in the X–Y plane, with axes coloured: X – red, Y – green, Z – blue. A conditional representation of the tool appears as an orange wireframe model.

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

<p class="center">CS: SFM</p>

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

Parameters such as camera image resolution, colour and thickness of the reticle elements are available in the program’s settings window.

#### 3.3.2.4 Window “Console”

For manual CNC control, as well as for configuring and displaying controller status information, the **“Console”** window is provided (Figure 5).

![Window “Console”](images_en/console.png#center)
<p class="center">Figure 5 – Console window</p>

At the bottom of the window there is a command‑entry field and two buttons: **Send Command** and **Clear Console**. At the top a multiline output area shows replies from the controller.

To send a command to the CNC controller, type it into the entry field and press the **Enter** key or click **Send Command**. After the controller processes the command, the command and its reply are displayed above in the following format:

<p class="center">Command < Response</p>

If the program setting *“Display user‑interface commands”* is enabled, all commands sent to the controller by toolbar controls will appear in the output area. When *“Display G‑code program commands”* is turned on, every command from the CP that is transmitted to the controller will also be shown.

The output field can be cleared by clicking **Clear Console**.

#### 3.3.2.5 Windows “Device”, “Modification”, “User”

Instrument panels containing controls and status information of the CNC are located in the **“Device”**, **“Modification”**, and **“User”** windows.

The name of each window indicates the functional purpose of the panels it contains, but this does not restrict their composition – all panels can be freely moved both within a given window and between windows.

Movement is performed by dragging a panel’s title bar with LMB. While dragging, the window shows the future position of the panel as a blue line.

Most instrument panels are collapsible to save screen space. In the expanded state a panel’s header displays a “‑” sign to its left; in the collapsed state it shows a “≡”. Panels can be collapsed or expanded by clicking their title bar with LMB.

Header text is normally black, but when critical functions of a panel are activated it turns red.

At program startup some panels appear inactive and become active only after the CNC is connected to the PC.

## 3.3.3 Instrument panels

### 3.3.3.1 Panel “Status”

The **Status** panel (Figure 6) displays the current work‑ and machine‑coordinates, as well as the operating mode of the CNC controller.  
Coordinates are shown in output fields arranged horizontally in the order: **X, Y, Z**.

#### Controller operating modes (field *“Status”*)

| Mode | Description |
|------|-------------|
| **Ready** | The controller is ready to receive commands. |
| **Alarm** | An emergency state. |
| **Run** | Executing a control program (CP). |
| **Home** | Searching for the home position. |
| **Hold**  | Motion is paused, awaiting further continue/reset commands. |
| **Check**  | Incoming G‑code is interpreted without actual tool movement. |
| **Door**  | Door‑sensor triggered mode. |
| **Jogging**  | Executing special jogging commands. |
| **Sleep** | Low‑power standby mode. |

In the same field, states that are not related to the controller’s operating mode are shown:

- **No connection** – when the serial port cannot be opened for the CNC.
- **Port opened** – the serial port is open but no connection with the GRBL controller has been established.

The background colour of the *Status* field may change depending on the state.

![Panel “Status”](images_en/status.png#center)
<p class="center">Figure 6 – Panel “Status”</p>

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
| **Cooling** | `0xA0` | Toggle water cooling system on/off. |

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
- A button to enable/disable the spindle.

![Panel “Spindle”](images_en/spindle.png#center)
<p class="center">Figure 9 – Panel “Spindle”</p>

The spindle speed can be set either by typing a number into the field or by using the slider.  
Text in the input field may appear **black** if the current spindle speed matches the desired value, or **red** otherwise.

The slider’s knob is a gray circle with a dark outline; the marker – a lighter‑coloured circle indicating the current speed.

During CP transmission to the controller the spindle speed can be altered via the above controls using injected G‑code `S`, or through the “Correction” panel’s override function.  
Spindle on/off during transmission is possible only while the controller is in *Hold* mode.

### 3.3.3.5 Panel “Jogging”

The **Jogging** panel contains controls for moving the CNC tool:

- Arrow buttons for axes **X** (left/right), **Y** (up/down) and **Z** (up/down on the right side).
- A central **Stop** button that force‑stops motion.
- A drop‑down list **Step**, where you can set the jog step size.
- A drop‑down list **Feed**, selecting the jog feed rate.
- A flag **Keyboard Control** to enable keyboard jogging from the PC.

![Panel “Jogging”](images_en/jogging.png#center)
<p class="center">Figure 10 – Panel “Jogging”</p>

The *Step* and *Feed* lists provide predefined values but allow entry of arbitrary numbers.  
Values entered while **Keyboard Control** is enabled are remembered and can be reused on subsequent program launches.

Each button, as well as changing the *Step* and *Feed* values, may have hotkeys defined in the program’s **Settings** window.  Keyboard control must be turned on for these shortcuts to work.

### 3.3.3.6 Panel “Correction”

Figure 11 shows the **Correction** panel.  
It contains controls similar to those on the spindle panel but overrides feed rate, idle speed and spindle speed during CP transmission.

The only difference is that the spindle button has been replaced by a corresponding flag (checkbox).

![Panel “Correction”](images_en/overriding.png#center)
<p class="center">Figure 11 – Panel “Correction”</p>

### 3.3.3.7 Panel “Height Map”

The **Height Map** panel (Figure 12) is responsible for creating, loading, scanning a surface roughness map and subsequently correcting the CP to level the part’s curvature when machining with a CNC.  
This feature is useful for PCB milling and engraving.

![Panel “Height Map”](images_en/heightmap.png#center)
<p class="center">Figure 12 – Panel “Height Map”</p>

The panel provides controls to:

- Create, load and enable the height‑map mode.
- Define a rectangular map area.
- Set the number of probe points along **X** and **Y** axes.
- Specify the working height above the surface and probing depth.
- Set feed rate.
- Choose grid line count for CP partitioning on **X** and **Y**.

CP correction based on the active height map is performed by enabling the **Use Height Map** flag.

More detailed information on using the height‑map feature can be found in § [3.7 “Creating a Height Map”](#37-creating-a-height-map) of this manual.

### 3.3.3.8 Panel “User Commands”

To extend program functionality for CNC control, a **User Commands** panel is provided (Figure 13).  
Each button on the panel sends pre‑defined commands to the GRBL controller when pressed.

![Panel “User Commands”](images_en/usercommands.png#center)
<p class="center">Figure 13 – Panel “User Commands”</p>

Command configuration occurs in the program’s **Settings** window.  Within the *User Commands* group, a table lists each command and allows you to:

- Add, delete or reorder commands.
- Set a tooltip shown when hovering over the button.
- Assign an icon to the button.
- Define one or more G‑code commands that are sent to the controller upon clicking the button.

The program includes a limited set of icons; additional user‑defined icons can be added by placing image files in `plugins/usercommands/images` inside the installation folder.

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
|                            | **Speed**                                 | Baud rate for serial communication                                                                          | 9600, 14400, 19200, 38400, 57600, 115200, any integer value      | 115200                |
|                            | **Polling period**                        | Time between status requests to the controller                                                              | 10–9999 ms                                                   | 100                   |
| **Machine information**    | **Spindle speed min.**                    | Minimum spindle rotation speed (used by the “Spindle” panel)                                                  | 0–99 999 RPM                                                 | 0                     |
|                            | **Spindle speed max.**                    | Maximum spindle rotation speed                                                                               | 0–99 999 RPM                                                 | 10 000                |
|                            | **Laser power min.**                      | Minimum laser power (used for half‑tone raster visualisation of CP)                                            | 0–99 999                                                    | 0                     |
|                            | **Laser power max.**                      | Maximum laser power                                                                                           | 0–99 999                                                    | 100                   |
| **Parser**                 | **Arc segment size – by length**          | Length of segments that split arcs in CP when displayed in the “Visualizer” and during height‑map creation   | 0.1–99 mm (0 = disabled)                                     | 0.1 (disabled)       |
|                            | **Arc segment size – by angle**           | Angle used to subdivide arcs in CP for the same purposes                                                     | 0–180°                                                       | 5 ° (enabled)        |
| **File sending**           | **Start program commands**                | G‑code commands sent to the CNC controller before transmitting the CP                                       | Set of G‑code commands (JavaScript allowed)                    | None                  |
|                            | **End program commands**                  | G‑code commands sent after the CP has been transmitted                                                     | Same as above                                                | None                  |
|                            | **Tool change commands**                  | G‑code commands sent when processing tool‑change instructions                                               | Same as above                                                | None                  |
|                            | **Ignore errors during file sending**     | Flag that determines whether to abort CP transmission when the controller reports an error                   | Enabled, Disabled                                            | Disabled              |
|                            | **Auto‑configure parser before sending from selected line** | Enable sending of parser‑configuration commands before transmitting the CP from a chosen line                 | Enabled, Disabled                                            | Enabled               |
|                            | **Pause file transfer on tool change commands** | Control whether to pause CP transmission while processing tool‑change instructions                         | Enabled, Disabled                                            | Enabled               |
| **Visualizer**             | **Line thickness**                        | Thickness of 3D projection lines in the visualiser                                                          | 1–9                                                           | 1.5                   |
|                            | **Smoothing**                             | Enable line smoothing for the 3D projection                                                               | Enabled, Disabled                                            | Enabled               |
|                            | **MSAA**                                  | Multi‑sample anti‑aliasing for the 3D projection                                                            | Enabled, Disabled                                            | Enabled               |
|                            | **Frame rate**                            | FPS of the 3D projection rendering                                                                           | 30, 60, 120, any integer                                     | 60                    |
|                            | **V-sync**                                | Enable vertical sync                                                                                        | Enabled, Disabled                                            | Disabled              |
|                            | **Depth buffer**                          | Enable depth‑buffering for line overlap control                                                              | Enabled, Disabled                                            | Disabled              |
|                            | **Rendering mode**                        | Method of CP projection: “Vector” (lines) or “Raster” (points)                                              | Vector, Raster                                                | Vector                |
|                            | **Simplify geometry**                     | Limit the minimum segment size when rendering the CP                                                      | Enabled, Disabled                                            | Enabled               |
|                            | **Simplify geometry – Precision**         | Minimum segment length used for simplification (0 = only segments on a single line are converted)            | 0–99 mm                                                       | 0                     |
|                            | **Grayscale shading**                     | Enable point colourization in raster rendering                                                             | Enabled, Disabled                                            | Disabled              |
|                            | **Grayscale shading – by 'S' code**        | Colour points according to the ‘S’ G‑code value                                                            | Enabled, Disabled                                            | Enabled               |
|                            | **Grayscale shading – by 'Z' code**        | Colour points according to the ‘Z’ G‑code value                                                            | Enabled, Disabled                                            | Disabled              |
| **Colors**                 | **Visualizer – Background**               | Background colour in the “Visualizer” window                                                               | Any colour                                                    | White                 |
|                            | **Visualizer – Text**                     | Text colour in the “Visualizer” window                                                                     | Any colour                                                    | Black                 |
|                            | **Visualizer – Tool**                     | Colour of the tool model in the “Visualizer”                                                              | Any colour                                                    | Orange                |
|                            | **Trajectory – Primary**                  | Colour of the main trajectory paths in the CP projection                                                   | Any colour                                                    | Black                 |
|                            | **Trajectory – Completed**                | Colour of parts already processed by the CNC when sending the CP                                         | Any colour                                                    | Gray                  |
|                            | **Trajectory – Highlight**                | Colour of lines sent to the CNC; colour of the marker for the selected CP line                           | Any colour                                                    | Purple                |
|                            | **Trajectory – Z movements**              | Colour of vertical trajectory moves                                                                       | Any colour                                                    | Red                   |
|                            | **Trajectory – Start**                    | Colour of the start marker for the CP                                                                      | Any colour                                                    | Red                   |
|                            | **Trajectory – End**                      | Colour of the end marker for the CP                                                                        | Any colour                                                    | Green                 |
| **Fret model**             | **Type**                                  | Tool model type in the “Visualizer”                                                                       | Flat, Conical                                                 | Conical               |
|                            | **Angle**                                 | Cone angle of the conical tool model                                                                    | 0–180°                                                       | 15 °                  |
|                            | **Diameter**                              | Diameter of the tool model                                                                               | 0–99 mm                                                      | 3 mm                  |
|                            | **Length**                                | Length of the tool model                                                                                | 0–999 mm                                                     | 30 mm                 |
| **Quick shortcuts**        | –                                         | Key combinations for fast invocation of program functions                                               | Any key combination                                          | None                  |
| **Console**                | **Display G‑code commands in CP**          | Show G‑code commands of the CP in the “Console” during transmission to the controller                    | Enabled, Disabled                                            | Disabled              |
|                            | **Display UI commands**                   | Show commands sent via instrument panel elements                                                          | Enabled, Disabled                                            | Enabled               |
|                            | **Auto‑complete command**                 | Auto‑finish a command when entering it in the “Console” field based on previously typed text             | Enabled, Disabled                                            | Enabled               |
| **User interface**         | **Font size**                             | Size of UI font                                                                                           | 8, 9, 10, 11, 12 pt or any integer                          | 9                     |
|                            | **Interface language**                    | Language used for UI labels                                                                              | American English, Russian (list can be extended)               | American English      |
| **Camera**                 | **Name**                                  | Name of the camera whose image is shown in the “Camera” window                                            | List of available cameras or any custom name                  | None                  |
|                            | **Resolution**                            | Image resolution displayed from the camera                                                               | Supported resolutions list or any custom resolution           | 1280×720              |
|                            | **Position**                              | Horizontal/vertical offset of the camera image in the “Camera” window                                      | Any offset in points                                         | 0, 0                  |
|                            | **Scale**                                 | Scaling factor for the camera image                                                                      | Any number                                                   | 1                     |
|                            | **Crosshair position**                    | Relative offset of targeting elements horizontally/vertically                                            | Offset between 0 and 1 in relative units                      | 0, 0                  |
|                            | **Crosshair size**                        | Diameter of the targeting circle                                                                        | 1–100                                                         | 20                    |
|                            | **Crosshair color**                       | Colour of targeting elements                                                                            | Any colour                                                   | Red                   |
|                            | **Line thickness**                        | Thickness of crosshair lines                                                                             | 0–100                                                         | 1                     |
| **User commands**          | –                                         | Table of commands for the “User Commands” panel                                                          | Any set of commands                                          | Test commands         |

## 3.5 Preparing the program for operation

## 3.6 Loading the control program

## 3.7 Creating a height map

## 3.8 Executing the control program

# 4 Operator messages

# 5 Extension development

The program supports extensions that add new features and UI elements.  
Each extension is a folder placed in the **plugins** directory of the installation folder and contains several files:

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

| Object | Property/Method          | Type         | Arguments                          | Return Value | Description |
|--------|--------------------------|--------------|------------------------------------|--------------|-------------|
| `app`  | `sendCommand(command, index)` | Function | command string, optional index     | –            | Sends a single G‑code command to the CNC controller; negative index values are ignored if `<‑99`. |
|        | `sendCommands(commands, index)` | Function | array of commands, optional index | –            | Sends an array of commands as a single string separated by “\n”. |
|        | `addAction(action)`      | Function | `QAction` object                 | –            | Adds an action to the application; shortcuts can be attached. |
|        | `removeAction(action)`   | Function | `QAction` object                 | –            | Removes a previously added action. |
|        | `buttonSize()`           | Function | –                                  | size          | Returns standard button size for program panels. |
|        | `responseReceived(command, index, response)` | Signal  | command string, index, response string | – | Emitted when the controller replies to a sent command. |
|        | `statusReceived(status)` | Signal   | status string                      | –            | Emitted when a “?” status is received from the controller. |
|        | `senderStateChanged(state)` | Signal  | state integer                     | –            | Sent when the program’s sending state changes (see Table 7). |
|        | `deviceStateChanged(state)` | Signal  | state integer                     | –            | Sent when the CNC controller state changes (see Table 8). |
|        | `settingsAboutToLoad()`  | Signal   | –                                  | –            | Before settings are loaded. |
|        | `settingsLoaded()`       | Signal   | –                                  | –            | After settings have been loaded. |
|        | `settingsAboutToSave()`  | Signal   | –                                  | –            | Before settings are saved. |
|        | `settingsSaved()`        | Signal   | –                                  | –            | After settings have been written to disk. |
|        | `settingsAboutToShow()`  | Signal   | –                                  | –            | Right before the Settings dialog is shown. |
|        | `settingsAccepted()`     | Signal   | –                                  | –            | When user accepts changes in the Settings dialog. |
|        | `settingsRejected()`     | Signal   | –                                  | –            | When user cancels changes in the Settings dialog. |
|        | `settingsSetByDefault()` | Signal   | –                                  | –            | When settings are reset to default values. |
|        | `pluginsLoaded()`        | Signal   | –                                  | –            | After all extensions have been loaded. |
|        | `settings`               | Object     | –                                  | –            | The global settings object (see below). |
|        | `path`                   | Value      | –                                  | –            | Absolute installation path of the program. |
| `app.settings` | `port`                 | Value       | –                                 | –            | “Connection – Port” setting. |
|                | `baud`                  | Value       | –                                 | –            | “Connection – Baudrate”. |
|                | `queryStateTime`         | Value       | –                                 | –            | “Connection – Query interval”. |
|                | `spindleSpeedMin`        | Value       | –                                 | –            | “Machine info – Min spindle speed”. |
|                | `spindleSpeedMax`        | Value       | –                                 | –            | “Machine info – Max spindle speed”. |
|                | `laserPowerMin`          | Value       | –                                 | –            | “Machine info – Min laser power”. |
|                | `laserPowerMax`          | Value       | –                                 | –            | “Machine info – Max laser power”. |
|                | `arcLength`              | Value       | –                                 | –            | “Arc approximation – Length”. |
|                | `arcDegree`              | Value       | –                                 | –            | “Arc approximation – Degree”. |
|                | `arcDegreeMode`          | Value       | –                                 | –            | Arc‑by‑degree mode toggle. |
|                | `startCommands`          | Value       | –                                 | –            | “File send – Start commands”. |
|                | `endCommands`            | Value       | –                                 | –            | “File send – End commands”. |
|                | `toolChangeCommands`     | Value       | –                                 | –            | “File send – Tool change commands”. |
|                | `ignoreErrors`           | Value       | –                                 | –            | “File send – Ignore errors”. |
|                | `autoLine`               | Value       | –                                 | –            | “File send – Auto‑parse line”. |
|                | `pauseToolChange`        | Value       | –                                 | –            | “File send – Pause on tool change”. |
|                | `lineWidth`              | Value       | –                                 | –            | “Visualizer – Line width”. |
|                | `antialiasing`           | Value       | –                                 | –            | “Visualizer – Antialiasing”. |
|                | `msaa`                   | Value       | –                                 | –            | “Visualizer – MSAA”. |
|                | `fps`                    | Value       | –                                 | –            | “Visualizer – FPS”. |
|                | `vsync`                  | Value       | –                                 | –            | “Visualizer – V‑Sync”. |
|                | `zBuffer`                | Value       | –                                 | –            | “Visualizer – Z‑buffer”. |
|                | `drawModeVectors`        | Value       | –                                 | –            | “Visualizer – Draw mode” (0 raster, 1 vector). |
|                | `simplify`               | Value       | –                                 | –            | “Visualizer – Simplify geometry”. |
|                | `simplifyPrecision`      | Value       | –                                 | –            | “Visualizer – Simplification precision”. |
|                | `grayscaleSegments`      | Value       | –                                 | –            | “Visualizer – Grayscale segments”. |
|                | `grayscaleSCode`         | Value       | –                                 | –            | “Visualizer – Grayscale by S‑code”. |
|                | `toolType`               | Value       | –                                 | –            | “Tool model – Type” (0 flat, 1 conical). |
|                | `toolAngle`              | Value       | –                                 | –            | “Tool model – Angle”. |
|                | `toolDiameter`           | Value       | –                                 | –            | “Tool model – Diameter”. |
|                | `toolLength`             | Value       | –                                 | –            | “Tool model – Length”. |
|                | `showProgramCommands`    | Value       | –                                 | –            | “Console – Show G‑code program commands”. |
|                | `showUICommands`         | Value       | –                                 | –            | “Console – Show UI commands”. |
|                | `autoCompletion`         | Value       | –                                 | –            | “Console – Auto‑complete command”. |
|                | `fontSize`               | Value       | –                                 | –            | “UI – Font size”. |
|                | `language`               | Value       | –                                 | –            | “UI – Interface language” (ISO 639‑1). |
|                | `units`                  | Value       | –                                 | –            | CNC units (0 metric, 1 imperial). |
|                | `rapidSpeed`             | Value       | –                                 | –            | Rapid movement speed. |
|                | `acceleration`           | Value       | –                                 | –            | Acceleration of movements. |
|                | `machineBounds`          | Value       | –                                 | –            | CNC movement bounds. |
|                | `homingEnabled`          | Value       | –                                 | –            | Homing enabled flag. |
|                | `softLimitsEnabled`      | Value       | –                                 | –            | Soft limits enabled flag. |
| **vars** | `Mx`, `My`, `Mz`           | Value        | –                                  | –            | Current machine coordinates X/Y/Z. |
|          | `Wx`, `Wy`, `Wz`           | Value        | –                                  | –            | Current workpiece coordinates X/Y/Z. |
|          | `G54x`, …, `G59z`          | Value        | –                                  | –            | Coordinate‑system offsets for G54–G59. |
|          | `CS`                       | Value        | –                                  | –            | Current coordinate system string (“G54”…“G59”). |
|          | `x`, `y`, `z`              | Value        | –                                  | –            | Offset of current system’s X/Y/Z. |
|          | `G92x`, …, `G92z`           | Value        | –                                  | –            | Workpiece offsets. |
|          | `G28x`, …, `G30z`           | Value        | –                                  | –            | Saved positions for G28/G30 commands. |
|          | `TLOx`, …, `TLOz`           | Value        | –                                  | –            | Tool‑offsets X/Y/Z. |
|          | `PRBx`, `PRBy`, `PRBz`      | Value        | –                                  | –            | Probe contact coordinates. |
|          | `tool`                     | Value        | –                                  | –            | Current tool number. |
| `script`  | `importExtension(name)`   | Function    | extension name string              | –            | Loads another JavaScript extension; the list of available extensions is in Table 9. |
|          | `path`                    | Value        | –                                 | –            | Absolute path to this extension folder. |

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

| Code | Description                                                              | Valid values | Example value |
|------|---------------------------------------------------------------------------|--------------|---------------|
| 0    | Step pulse duration for stepper drivers, microseconds                    |              | `10`          |
| 1    | Timeout for turning off stepper drivers, milliseconds                     |              | `25`          |
| 2    | Bit mask of step signal inversion                                      | bit 0 – X, bit 1 – Y, bit 2 – Z | `0`   |
| 3    | Bit mask of direction signal inversion                                 | bit 0 – X, bit 1 – Y, bit 2 – Z | `0`   |
| 4    | Enable signal inversion flag                                            | `0` low active, `1` high active | `0`   |
| 5    | End‑stop inversion flag                                                | `0` low active, `1` high active | `0`   |
| 6    | Probe signal inversion flag                                           | `0` low active, `1` high active | `0`   |
| 10   | Bit mask of status output                                             | bit 0 – work coords, bit 1 – machine coords, bit 2 – buffer info | `3`   |
| 11   | Junction deviation parameter (mm)                                     |              | `0.01`        |
| 12   | Max arc‑to‑segment approximation error (mm)                           |              | `0.002`       |
| 13   | Output units in inches flag                                            | `0` mm, `1` inch | `0`      |
| 20   | Software limits enable flag                                           | `0` off, `1` on | `0`        |
| 21   | Hardware limits enable flag                                           | `0` off, `1` on | `0`        |
| 22   | Homing enabled flag                                                   | `0` off, `1` on | `0`        |
| 23   | Bit mask of homing direction inversion                                 | bit 0 – X, bit 1 – Y, bit 2 – Z | `0`   |
| 24   | Homing speed (mm/s)                                                   |              | `25`          |
| 25   | Initial homing speed (mm/s)                                           |              | `250`         |
| 26   | End‑stop debounce time (ms)                                          |              | `250`         |
| 27   | Home offset distance after end‑stops (mm)                             |              | `1`           |
| 30   | Max spindle speed (rev/s)                                             |              | `10000`       |
| 31   | Min spindle speed (rev/s)                                             |              | `0`           |
| 32   | Laser mode flag (no stop on “S” command)                             | `0` off, `1` on | `0`        |
| 100  | Steps per mm for X axis                                               |              | `200`         |
| 101  | Steps per mm for Y axis                                               |              | `200`         |
| 102  | Steps per mm for Z axis                                               |              | `200`         |
| 110  | Max feed rate X (mm/s)                                                |              | `2000`        |
| 111  | Max feed rate Y (mm/s)                                                |              | `2000`        |
| 112  | Max feed rate Z (mm/s)                                                |              | `2000`        |
| 120  | Acceleration X (mm/s²)                                                |              | `200`         |
| 121  | Acceleration Y (mm/s²)                                                |              | `200`         |
| 122  | Acceleration Z (mm/s²)                                                |              | `200`         |
| 130  | Max X travel from home (software limit)                               |              | `200`         |
| 131  | Max Y travel from home                                               |              | `200`         |
| 132  | Max Z travel from home                                               |              | `200`         |

# Appendix B: G-code command table

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