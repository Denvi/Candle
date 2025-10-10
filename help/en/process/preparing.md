# Preparing the program for operation

Before working with the program, perform the following steps:

- Connect and start the CNC machine.  
- Configure the port and baud rate for connection to the CNC controller.  
- Verify the connection to the controller. If the connection is correct, the **"Status"** field in the **"State"** panel should display **"Idle"**.  
- Check the controller settings.

To verify the settings, enter the command `$$` in the input field of the **"Console"** window and send it to the controller.  
The correct operation of the program depends on the following settings (see [Appendix A: Controller settings](#appendix-a-controller-settings)):

- `$5`, `$6` affect the homing and probe functions.  
- `$10` must include the machine coordinate output in its mask, feed & speed, pin state, work coordinate offsets, overrides; a working value example is `1` (`511` for grblHAL).  
- `$22` determines whether limit switches are used during homing; a working value example is `1`.  
- `$23` sets the direction of axis movement during homing.  
- `$30`, `$31` set the spindle speed range and may correspond to the **"Spindle speed min"**, **"Spindle speed max"** settings in the program.  
- `$100`…`$102` define the actual axis travel per commanded unit.  
- `$110`…`$112` – maximum axis travel speeds.  
- `$120`…`$122` – axis acceleration values.  
- `$130`…`$132` define the work area size; used in jogging commands.

To set new values, send commands of the form `$CODE=VALUE` to the controller, e.g. `$10=1`.  
After changing controller settings, it is recommended to reset the controller by pressing the **"Reset"** button on the **"Control"** panel.