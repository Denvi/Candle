# Common G-code commands

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