# Plugins

The program supports extensions that add new features and UI elements.  
Each extension is a folder placed in the **candleplugins** directory of the installation folder and contains several files:

- `config.ini` – text file describing the extension.
- `script.js` – JavaScript code implementing the extension logic.
- Supporting resources (Qt Designer `.ui` files, translation files, images, etc.).

The default installation already includes three extensions:

| Extension name        | Purpose                                              |
|-----------------------|------------------------------------------------------|
| `camera`              | "Camera" panel functionality                        |
| `coordinatessytem`    | "Coordinate system" panel functionality             |
| `usercommands`        | "User commands" panel functionality                |