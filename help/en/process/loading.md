# Loading the control program

As an example we will use the PCB track-milling G-code, because it touches most of the program’s features.

Load the G-code via the **"Open"** command in the **"File"** menu or by clicking the **"Open"** button in the **"G-code program"** window. After selecting the file and confirming, the **"Visualizer"** window will show the toolpath, machining boundaries, and estimated runtime.

Preparation for running the G-code includes:

- Clamping the workpiece on the table (for milling it is usually placed on a **"sacrificial"** table).  
- Homing the machine (**"Home"** button on the **"Control"** panel).  
- Installing the tool.  
- Setting the work coordinate system zero.

Use the **"Jog"** panel buttons to position the tool at the desired X and Y zero point on the workpiece, then zero the work coordinates for X and Y.

Note: you can zero the work zero either with the axis-zero buttons on the **"User Commands"** panel or on the **"Coordinate System"** panel.  
- With **"User Commands"**, work coordinates are **NOT** restored after a controller reset or emergency stop.  
- With **"Coordinate System"**, values are stored in non-volatile memory and survive power cycles.  

The user decides, but it is recommended to use the **"Coordinate System"** panel for X and Y; for Z you may use **"User Commands"**, because Z depends on the current tool length and is usually set immediately before running the G-code.

Set the Z work zero manually (as with X and Y) or by using the probe command on the **"User Commands"** panel. Connect and configure the probe according to the CNC machine manual.