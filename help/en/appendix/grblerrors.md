# GRBL errors

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
