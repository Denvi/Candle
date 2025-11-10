# Script preparation

To get familiar with script operation, it is suggested to use the tools provided in the program's "Script" window.

Before starting work, you need to create a new script (the "New" button).

Next, you need to enter the script text. For example:

```js
script.importExtension("qt.core");
script.importExtension("qt.widgets");

const x = QInputDialog.getDouble(app.window, "", "Move X", 1, 0.0, 100.0, 0, Qt.Dialog);

if (x) {
    app.device.sendCommand("G21 G91 G0 X" + x);
}
```

The first two lines are responsible for loading bindings (packages) to enable the use of Qt classes in the script.

The next line calls a dialog box to request a real number - the movement distance along the X-axis.

After setting the value and confirming the input, a relative movement of the tool by the specified distance is performed.

More detailed information on available objects, such as `script` and `app`, is located in the [Objects](qthelp://candle.en/html/scripting/objects.html) section.

Information on Qt class bindings in English is located in the [Script bindings reference](qthelp://candle.script/html/index.html) section.

In addition to the standard Qt classes, there are additional classes available in scripts that can be used when developing user interfaces - [Additional Classes](qthelp://candle.en/html/scripting/customclasses.html).