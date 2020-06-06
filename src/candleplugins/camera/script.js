function on_settings_aboutToSave()
{
}

function on_settings_loaded()
{
    updateSettings();

    var l = ui.camMain.availableCameras;
    var s = "";

    for (var i = 0; i < l.length - 1; i++) s += l[i] + "\r\n";
    s += l[l.length - 1];

    settings.txtCameraName.toolTip = s;

    ui.camMain.posChanged.connect(on_pos_changed);
    ui.camMain.aimPosChanged.connect(on_aimPos_changed);
    ui.camMain.aimSizeChanged.connect(on_aimSize_changed);
    ui.camMain.aimLineWidthChanged.connect(on_aimLineWidth_changed);
    ui.camMain.aimColorChanged.connect(on_aimColor_changed);
    ui.camMain.zoomChanged.connect(on_zoom_changed);
}

function on_settings_changed()
{
    updateSettings();
}

function updateSettings()
{
    ui.camMain.cameraName = settings.txtCameraName.text;

    if (settings.txtCameraResolution.text == "") settings.txtCameraResolution.text = "1280x720";
    var l = settings.txtCameraResolution.text.split("x");
    ui.camMain.resolution = [parseInt(l[0]), parseInt(l[1])];   
    
    if (settings.txtCameraZoom.text == "") settings.txtCameraZoom.text = "1.0";
    ui.camMain.zoom = parseFloat(settings.txtCameraZoom.text);

    if (settings.txtCameraPosition.text == "") settings.txtCameraPosition.text = "0, 0";
    l = settings.txtCameraPosition.text.split(",");
    ui.camMain.pos = [parseInt(l[0]), parseInt(l[1])];

    if (settings.txtCameraAimPosition.text == "") settings.txtCameraAimPosition.text = "0, 0";
    l = settings.txtCameraAimPosition.text.split(",");
    ui.camMain.aimPos = [parseFloat(l[0]), parseFloat(l[1])];

    if (settings.txtCameraAimSize.text == "") settings.txtCameraAimSize.text = "20";
    ui.camMain.aimSize = parseInt(settings.txtCameraAimSize.text);
    
    if (settings.txtCameraAimLineWidth.text == "") settings.txtCameraAimLineWidth.text = "1.0";
    ui.camMain.aimLineWidth = parseInt(settings.txtCameraAimLineWidth.text);
    
    ui.camMain.aimColor = parseInt(settings.colCameraAimColor.colorInt);
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

main.settingsLoaded.connect(on_settings_loaded);
main.settingsAboutToSave.connect(on_settings_aboutToSave);
main.settingsChanged.connect(on_settings_changed);