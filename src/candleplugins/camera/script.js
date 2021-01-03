function on_settings_aboutToSave()
{
}

function on_settings_aboutToLoad()
{

}

function on_settings_loaded()
{
    // Update cameras list
    var n = settings.txtCameraName.currentText;
    settings.txtCameraName.clear();
    settings.txtCameraName.addItems(ui.camMain.availableCameras);
    settings.txtCameraName.currentText = n;

    // Apply settings
    updateSettings();

    // Update resolutions list
    var r = settings.txtCameraResolution.currentText;
    settings.txtCameraResolution.clear();
    settings.txtCameraResolution.addItems(ui.camMain.availableResolutions);
    settings.txtCameraResolution.currentText = r;

    // Connect signals/slots
    ui.camMain.posChanged.connect(on_pos_changed);
    ui.camMain.aimPosChanged.connect(on_aimPos_changed);
    ui.camMain.aimSizeChanged.connect(on_aimSize_changed);
    ui.camMain.aimLineWidthChanged.connect(on_aimLineWidth_changed);
    ui.camMain.aimColorChanged.connect(on_aimColor_changed);
    ui.camMain.zoomChanged.connect(on_zoom_changed);
    settings.txtCameraName.currentTextChanged.connect(on_cameraName_changed);
}

function on_settings_changed()
{
    updateSettings();
}

function updateSettings()
{
    // Resolution
    if (settings.txtCameraResolution.currentText != "") {
        var l = settings.txtCameraResolution.currentText.split("x");
        ui.camMain.resolution = [parseInt(l[0]), parseInt(l[1])];
    }
    
    // Zoom
    if (settings.txtCameraZoom.text == "") settings.txtCameraZoom.text = "1.0";
    ui.camMain.zoom = parseFloat(settings.txtCameraZoom.text);

    // Padding
    if (settings.txtCameraPosition.text == "") settings.txtCameraPosition.text = "0, 0";
    l = settings.txtCameraPosition.text.split(",");
    ui.camMain.pos = [parseInt(l[0]), parseInt(l[1])];

    // Aim position
    if (settings.txtCameraAimPosition.text == "") settings.txtCameraAimPosition.text = "0, 0";
    l = settings.txtCameraAimPosition.text.split(",");
    ui.camMain.aimPos = [parseFloat(l[0]), parseFloat(l[1])];

    // Aim size
    ui.camMain.aimSize = parseInt(settings.txtCameraAimSize.value);

    // Aim line width
    ui.camMain.aimLineWidth = parseInt(settings.txtCameraAimLineWidth.value);
    
    // Aim color
    ui.camMain.aimColor = parseInt(settings.colCameraAimColor.colorInt);

    // Update camera
    ui.camMain.cameraName = settings.txtCameraName.currentText;
}

function on_cameraName_changed(name)
{
    // Update camera
    ui.camMain.cameraName = name;
    
    // Update resolutions list
    var r = settings.txtCameraResolution.currentText;
    settings.txtCameraResolution.clear();
    settings.txtCameraResolution.addItems(ui.camMain.availableResolutions);
    settings.txtCameraResolution.currentText = r;
}

function on_pos_changed(pos)
{
    settings.txtCameraPosition.text = pos.join(", ");
}

function on_aimPos_changed(aimPos)
{
    p = [parseFloat(aimPos[0].toFixed(3)), parseFloat(aimPos[1].toFixed(3))];
    settings.txtCameraAimPosition.text = p.join(", ");
}

function on_aimSize_changed(aimSize)
{
    settings.txtCameraAimSize.text = aimSize;
}

function on_aimLineWidth_changed(aimLineWidth)
{
    settings.txtCameraAimLineWidth.text = aimLineWidth;
}

function on_aimColor_changed(aimColor)
{
    settings.colCameraAimColor.colorInt = aimColor;
}

function on_zoom_changed(zoom)
{
    settings.txtCameraZoom.text = zoom.toFixed(3);
}

main.settingsAboutToLoad.connect(on_settings_aboutToLoad);
main.settingsLoaded.connect(on_settings_loaded);
main.settingsAboutToSave.connect(on_settings_aboutToSave);
main.settingsChanged.connect(on_settings_changed);