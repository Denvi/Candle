TEMPLATE = subdirs
 
SUBDIRS = cameraplugin customwidgetsplugin

install_cameraplugin.path = ../../bin/plugins/camera/plugins
install_cameraplugin.files = cameraplugin/release/cameraplugin.dll

install_customwidgetsplugin.path = ../../bin
install_customwidgetsplugin.files = customwidgetsplugin/release/customwidgets.dll

INSTALLS += install_cameraplugin install_customwidgetsplugin