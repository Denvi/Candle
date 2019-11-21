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
}

function on_settings_changed()
{
    updateSettings();
}

function updateSettings()
{
    ui.camMain.cameraName = settings.txtCameraName.text;

    var l = settings.txtCameraResolution.text.split("x");
    ui.camMain.resolution = [parseInt(l[0]), parseInt(l[1])];   
    
    ui.camMain.zoom = parseFloat(settings.txtCameraZoom.text);

    l = settings.txtCameraPosition.text.split(",");
    ui.camMain.pos = [parseInt(l[0]), parseInt(l[1])];
}

function on_pos_changed(pos)
{
    settings.txtCameraPosition.text = pos.join(", ");
}

function on_zoom_changed(zoom)
{
    settings.txtCameraZoom.text = zoom.toFixed(3);
}

main.settingsLoaded.connect(on_settings_loaded);
main.settingsAboutToSave.connect(on_settings_aboutToSave);
main.settingsChanged.connect(on_settings_changed);

ui.camMain.posChanged.connect(on_pos_changed);
ui.camMain.zoomChanged.connect(on_zoom_changed);