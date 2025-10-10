# Additional classes

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
