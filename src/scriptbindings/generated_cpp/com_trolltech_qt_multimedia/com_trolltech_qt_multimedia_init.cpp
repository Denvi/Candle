#include <QtScript/QScriptValue>
#include <QtScript/QScriptEngine>

QScriptValue qtscript_create_QSound_class(QScriptEngine *engine);
QScriptValue qtscript_create_QSoundEffect_class(QScriptEngine *engine);

static const char * const qtscript_com_trolltech_qt_multimedia_class_names[] = {
    "QSound"
    , "QSoundEffect"
};

typedef QScriptValue (*QtBindingCreator)(QScriptEngine *engine);
static const QtBindingCreator qtscript_com_trolltech_qt_multimedia_class_functions[] = {
    qtscript_create_QSound_class
    , qtscript_create_QSoundEffect_class
};

void qtscript_initialize_com_trolltech_qt_multimedia_bindings(QScriptValue &extensionObject)
{
    QScriptEngine *engine = extensionObject.engine();
    for (int i = 0; i < 2; ++i) {
        extensionObject.setProperty(qtscript_com_trolltech_qt_multimedia_class_names[i],
            qtscript_com_trolltech_qt_multimedia_class_functions[i](engine),
            QScriptValue::SkipInEnumeration);
    }
}
