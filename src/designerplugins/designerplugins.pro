TEMPLATE = subdirs
 
SUBDIRS = cameraplugin

install_cameraplugin.path = ../../bin/plugins/camera/plugins
install_cameraplugin.files = cameraplugin/release/cameraplugin.dll

INSTALLS += install_cameraplugin