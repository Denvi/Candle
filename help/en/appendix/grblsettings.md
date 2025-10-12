# GRBL settings

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
| 32   | Laser mode flag (no stop on "S" command)              | `0` off, `1` on                                                  | `0`           |
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