TEMPLATE = subdirs
SUBDIRS = qtscript_core \
          qtscript_gui \
          qtscript_widgets \
          qtscript_printsupport \
          qtscript_multimedia \
          qtscript_network \
          qtscript_opengl \
          qtscript_sql \
          qtscript_xml \
          qtscript_uitools \
          qtscript_custom

CONFIG += c++14
QMAKE_CXXFLAGS += -std=c++14
