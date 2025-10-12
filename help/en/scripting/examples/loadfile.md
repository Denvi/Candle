# Loading a file

The example shows how to load an array of strings into the “G-code program” window.  
Useful when generating your own machining programs.

```js
// Load a ready-made G-code program into the workspace
app.loadFile([
    "G21G90",
    "G0X0Y0Z0",
    "G1X10F100",
    "G1Y10F200",
    "G0Z1",
    "G0X0Y0",
    "M2"
]);
```