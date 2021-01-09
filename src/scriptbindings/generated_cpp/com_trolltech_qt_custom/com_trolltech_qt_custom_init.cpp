#include <QtScript/QScriptValue>
#include <QtScript/QScriptEngine>

QScriptValue qtscript_create_ColorPicker_class(QScriptEngine *engine);
QScriptValue qtscript_create_SliderBox_class(QScriptEngine *engine);
QScriptValue qtscript_create_Slider_class(QScriptEngine *engine);
QScriptValue qtscript_create_StyledToolButton_class(QScriptEngine *engine);

static const char * const qtscript_com_trolltech_qt_custom_class_names[] = {
    "ColorPicker"
    , "SliderBox"
    , "Slider"
    , "StyledToolButton"
};

typedef QScriptValue (*QtBindingCreator)(QScriptEngine *engine);
static const QtBindingCreator qtscript_com_trolltech_qt_custom_class_functions[] = {
    qtscript_create_ColorPicker_class
    , qtscript_create_SliderBox_class
    , qtscript_create_Slider_class
    , qtscript_create_StyledToolButton_class
};

void qtscript_initialize_com_trolltech_qt_custom_bindings(QScriptValue &extensionObject)
{
    QScriptEngine *engine = extensionObject.engine();
    for (int i = 0; i < 4; ++i) {
        extensionObject.setProperty(qtscript_com_trolltech_qt_custom_class_names[i],
            qtscript_com_trolltech_qt_custom_class_functions[i](engine),
            QScriptValue::SkipInEnumeration);
    }
}
