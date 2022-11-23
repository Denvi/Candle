#/*******************************************************************************
#* Author    :  Damir Bakiev                                                    *
#* Version   :  na                                                              *
#* Date      :  11 November 2021                                                *
#* Website   :  na                                                              *
#* Copyright :  Damir Bakiev 2016-2022                                          *
#* License:                                                                     *
#* Use, modification & distribution is subject to Boost Software License Ver 1. *
#* http://www.boost.org/LICENSE_1_0.txt                                         *
#*******************************************************************************/
cmake_minimum_required(VERSION 3.20)

#file:///C:/Users/bakiev/Junk_Yard/SFT/Candle_1.2.15/script/qtscript_core.dll
#file:///C:/Users/bakiev/Junk_Yard/SFT/Candle_1.2.15/script/qtscript_custom.dll
#file:///C:/Users/bakiev/Junk_Yard/SFT/Candle_1.2.15/script/qtscript_gui.dll
#file:///C:/Users/bakiev/Junk_Yard/SFT/Candle_1.2.15/script/qtscript_multimedia.dll
#file:///C:/Users/bakiev/Junk_Yard/SFT/Candle_1.2.15/script/qtscript_network.dll
#file:///C:/Users/bakiev/Junk_Yard/SFT/Candle_1.2.15/script/qtscript_opengl.dll
#file:///C:/Users/bakiev/Junk_Yard/SFT/Candle_1.2.15/script/qtscript_printsupport.dll
#file:///C:/Users/bakiev/Junk_Yard/SFT/Candle_1.2.15/script/qtscript_sql.dll
#file:///C:/Users/bakiev/Junk_Yard/SFT/Candle_1.2.15/script/qtscript_uitools.dll
#file:///C:/Users/bakiev/Junk_Yard/SFT/Candle_1.2.15/script/qtscript_widgets.dll
#file:///C:/Users/bakiev/Junk_Yard/SFT/Candle_1.2.15/script/qtscript_xml.dll

#add_subdirectory(generated_cpp)
#add_subdirectory(generated_cpp/com_trolltech_qt_core)
#add_subdirectory(generated_cpp/com_trolltech_qt_custom)
#add_subdirectory(generated_cpp/com_trolltech_qt_gui)
#add_subdirectory(generated_cpp/com_trolltech_qt_multimedia)
#add_subdirectory(generated_cpp/com_trolltech_qt_network)
#add_subdirectory(generated_cpp/com_trolltech_qt_opengl)
#add_subdirectory(generated_cpp/com_trolltech_qt_printsupport)
#add_subdirectory(generated_cpp/com_trolltech_qt_sql)
#add_subdirectory(generated_cpp/com_trolltech_qt_uitools)
#add_subdirectory(generated_cpp/com_trolltech_qt_widgets)
#add_subdirectory(generated_cpp/com_trolltech_qt_xml)
#add_subdirectory(plugins)
#add_subdirectory(plugins/script)
#add_subdirectory(plugins/script_debug)
#add_subdirectory(qtbindings)

add_subdirectory(qtbindings/qtscript_core)
add_subdirectory(qtbindings/qtscript_custom)
add_subdirectory(qtbindings/qtscript_gui)
add_subdirectory(qtbindings/qtscript_multimedia)
add_subdirectory(qtbindings/qtscript_network)
add_subdirectory(qtbindings/qtscript_opengl)
add_subdirectory(qtbindings/qtscript_printsupport)
add_subdirectory(qtbindings/qtscript_sql)
add_subdirectory(qtbindings/qtscript_uitools)
add_subdirectory(qtbindings/qtscript_widgets)
add_subdirectory(qtbindings/qtscript_xml)
