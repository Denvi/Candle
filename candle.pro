TEMPLATE = subdirs
 
SUBDIRS =   src/designerplugins \
            src/candle \
            src/candleplugins
            
# Make plugins translations
system(qmake src/candleplugins/candleplugins.pro)

install_main.path = bin
install_main.files = src/candle/release/candle.exe

install_plugins.path = bin/plugins
install_plugins.files = src/candleplugins/camera src/candleplugins/test1

install_translations.path = bin/translations
install_translations.files = src/candle/translations/*

install_license.path = bin
install_license.files = LICENSE

INSTALLS += install_main install_plugins install_translations install_license
