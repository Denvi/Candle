# Script file

The script must be written in **JavaScript** and implement the required functionality.  
An extension can provide UI panels for the "Device", "Modification", "User" windows, a dedicated window in the main program area, settings panel, or none of them.

When the main program loads an extension it calls its functions in the order listed below:

| Function             | Arguments | Return Value          | Description                                           |
|----------------------|-----------|-----------------------|-------------------------------------------------------|
| `init()`             | –         | –                     | Extension initialisation routine                     |
| `createPanelWidget()`| –         | `QWidget` object      | Create a panel widget for "Device", "Modification" or "User" windows |
| `createWindowWidget()`| –       | `QWidget` object      | Create a standalone window in the main program area   |
| `createSettingsWidget()`| –    | `QWidget` object      | Create a settings widget (appears in the Settings dialog) |

The following global objects are available to the script: [Objects](qthelp://candle.en/html/scripting/objects.html).