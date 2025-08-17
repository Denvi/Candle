#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qglshaderprogram.h>
#include <QVariant>
#include <qbytearray.h>
#include <qcolor.h>
#include <qcoreevent.h>
#include <qgenericmatrix.h>
#include <qgl.h>
#include <qglshaderprogram.h>
#include <qlist.h>
#include <qmatrix4x4.h>
#include <qobject.h>
#include <qpoint.h>
#include <qsize.h>
#include <qtransform.h>
#include <qvector2d.h>
#include <qvector3d.h>
#include <qvector4d.h>

#include "qtscriptshell_QGLShaderProgram.h"

static const char * const qtscript_QGLShaderProgram_function_names[] = {
    "QGLShaderProgram"
    // static
    , "hasOpenGLShaderPrograms"
    // prototype
    , "addShader"
    , "addShaderFromSourceCode"
    , "addShaderFromSourceFile"
    , "attributeLocation"
    , "bind"
    , "bindAttributeLocation"
    , "disableAttributeArray"
    , "enableAttributeArray"
    , "geometryInputType"
    , "geometryOutputType"
    , "geometryOutputVertexCount"
    , "isLinked"
    , "link"
    , "log"
    , "maxGeometryOutputVertices"
    , "programId"
    , "release"
    , "removeAllShaders"
    , "removeShader"
    , "setAttributeArray"
    , "setAttributeArray_QVector2D"
    , "setAttributeArray_QVector3D"
    , "setAttributeArray_QVector4D"
    , "setAttributeBuffer"
    , "setAttributeValue"
    , "setGeometryInputType"
    , "setGeometryOutputType"
    , "setGeometryOutputVertexCount"
    , "setUniformValue"
    , "setUniformValueArray"
    , "setUniformValueArray_QVector2D"
    , "setUniformValueArray_QVector3D"
    , "setUniformValueArray_QVector4D"
    , "shaders"
    , "uniformLocation"
    , "toString"
};

static const char * const qtscript_QGLShaderProgram_function_signatures[] = {
    "QObject parent\nQGLContext context, QObject parent"
    // static
    , "QGLContext context"
    // prototype
    , "QGLShader shader"
    , "ShaderType type, QByteArray source\nShaderType type, String source\nShaderType type, char source"
    , "ShaderType type, String fileName"
    , "QByteArray name\nString name\nchar name"
    , ""
    , "QByteArray name, int location\nString name, int location\nchar name, int location"
    , "char name\nint location"
    , "char name\nint location"
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "QGLShader shader"
    , "char name, float values, int tupleSize, int stride\nchar name, unsigned int type, void values, int tupleSize, int stride\nint location, float values, int tupleSize, int stride\nint location, unsigned int type, void values, int tupleSize, int stride"
    , "char name, QVector2D values, int stride\nint location, QVector2D values, int stride"
    , "char name, QVector3D values, int stride\nint location, QVector3D values, int stride"
    , "char name, QVector4D values, int stride\nint location, QVector4D values, int stride"
    , "char name, unsigned int type, int offset, int tupleSize, int stride\nint location, unsigned int type, int offset, int tupleSize, int stride"
    , "char name, QColor value\nchar name, QVector2D value\nchar name, QVector3D value\nchar name, QVector4D value\nchar name, float values, int columns, int rows\nchar name, float value\nchar name, float x, float y\nchar name, float x, float y, float z\nchar name, float x, float y, float z, float w\nint location, QColor value\nint location, QVector2D value\nint location, QVector3D value\nint location, QVector4D value\nint location, float values, int columns, int rows\nint location, float value\nint location, float x, float y\nint location, float x, float y, float z\nint location, float x, float y, float z, float w"
    , "unsigned int inputType"
    , "unsigned int outputType"
    , "int count"
    , "char name, QColor color\nchar name, QMatrix3x3 value\nchar name, QMatrix4x4 value\nchar name, QPoint point\nchar name, QPointF point\nchar name, QSize size\nchar name, QSizeF size\nchar name, QTransform value\nchar name, QVector2D value\nchar name, QVector3D value\nchar name, QVector4D value\nchar name, float value\nchar name, float x, float y\nchar name, float x, float y, float z\nchar name, float x, float y, float z, float w\nchar name, int value\nchar name, unsigned int value\nint location, QColor color\nint location, QMatrix3x3 value\nint location, QMatrix4x4 value\nint location, QPoint point\nint location, QPointF point\nint location, QSize size\nint location, QSizeF size\nint location, QTransform value\nint location, QVector2D value\nint location, QVector3D value\nint location, QVector4D value\nint location, float value\nint location, float x, float y\nint location, float x, float y, float z\nint location, float x, float y, float z, float w\nint location, int value\nint location, unsigned int value"
    , "char name, QMatrix3x3 values, int count\nchar name, QMatrix4x4 values, int count\nchar name, float values, int count, int tupleSize\nchar name, int values, int count\nchar name, unsigned int values, int count\nint location, QMatrix3x3 values, int count\nint location, QMatrix4x4 values, int count\nint location, float values, int count, int tupleSize\nint location, int values, int count\nint location, unsigned int values, int count"
    , "char name, QVector2D values, int count\nint location, QVector2D values, int count"
    , "char name, QVector3D values, int count\nint location, QVector3D values, int count"
    , "char name, QVector4D values, int count\nint location, QVector4D values, int count"
    , ""
    , "QByteArray name\nString name\nchar name"
""
};

static const int qtscript_QGLShaderProgram_function_lengths[] = {
    2
    // static
    , 1
    // prototype
    , 1
    , 2
    , 2
    , 1
    , 0
    , 2
    , 1
    , 1
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 5
    , 3
    , 3
    , 3
    , 5
    , 5
    , 1
    , 1
    , 1
    , 5
    , 4
    , 3
    , 3
    , 3
    , 0
    , 1
    , 0
};

static QScriptValue qtscript_QGLShaderProgram_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QGLShaderProgram::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QGLShaderProgram*)
Q_DECLARE_METATYPE(QtScriptShell_QGLShaderProgram*)
Q_DECLARE_METATYPE(QGLShader*)
Q_DECLARE_METATYPE(QFlags<QGLShader::ShaderTypeBit>)
Q_DECLARE_METATYPE(const char*)
Q_DECLARE_METATYPE(const float*)
Q_DECLARE_METATYPE(const void*)
Q_DECLARE_METATYPE(const QVector2D*)
Q_DECLARE_METATYPE(const QVector3D*)
Q_DECLARE_METATYPE(const QVector4D*)
Q_DECLARE_METATYPE(const QMatrix3x3*)
Q_DECLARE_METATYPE(const QMatrix4x4*)
Q_DECLARE_METATYPE(const int*)
Q_DECLARE_METATYPE(const unsigned int*)
Q_DECLARE_METATYPE(QList<QGLShader* >)
Q_DECLARE_METATYPE(const QGLContext*)

//
// QGLShaderProgram
//

static QScriptValue qtscript_QGLShaderProgram_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 35;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QGLShaderProgram* _q_self = qscriptvalue_cast<QGLShaderProgram*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QGLShaderProgram.%0(): this object is not a QGLShaderProgram")
            .arg(qtscript_QGLShaderProgram_function_names[_id+2]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QGLShader* _q_arg0 = qscriptvalue_cast<QGLShader*>(context->argument(0));
        bool _q_result = _q_self->addShader(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 2) {
        if ((qMetaTypeId<QFlags<QGLShader::ShaderTypeBit> >() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<QByteArray>() == context->argument(1).toVariant().userType())) {
            QFlags<QGLShader::ShaderTypeBit> _q_arg0 = qscriptvalue_cast<QFlags<QGLShader::ShaderTypeBit> >(context->argument(0));
            QByteArray _q_arg1 = qscriptvalue_cast<QByteArray>(context->argument(1));
            bool _q_result = _q_self->addShaderFromSourceCode(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QFlags<QGLShader::ShaderTypeBit> >() == context->argument(0).toVariant().userType())
            && context->argument(1).isString()) {
            QFlags<QGLShader::ShaderTypeBit> _q_arg0 = qscriptvalue_cast<QFlags<QGLShader::ShaderTypeBit> >(context->argument(0));
            QString _q_arg1 = context->argument(1).toString();
            bool _q_result = _q_self->addShaderFromSourceCode(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QFlags<QGLShader::ShaderTypeBit> >() == context->argument(0).toVariant().userType())
            && qscriptvalue_cast<const char*>(context->argument(1))) {
            QFlags<QGLShader::ShaderTypeBit> _q_arg0 = qscriptvalue_cast<QFlags<QGLShader::ShaderTypeBit> >(context->argument(0));
            const char* _q_arg1 = qscriptvalue_cast<const char*>(context->argument(1));
            bool _q_result = _q_self->addShaderFromSourceCode(_q_arg0, _q_arg1);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    break;

    case 2:
    if (context->argumentCount() == 2) {
        QFlags<QGLShader::ShaderTypeBit> _q_arg0 = qscriptvalue_cast<QFlags<QGLShader::ShaderTypeBit> >(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        bool _q_result = _q_self->addShaderFromSourceFile(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QByteArray>() == context->argument(0).toVariant().userType())) {
            QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
            int _q_result = _q_self->attributeLocation(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            int _q_result = _q_self->attributeLocation(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if (qscriptvalue_cast<const char*>(context->argument(0))) {
            const char* _q_arg0 = qscriptvalue_cast<const char*>(context->argument(0));
            int _q_result = _q_self->attributeLocation(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->bind();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 2) {
        if ((qMetaTypeId<QByteArray>() == context->argument(0).toVariant().userType())
            && context->argument(1).isNumber()) {
            QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
            int _q_arg1 = context->argument(1).toInt32();
            _q_self->bindAttributeLocation(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isString()
            && context->argument(1).isNumber()) {
            QString _q_arg0 = context->argument(0).toString();
            int _q_arg1 = context->argument(1).toInt32();
            _q_self->bindAttributeLocation(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (qscriptvalue_cast<const char*>(context->argument(0))
            && context->argument(1).isNumber()) {
            const char* _q_arg0 = qscriptvalue_cast<const char*>(context->argument(0));
            int _q_arg1 = context->argument(1).toInt32();
            _q_self->bindAttributeLocation(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<const char*>(context->argument(0))) {
            const char* _q_arg0 = qscriptvalue_cast<const char*>(context->argument(0));
            _q_self->disableAttributeArray(_q_arg0);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            _q_self->disableAttributeArray(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<const char*>(context->argument(0))) {
            const char* _q_arg0 = qscriptvalue_cast<const char*>(context->argument(0));
            _q_self->enableAttributeArray(_q_arg0);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            _q_self->enableAttributeArray(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        unsigned int _q_result = _q_self->geometryInputType();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        unsigned int _q_result = _q_self->geometryOutputType();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->geometryOutputVertexCount();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isLinked();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->link();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->log();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->maxGeometryOutputVertices();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 0) {
        unsigned int _q_result = _q_self->programId();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 0) {
        _q_self->release();
        return context->engine()->undefinedValue();
    }
    break;

    case 17:
    if (context->argumentCount() == 0) {
        _q_self->removeAllShaders();
        return context->engine()->undefinedValue();
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        QGLShader* _q_arg0 = qscriptvalue_cast<QGLShader*>(context->argument(0));
        _q_self->removeShader(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 19:
    if (context->argumentCount() == 3) {
        if (qscriptvalue_cast<const char*>(context->argument(0))
            && qscriptvalue_cast<const float*>(context->argument(1))
            && context->argument(2).isNumber()) {
            const char* _q_arg0 = qscriptvalue_cast<const char*>(context->argument(0));
            const float* _q_arg1 = qscriptvalue_cast<const float*>(context->argument(1));
            int _q_arg2 = context->argument(2).toInt32();
            _q_self->setAttributeArray(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && qscriptvalue_cast<const float*>(context->argument(1))
            && context->argument(2).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            const float* _q_arg1 = qscriptvalue_cast<const float*>(context->argument(1));
            int _q_arg2 = context->argument(2).toInt32();
            _q_self->setAttributeArray(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 4) {
        if (qscriptvalue_cast<const char*>(context->argument(0))
            && qscriptvalue_cast<const float*>(context->argument(1))
            && context->argument(2).isNumber()
            && context->argument(3).isNumber()) {
            const char* _q_arg0 = qscriptvalue_cast<const char*>(context->argument(0));
            const float* _q_arg1 = qscriptvalue_cast<const float*>(context->argument(1));
            int _q_arg2 = context->argument(2).toInt32();
            int _q_arg3 = context->argument(3).toInt32();
            _q_self->setAttributeArray(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
            return context->engine()->undefinedValue();
        } else if (qscriptvalue_cast<const char*>(context->argument(0))
            && context->argument(1).isNumber()
            && qscriptvalue_cast<const void*>(context->argument(2))
            && context->argument(3).isNumber()) {
            const char* _q_arg0 = qscriptvalue_cast<const char*>(context->argument(0));
            uint _q_arg1 = context->argument(1).toUInt32();
            const void* _q_arg2 = qscriptvalue_cast<const void*>(context->argument(2));
            int _q_arg3 = context->argument(3).toInt32();
            _q_self->setAttributeArray(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && qscriptvalue_cast<const float*>(context->argument(1))
            && context->argument(2).isNumber()
            && context->argument(3).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            const float* _q_arg1 = qscriptvalue_cast<const float*>(context->argument(1));
            int _q_arg2 = context->argument(2).toInt32();
            int _q_arg3 = context->argument(3).toInt32();
            _q_self->setAttributeArray(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && context->argument(1).isNumber()
            && qscriptvalue_cast<const void*>(context->argument(2))
            && context->argument(3).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            uint _q_arg1 = context->argument(1).toUInt32();
            const void* _q_arg2 = qscriptvalue_cast<const void*>(context->argument(2));
            int _q_arg3 = context->argument(3).toInt32();
            _q_self->setAttributeArray(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 5) {
        if (qscriptvalue_cast<const char*>(context->argument(0))
            && context->argument(1).isNumber()
            && qscriptvalue_cast<const void*>(context->argument(2))
            && context->argument(3).isNumber()
            && context->argument(4).isNumber()) {
            const char* _q_arg0 = qscriptvalue_cast<const char*>(context->argument(0));
            uint _q_arg1 = context->argument(1).toUInt32();
            const void* _q_arg2 = qscriptvalue_cast<const void*>(context->argument(2));
            int _q_arg3 = context->argument(3).toInt32();
            int _q_arg4 = context->argument(4).toInt32();
            _q_self->setAttributeArray(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && context->argument(1).isNumber()
            && qscriptvalue_cast<const void*>(context->argument(2))
            && context->argument(3).isNumber()
            && context->argument(4).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            uint _q_arg1 = context->argument(1).toUInt32();
            const void* _q_arg2 = qscriptvalue_cast<const void*>(context->argument(2));
            int _q_arg3 = context->argument(3).toInt32();
            int _q_arg4 = context->argument(4).toInt32();
            _q_self->setAttributeArray(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 20:
    if (context->argumentCount() == 2) {
        if (qscriptvalue_cast<const char*>(context->argument(0))
            && qscriptvalue_cast<const QVector2D*>(context->argument(1))) {
            const char* _q_arg0 = qscriptvalue_cast<const char*>(context->argument(0));
            const QVector2D* _q_arg1 = qscriptvalue_cast<const QVector2D*>(context->argument(1));
            _q_self->setAttributeArray(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && qscriptvalue_cast<const QVector2D*>(context->argument(1))) {
            int _q_arg0 = context->argument(0).toInt32();
            const QVector2D* _q_arg1 = qscriptvalue_cast<const QVector2D*>(context->argument(1));
            _q_self->setAttributeArray(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 3) {
        if (qscriptvalue_cast<const char*>(context->argument(0))
            && qscriptvalue_cast<const QVector2D*>(context->argument(1))
            && context->argument(2).isNumber()) {
            const char* _q_arg0 = qscriptvalue_cast<const char*>(context->argument(0));
            const QVector2D* _q_arg1 = qscriptvalue_cast<const QVector2D*>(context->argument(1));
            int _q_arg2 = context->argument(2).toInt32();
            _q_self->setAttributeArray(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && qscriptvalue_cast<const QVector2D*>(context->argument(1))
            && context->argument(2).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            const QVector2D* _q_arg1 = qscriptvalue_cast<const QVector2D*>(context->argument(1));
            int _q_arg2 = context->argument(2).toInt32();
            _q_self->setAttributeArray(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 21:
    if (context->argumentCount() == 2) {
        if (qscriptvalue_cast<const char*>(context->argument(0))
            && qscriptvalue_cast<const QVector3D*>(context->argument(1))) {
            const char* _q_arg0 = qscriptvalue_cast<const char*>(context->argument(0));
            const QVector3D* _q_arg1 = qscriptvalue_cast<const QVector3D*>(context->argument(1));
            _q_self->setAttributeArray(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && qscriptvalue_cast<const QVector3D*>(context->argument(1))) {
            int _q_arg0 = context->argument(0).toInt32();
            const QVector3D* _q_arg1 = qscriptvalue_cast<const QVector3D*>(context->argument(1));
            _q_self->setAttributeArray(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 3) {
        if (qscriptvalue_cast<const char*>(context->argument(0))
            && qscriptvalue_cast<const QVector3D*>(context->argument(1))
            && context->argument(2).isNumber()) {
            const char* _q_arg0 = qscriptvalue_cast<const char*>(context->argument(0));
            const QVector3D* _q_arg1 = qscriptvalue_cast<const QVector3D*>(context->argument(1));
            int _q_arg2 = context->argument(2).toInt32();
            _q_self->setAttributeArray(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && qscriptvalue_cast<const QVector3D*>(context->argument(1))
            && context->argument(2).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            const QVector3D* _q_arg1 = qscriptvalue_cast<const QVector3D*>(context->argument(1));
            int _q_arg2 = context->argument(2).toInt32();
            _q_self->setAttributeArray(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 22:
    if (context->argumentCount() == 2) {
        if (qscriptvalue_cast<const char*>(context->argument(0))
            && qscriptvalue_cast<const QVector4D*>(context->argument(1))) {
            const char* _q_arg0 = qscriptvalue_cast<const char*>(context->argument(0));
            const QVector4D* _q_arg1 = qscriptvalue_cast<const QVector4D*>(context->argument(1));
            _q_self->setAttributeArray(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && qscriptvalue_cast<const QVector4D*>(context->argument(1))) {
            int _q_arg0 = context->argument(0).toInt32();
            const QVector4D* _q_arg1 = qscriptvalue_cast<const QVector4D*>(context->argument(1));
            _q_self->setAttributeArray(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 3) {
        if (qscriptvalue_cast<const char*>(context->argument(0))
            && qscriptvalue_cast<const QVector4D*>(context->argument(1))
            && context->argument(2).isNumber()) {
            const char* _q_arg0 = qscriptvalue_cast<const char*>(context->argument(0));
            const QVector4D* _q_arg1 = qscriptvalue_cast<const QVector4D*>(context->argument(1));
            int _q_arg2 = context->argument(2).toInt32();
            _q_self->setAttributeArray(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && qscriptvalue_cast<const QVector4D*>(context->argument(1))
            && context->argument(2).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            const QVector4D* _q_arg1 = qscriptvalue_cast<const QVector4D*>(context->argument(1));
            int _q_arg2 = context->argument(2).toInt32();
            _q_self->setAttributeArray(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 23:
    if (context->argumentCount() == 4) {
        if (qscriptvalue_cast<const char*>(context->argument(0))
            && context->argument(1).isNumber()
            && context->argument(2).isNumber()
            && context->argument(3).isNumber()) {
            const char* _q_arg0 = qscriptvalue_cast<const char*>(context->argument(0));
            uint _q_arg1 = context->argument(1).toUInt32();
            int _q_arg2 = context->argument(2).toInt32();
            int _q_arg3 = context->argument(3).toInt32();
            _q_self->setAttributeBuffer(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && context->argument(1).isNumber()
            && context->argument(2).isNumber()
            && context->argument(3).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            uint _q_arg1 = context->argument(1).toUInt32();
            int _q_arg2 = context->argument(2).toInt32();
            int _q_arg3 = context->argument(3).toInt32();
            _q_self->setAttributeBuffer(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 5) {
        if (qscriptvalue_cast<const char*>(context->argument(0))
            && context->argument(1).isNumber()
            && context->argument(2).isNumber()
            && context->argument(3).isNumber()
            && context->argument(4).isNumber()) {
            const char* _q_arg0 = qscriptvalue_cast<const char*>(context->argument(0));
            uint _q_arg1 = context->argument(1).toUInt32();
            int _q_arg2 = context->argument(2).toInt32();
            int _q_arg3 = context->argument(3).toInt32();
            int _q_arg4 = context->argument(4).toInt32();
            _q_self->setAttributeBuffer(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && context->argument(1).isNumber()
            && context->argument(2).isNumber()
            && context->argument(3).isNumber()
            && context->argument(4).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            uint _q_arg1 = context->argument(1).toUInt32();
            int _q_arg2 = context->argument(2).toInt32();
            int _q_arg3 = context->argument(3).toInt32();
            int _q_arg4 = context->argument(4).toInt32();
            _q_self->setAttributeBuffer(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 24:
    if (context->argumentCount() == 2) {
        if (qscriptvalue_cast<const char*>(context->argument(0))
            && (qMetaTypeId<QColor>() == context->argument(1).toVariant().userType())) {
            const char* _q_arg0 = qscriptvalue_cast<const char*>(context->argument(0));
            QColor _q_arg1 = qscriptvalue_cast<QColor>(context->argument(1));
            _q_self->setAttributeValue(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (qscriptvalue_cast<const char*>(context->argument(0))
            && (qMetaTypeId<QVector2D>() == context->argument(1).toVariant().userType())) {
            const char* _q_arg0 = qscriptvalue_cast<const char*>(context->argument(0));
            QVector2D _q_arg1 = qscriptvalue_cast<QVector2D>(context->argument(1));
            _q_self->setAttributeValue(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (qscriptvalue_cast<const char*>(context->argument(0))
            && (qMetaTypeId<QVector3D>() == context->argument(1).toVariant().userType())) {
            const char* _q_arg0 = qscriptvalue_cast<const char*>(context->argument(0));
            QVector3D _q_arg1 = qscriptvalue_cast<QVector3D>(context->argument(1));
            _q_self->setAttributeValue(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (qscriptvalue_cast<const char*>(context->argument(0))
            && (qMetaTypeId<QVector4D>() == context->argument(1).toVariant().userType())) {
            const char* _q_arg0 = qscriptvalue_cast<const char*>(context->argument(0));
            QVector4D _q_arg1 = qscriptvalue_cast<QVector4D>(context->argument(1));
            _q_self->setAttributeValue(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (qscriptvalue_cast<const char*>(context->argument(0))
            && context->argument(1).isNumber()) {
            const char* _q_arg0 = qscriptvalue_cast<const char*>(context->argument(0));
            float _q_arg1 = qscriptvalue_cast<float>(context->argument(1));
            _q_self->setAttributeValue(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && (qMetaTypeId<QColor>() == context->argument(1).toVariant().userType())) {
            int _q_arg0 = context->argument(0).toInt32();
            QColor _q_arg1 = qscriptvalue_cast<QColor>(context->argument(1));
            _q_self->setAttributeValue(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && (qMetaTypeId<QVector2D>() == context->argument(1).toVariant().userType())) {
            int _q_arg0 = context->argument(0).toInt32();
            QVector2D _q_arg1 = qscriptvalue_cast<QVector2D>(context->argument(1));
            _q_self->setAttributeValue(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && (qMetaTypeId<QVector3D>() == context->argument(1).toVariant().userType())) {
            int _q_arg0 = context->argument(0).toInt32();
            QVector3D _q_arg1 = qscriptvalue_cast<QVector3D>(context->argument(1));
            _q_self->setAttributeValue(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && (qMetaTypeId<QVector4D>() == context->argument(1).toVariant().userType())) {
            int _q_arg0 = context->argument(0).toInt32();
            QVector4D _q_arg1 = qscriptvalue_cast<QVector4D>(context->argument(1));
            _q_self->setAttributeValue(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && context->argument(1).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            float _q_arg1 = qscriptvalue_cast<float>(context->argument(1));
            _q_self->setAttributeValue(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 3) {
        if (qscriptvalue_cast<const char*>(context->argument(0))
            && context->argument(1).isNumber()
            && context->argument(2).isNumber()) {
            const char* _q_arg0 = qscriptvalue_cast<const char*>(context->argument(0));
            float _q_arg1 = qscriptvalue_cast<float>(context->argument(1));
            float _q_arg2 = qscriptvalue_cast<float>(context->argument(2));
            _q_self->setAttributeValue(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && context->argument(1).isNumber()
            && context->argument(2).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            float _q_arg1 = qscriptvalue_cast<float>(context->argument(1));
            float _q_arg2 = qscriptvalue_cast<float>(context->argument(2));
            _q_self->setAttributeValue(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 4) {
        if (qscriptvalue_cast<const char*>(context->argument(0))
            && qscriptvalue_cast<const float*>(context->argument(1))
            && context->argument(2).isNumber()
            && context->argument(3).isNumber()) {
            const char* _q_arg0 = qscriptvalue_cast<const char*>(context->argument(0));
            const float* _q_arg1 = qscriptvalue_cast<const float*>(context->argument(1));
            int _q_arg2 = context->argument(2).toInt32();
            int _q_arg3 = context->argument(3).toInt32();
            _q_self->setAttributeValue(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
            return context->engine()->undefinedValue();
        } else if (qscriptvalue_cast<const char*>(context->argument(0))
            && context->argument(1).isNumber()
            && context->argument(2).isNumber()
            && context->argument(3).isNumber()) {
            const char* _q_arg0 = qscriptvalue_cast<const char*>(context->argument(0));
            float _q_arg1 = qscriptvalue_cast<float>(context->argument(1));
            float _q_arg2 = qscriptvalue_cast<float>(context->argument(2));
            float _q_arg3 = qscriptvalue_cast<float>(context->argument(3));
            _q_self->setAttributeValue(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && qscriptvalue_cast<const float*>(context->argument(1))
            && context->argument(2).isNumber()
            && context->argument(3).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            const float* _q_arg1 = qscriptvalue_cast<const float*>(context->argument(1));
            int _q_arg2 = context->argument(2).toInt32();
            int _q_arg3 = context->argument(3).toInt32();
            _q_self->setAttributeValue(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && context->argument(1).isNumber()
            && context->argument(2).isNumber()
            && context->argument(3).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            float _q_arg1 = qscriptvalue_cast<float>(context->argument(1));
            float _q_arg2 = qscriptvalue_cast<float>(context->argument(2));
            float _q_arg3 = qscriptvalue_cast<float>(context->argument(3));
            _q_self->setAttributeValue(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 5) {
        if (qscriptvalue_cast<const char*>(context->argument(0))
            && context->argument(1).isNumber()
            && context->argument(2).isNumber()
            && context->argument(3).isNumber()
            && context->argument(4).isNumber()) {
            const char* _q_arg0 = qscriptvalue_cast<const char*>(context->argument(0));
            float _q_arg1 = qscriptvalue_cast<float>(context->argument(1));
            float _q_arg2 = qscriptvalue_cast<float>(context->argument(2));
            float _q_arg3 = qscriptvalue_cast<float>(context->argument(3));
            float _q_arg4 = qscriptvalue_cast<float>(context->argument(4));
            _q_self->setAttributeValue(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && context->argument(1).isNumber()
            && context->argument(2).isNumber()
            && context->argument(3).isNumber()
            && context->argument(4).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            float _q_arg1 = qscriptvalue_cast<float>(context->argument(1));
            float _q_arg2 = qscriptvalue_cast<float>(context->argument(2));
            float _q_arg3 = qscriptvalue_cast<float>(context->argument(3));
            float _q_arg4 = qscriptvalue_cast<float>(context->argument(4));
            _q_self->setAttributeValue(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 25:
    if (context->argumentCount() == 1) {
        uint _q_arg0 = context->argument(0).toUInt32();
        _q_self->setGeometryInputType(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 26:
    if (context->argumentCount() == 1) {
        uint _q_arg0 = context->argument(0).toUInt32();
        _q_self->setGeometryOutputType(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 27:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setGeometryOutputVertexCount(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 28:
    if (context->argumentCount() == 2) {
        if (qscriptvalue_cast<const char*>(context->argument(0))
            && (qMetaTypeId<QColor>() == context->argument(1).toVariant().userType())) {
            const char* _q_arg0 = qscriptvalue_cast<const char*>(context->argument(0));
            QColor _q_arg1 = qscriptvalue_cast<QColor>(context->argument(1));
            _q_self->setUniformValue(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (qscriptvalue_cast<const char*>(context->argument(0))
            && (qMetaTypeId<QMatrix3x3>() == context->argument(1).toVariant().userType())) {
            const char* _q_arg0 = qscriptvalue_cast<const char*>(context->argument(0));
            QMatrix3x3 _q_arg1 = qscriptvalue_cast<QMatrix3x3>(context->argument(1));
            _q_self->setUniformValue(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (qscriptvalue_cast<const char*>(context->argument(0))
            && (qMetaTypeId<QMatrix4x4>() == context->argument(1).toVariant().userType())) {
            const char* _q_arg0 = qscriptvalue_cast<const char*>(context->argument(0));
            QMatrix4x4 _q_arg1 = qscriptvalue_cast<QMatrix4x4>(context->argument(1));
            _q_self->setUniformValue(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (qscriptvalue_cast<const char*>(context->argument(0))
            && (qMetaTypeId<QPoint>() == context->argument(1).toVariant().userType())) {
            const char* _q_arg0 = qscriptvalue_cast<const char*>(context->argument(0));
            QPoint _q_arg1 = qscriptvalue_cast<QPoint>(context->argument(1));
            _q_self->setUniformValue(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (qscriptvalue_cast<const char*>(context->argument(0))
            && (qMetaTypeId<QPointF>() == context->argument(1).toVariant().userType())) {
            const char* _q_arg0 = qscriptvalue_cast<const char*>(context->argument(0));
            QPointF _q_arg1 = qscriptvalue_cast<QPointF>(context->argument(1));
            _q_self->setUniformValue(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (qscriptvalue_cast<const char*>(context->argument(0))
            && (qMetaTypeId<QSize>() == context->argument(1).toVariant().userType())) {
            const char* _q_arg0 = qscriptvalue_cast<const char*>(context->argument(0));
            QSize _q_arg1 = qscriptvalue_cast<QSize>(context->argument(1));
            _q_self->setUniformValue(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (qscriptvalue_cast<const char*>(context->argument(0))
            && (qMetaTypeId<QSizeF>() == context->argument(1).toVariant().userType())) {
            const char* _q_arg0 = qscriptvalue_cast<const char*>(context->argument(0));
            QSizeF _q_arg1 = qscriptvalue_cast<QSizeF>(context->argument(1));
            _q_self->setUniformValue(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (qscriptvalue_cast<const char*>(context->argument(0))
            && (qMetaTypeId<QTransform>() == context->argument(1).toVariant().userType())) {
            const char* _q_arg0 = qscriptvalue_cast<const char*>(context->argument(0));
            QTransform _q_arg1 = qscriptvalue_cast<QTransform>(context->argument(1));
            _q_self->setUniformValue(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (qscriptvalue_cast<const char*>(context->argument(0))
            && (qMetaTypeId<QVector2D>() == context->argument(1).toVariant().userType())) {
            const char* _q_arg0 = qscriptvalue_cast<const char*>(context->argument(0));
            QVector2D _q_arg1 = qscriptvalue_cast<QVector2D>(context->argument(1));
            _q_self->setUniformValue(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (qscriptvalue_cast<const char*>(context->argument(0))
            && (qMetaTypeId<QVector3D>() == context->argument(1).toVariant().userType())) {
            const char* _q_arg0 = qscriptvalue_cast<const char*>(context->argument(0));
            QVector3D _q_arg1 = qscriptvalue_cast<QVector3D>(context->argument(1));
            _q_self->setUniformValue(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (qscriptvalue_cast<const char*>(context->argument(0))
            && (qMetaTypeId<QVector4D>() == context->argument(1).toVariant().userType())) {
            const char* _q_arg0 = qscriptvalue_cast<const char*>(context->argument(0));
            QVector4D _q_arg1 = qscriptvalue_cast<QVector4D>(context->argument(1));
            _q_self->setUniformValue(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (qscriptvalue_cast<const char*>(context->argument(0))
            && context->argument(1).isNumber()) {
            const char* _q_arg0 = qscriptvalue_cast<const char*>(context->argument(0));
            float _q_arg1 = qscriptvalue_cast<float>(context->argument(1));
            _q_self->setUniformValue(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (qscriptvalue_cast<const char*>(context->argument(0))
            && context->argument(1).isNumber()) {
            const char* _q_arg0 = qscriptvalue_cast<const char*>(context->argument(0));
            int _q_arg1 = context->argument(1).toInt32();
            _q_self->setUniformValue(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (qscriptvalue_cast<const char*>(context->argument(0))
            && context->argument(1).isNumber()) {
            const char* _q_arg0 = qscriptvalue_cast<const char*>(context->argument(0));
            uint _q_arg1 = context->argument(1).toUInt32();
            _q_self->setUniformValue(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && (qMetaTypeId<QColor>() == context->argument(1).toVariant().userType())) {
            int _q_arg0 = context->argument(0).toInt32();
            QColor _q_arg1 = qscriptvalue_cast<QColor>(context->argument(1));
            _q_self->setUniformValue(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && (qMetaTypeId<QMatrix3x3>() == context->argument(1).toVariant().userType())) {
            int _q_arg0 = context->argument(0).toInt32();
            QMatrix3x3 _q_arg1 = qscriptvalue_cast<QMatrix3x3>(context->argument(1));
            _q_self->setUniformValue(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && (qMetaTypeId<QMatrix4x4>() == context->argument(1).toVariant().userType())) {
            int _q_arg0 = context->argument(0).toInt32();
            QMatrix4x4 _q_arg1 = qscriptvalue_cast<QMatrix4x4>(context->argument(1));
            _q_self->setUniformValue(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && (qMetaTypeId<QPoint>() == context->argument(1).toVariant().userType())) {
            int _q_arg0 = context->argument(0).toInt32();
            QPoint _q_arg1 = qscriptvalue_cast<QPoint>(context->argument(1));
            _q_self->setUniformValue(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && (qMetaTypeId<QPointF>() == context->argument(1).toVariant().userType())) {
            int _q_arg0 = context->argument(0).toInt32();
            QPointF _q_arg1 = qscriptvalue_cast<QPointF>(context->argument(1));
            _q_self->setUniformValue(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && (qMetaTypeId<QSize>() == context->argument(1).toVariant().userType())) {
            int _q_arg0 = context->argument(0).toInt32();
            QSize _q_arg1 = qscriptvalue_cast<QSize>(context->argument(1));
            _q_self->setUniformValue(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && (qMetaTypeId<QSizeF>() == context->argument(1).toVariant().userType())) {
            int _q_arg0 = context->argument(0).toInt32();
            QSizeF _q_arg1 = qscriptvalue_cast<QSizeF>(context->argument(1));
            _q_self->setUniformValue(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && (qMetaTypeId<QTransform>() == context->argument(1).toVariant().userType())) {
            int _q_arg0 = context->argument(0).toInt32();
            QTransform _q_arg1 = qscriptvalue_cast<QTransform>(context->argument(1));
            _q_self->setUniformValue(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && (qMetaTypeId<QVector2D>() == context->argument(1).toVariant().userType())) {
            int _q_arg0 = context->argument(0).toInt32();
            QVector2D _q_arg1 = qscriptvalue_cast<QVector2D>(context->argument(1));
            _q_self->setUniformValue(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && (qMetaTypeId<QVector3D>() == context->argument(1).toVariant().userType())) {
            int _q_arg0 = context->argument(0).toInt32();
            QVector3D _q_arg1 = qscriptvalue_cast<QVector3D>(context->argument(1));
            _q_self->setUniformValue(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && (qMetaTypeId<QVector4D>() == context->argument(1).toVariant().userType())) {
            int _q_arg0 = context->argument(0).toInt32();
            QVector4D _q_arg1 = qscriptvalue_cast<QVector4D>(context->argument(1));
            _q_self->setUniformValue(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && context->argument(1).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            float _q_arg1 = qscriptvalue_cast<float>(context->argument(1));
            _q_self->setUniformValue(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && context->argument(1).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            int _q_arg1 = context->argument(1).toInt32();
            _q_self->setUniformValue(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && context->argument(1).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            uint _q_arg1 = context->argument(1).toUInt32();
            _q_self->setUniformValue(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 3) {
        if (qscriptvalue_cast<const char*>(context->argument(0))
            && context->argument(1).isNumber()
            && context->argument(2).isNumber()) {
            const char* _q_arg0 = qscriptvalue_cast<const char*>(context->argument(0));
            float _q_arg1 = qscriptvalue_cast<float>(context->argument(1));
            float _q_arg2 = qscriptvalue_cast<float>(context->argument(2));
            _q_self->setUniformValue(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && context->argument(1).isNumber()
            && context->argument(2).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            float _q_arg1 = qscriptvalue_cast<float>(context->argument(1));
            float _q_arg2 = qscriptvalue_cast<float>(context->argument(2));
            _q_self->setUniformValue(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 4) {
        if (qscriptvalue_cast<const char*>(context->argument(0))
            && context->argument(1).isNumber()
            && context->argument(2).isNumber()
            && context->argument(3).isNumber()) {
            const char* _q_arg0 = qscriptvalue_cast<const char*>(context->argument(0));
            float _q_arg1 = qscriptvalue_cast<float>(context->argument(1));
            float _q_arg2 = qscriptvalue_cast<float>(context->argument(2));
            float _q_arg3 = qscriptvalue_cast<float>(context->argument(3));
            _q_self->setUniformValue(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && context->argument(1).isNumber()
            && context->argument(2).isNumber()
            && context->argument(3).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            float _q_arg1 = qscriptvalue_cast<float>(context->argument(1));
            float _q_arg2 = qscriptvalue_cast<float>(context->argument(2));
            float _q_arg3 = qscriptvalue_cast<float>(context->argument(3));
            _q_self->setUniformValue(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 5) {
        if (qscriptvalue_cast<const char*>(context->argument(0))
            && context->argument(1).isNumber()
            && context->argument(2).isNumber()
            && context->argument(3).isNumber()
            && context->argument(4).isNumber()) {
            const char* _q_arg0 = qscriptvalue_cast<const char*>(context->argument(0));
            float _q_arg1 = qscriptvalue_cast<float>(context->argument(1));
            float _q_arg2 = qscriptvalue_cast<float>(context->argument(2));
            float _q_arg3 = qscriptvalue_cast<float>(context->argument(3));
            float _q_arg4 = qscriptvalue_cast<float>(context->argument(4));
            _q_self->setUniformValue(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && context->argument(1).isNumber()
            && context->argument(2).isNumber()
            && context->argument(3).isNumber()
            && context->argument(4).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            float _q_arg1 = qscriptvalue_cast<float>(context->argument(1));
            float _q_arg2 = qscriptvalue_cast<float>(context->argument(2));
            float _q_arg3 = qscriptvalue_cast<float>(context->argument(3));
            float _q_arg4 = qscriptvalue_cast<float>(context->argument(4));
            _q_self->setUniformValue(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 29:
    if (context->argumentCount() == 3) {
        if (qscriptvalue_cast<const char*>(context->argument(0))
            && qscriptvalue_cast<const QMatrix3x3*>(context->argument(1))
            && context->argument(2).isNumber()) {
            const char* _q_arg0 = qscriptvalue_cast<const char*>(context->argument(0));
            const QMatrix3x3* _q_arg1 = qscriptvalue_cast<const QMatrix3x3*>(context->argument(1));
            int _q_arg2 = context->argument(2).toInt32();
            _q_self->setUniformValueArray(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        } else if (qscriptvalue_cast<const char*>(context->argument(0))
            && qscriptvalue_cast<const QMatrix4x4*>(context->argument(1))
            && context->argument(2).isNumber()) {
            const char* _q_arg0 = qscriptvalue_cast<const char*>(context->argument(0));
            const QMatrix4x4* _q_arg1 = qscriptvalue_cast<const QMatrix4x4*>(context->argument(1));
            int _q_arg2 = context->argument(2).toInt32();
            _q_self->setUniformValueArray(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        } else if (qscriptvalue_cast<const char*>(context->argument(0))
            && qscriptvalue_cast<const int*>(context->argument(1))
            && context->argument(2).isNumber()) {
            const char* _q_arg0 = qscriptvalue_cast<const char*>(context->argument(0));
            const int* _q_arg1 = qscriptvalue_cast<const int*>(context->argument(1));
            int _q_arg2 = context->argument(2).toInt32();
            _q_self->setUniformValueArray(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        } else if (qscriptvalue_cast<const char*>(context->argument(0))
            && qscriptvalue_cast<const uint*>(context->argument(1))
            && context->argument(2).isNumber()) {
            const char* _q_arg0 = qscriptvalue_cast<const char*>(context->argument(0));
            const uint* _q_arg1 = qscriptvalue_cast<const uint*>(context->argument(1));
            int _q_arg2 = context->argument(2).toInt32();
            _q_self->setUniformValueArray(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && qscriptvalue_cast<const QMatrix3x3*>(context->argument(1))
            && context->argument(2).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            const QMatrix3x3* _q_arg1 = qscriptvalue_cast<const QMatrix3x3*>(context->argument(1));
            int _q_arg2 = context->argument(2).toInt32();
            _q_self->setUniformValueArray(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && qscriptvalue_cast<const QMatrix4x4*>(context->argument(1))
            && context->argument(2).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            const QMatrix4x4* _q_arg1 = qscriptvalue_cast<const QMatrix4x4*>(context->argument(1));
            int _q_arg2 = context->argument(2).toInt32();
            _q_self->setUniformValueArray(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && qscriptvalue_cast<const int*>(context->argument(1))
            && context->argument(2).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            const int* _q_arg1 = qscriptvalue_cast<const int*>(context->argument(1));
            int _q_arg2 = context->argument(2).toInt32();
            _q_self->setUniformValueArray(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && qscriptvalue_cast<const uint*>(context->argument(1))
            && context->argument(2).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            const uint* _q_arg1 = qscriptvalue_cast<const uint*>(context->argument(1));
            int _q_arg2 = context->argument(2).toInt32();
            _q_self->setUniformValueArray(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 4) {
        if (qscriptvalue_cast<const char*>(context->argument(0))
            && qscriptvalue_cast<const float*>(context->argument(1))
            && context->argument(2).isNumber()
            && context->argument(3).isNumber()) {
            const char* _q_arg0 = qscriptvalue_cast<const char*>(context->argument(0));
            const float* _q_arg1 = qscriptvalue_cast<const float*>(context->argument(1));
            int _q_arg2 = context->argument(2).toInt32();
            int _q_arg3 = context->argument(3).toInt32();
            _q_self->setUniformValueArray(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && qscriptvalue_cast<const float*>(context->argument(1))
            && context->argument(2).isNumber()
            && context->argument(3).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            const float* _q_arg1 = qscriptvalue_cast<const float*>(context->argument(1));
            int _q_arg2 = context->argument(2).toInt32();
            int _q_arg3 = context->argument(3).toInt32();
            _q_self->setUniformValueArray(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 30:
    if (context->argumentCount() == 3) {
        if (qscriptvalue_cast<const char*>(context->argument(0))
            && qscriptvalue_cast<const QVector2D*>(context->argument(1))
            && context->argument(2).isNumber()) {
            const char* _q_arg0 = qscriptvalue_cast<const char*>(context->argument(0));
            const QVector2D* _q_arg1 = qscriptvalue_cast<const QVector2D*>(context->argument(1));
            int _q_arg2 = context->argument(2).toInt32();
            _q_self->setUniformValueArray(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && qscriptvalue_cast<const QVector2D*>(context->argument(1))
            && context->argument(2).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            const QVector2D* _q_arg1 = qscriptvalue_cast<const QVector2D*>(context->argument(1));
            int _q_arg2 = context->argument(2).toInt32();
            _q_self->setUniformValueArray(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 31:
    if (context->argumentCount() == 3) {
        if (qscriptvalue_cast<const char*>(context->argument(0))
            && qscriptvalue_cast<const QVector3D*>(context->argument(1))
            && context->argument(2).isNumber()) {
            const char* _q_arg0 = qscriptvalue_cast<const char*>(context->argument(0));
            const QVector3D* _q_arg1 = qscriptvalue_cast<const QVector3D*>(context->argument(1));
            int _q_arg2 = context->argument(2).toInt32();
            _q_self->setUniformValueArray(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && qscriptvalue_cast<const QVector3D*>(context->argument(1))
            && context->argument(2).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            const QVector3D* _q_arg1 = qscriptvalue_cast<const QVector3D*>(context->argument(1));
            int _q_arg2 = context->argument(2).toInt32();
            _q_self->setUniformValueArray(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 32:
    if (context->argumentCount() == 3) {
        if (qscriptvalue_cast<const char*>(context->argument(0))
            && qscriptvalue_cast<const QVector4D*>(context->argument(1))
            && context->argument(2).isNumber()) {
            const char* _q_arg0 = qscriptvalue_cast<const char*>(context->argument(0));
            const QVector4D* _q_arg1 = qscriptvalue_cast<const QVector4D*>(context->argument(1));
            int _q_arg2 = context->argument(2).toInt32();
            _q_self->setUniformValueArray(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isNumber()
            && qscriptvalue_cast<const QVector4D*>(context->argument(1))
            && context->argument(2).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            const QVector4D* _q_arg1 = qscriptvalue_cast<const QVector4D*>(context->argument(1));
            int _q_arg2 = context->argument(2).toInt32();
            _q_self->setUniformValueArray(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 33:
    if (context->argumentCount() == 0) {
        QList<QGLShader* > _q_result = _q_self->shaders();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 34:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QByteArray>() == context->argument(0).toVariant().userType())) {
            QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
            int _q_result = _q_self->uniformLocation(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if (context->argument(0).isString()) {
            QString _q_arg0 = context->argument(0).toString();
            int _q_result = _q_self->uniformLocation(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        } else if (qscriptvalue_cast<const char*>(context->argument(0))) {
            const char* _q_arg0 = qscriptvalue_cast<const char*>(context->argument(0));
            int _q_result = _q_self->uniformLocation(_q_arg0);
            return QScriptValue(context->engine(), _q_result);
        }
    }
    break;

    case 35: {
    QString result = QString::fromLatin1("QGLShaderProgram");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGLShaderProgram_throw_ambiguity_error_helper(context,
        qtscript_QGLShaderProgram_function_names[_id+2],
        qtscript_QGLShaderProgram_function_signatures[_id+2]);
}

static QScriptValue qtscript_QGLShaderProgram_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QGLShaderProgram(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QGLShaderProgram* _q_cpp_result = new QtScriptShell_QGLShaderProgram();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QGLShaderProgram*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (context->argument(0).isQObject()) {
            QObject* _q_arg0 = context->argument(0).toQObject();
            QtScriptShell_QGLShaderProgram* _q_cpp_result = new QtScriptShell_QGLShaderProgram(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QGLShaderProgram*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (qscriptvalue_cast<const QGLContext*>(context->argument(0))) {
            const QGLContext* _q_arg0 = qscriptvalue_cast<const QGLContext*>(context->argument(0));
            QtScriptShell_QGLShaderProgram* _q_cpp_result = new QtScriptShell_QGLShaderProgram(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QGLShaderProgram*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        const QGLContext* _q_arg0 = qscriptvalue_cast<const QGLContext*>(context->argument(0));
        QObject* _q_arg1 = context->argument(1).toQObject();
        QtScriptShell_QGLShaderProgram* _q_cpp_result = new QtScriptShell_QGLShaderProgram(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QGLShaderProgram*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        bool _q_result = QGLShaderProgram::hasOpenGLShaderPrograms();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        const QGLContext* _q_arg0 = qscriptvalue_cast<const QGLContext*>(context->argument(0));
        bool _q_result = QGLShaderProgram::hasOpenGLShaderPrograms(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGLShaderProgram_throw_ambiguity_error_helper(context,
        qtscript_QGLShaderProgram_function_names[_id],
        qtscript_QGLShaderProgram_function_signatures[_id]);
}

static QScriptValue qtscript_QGLShaderProgram_toScriptValue(QScriptEngine *engine, QGLShaderProgram* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QGLShaderProgram_fromScriptValue(const QScriptValue &value, QGLShaderProgram* &out)
{
    out = qobject_cast<QGLShaderProgram*>(value.toQObject());
}

QScriptValue qtscript_create_QGLShaderProgram_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QGLShaderProgram*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QGLShaderProgram*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 36; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QGLShaderProgram_prototype_call, qtscript_QGLShaderProgram_function_lengths[i+2]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QGLShaderProgram_function_names[i+2]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QGLShaderProgram*>(engine, qtscript_QGLShaderProgram_toScriptValue, 
        qtscript_QGLShaderProgram_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QGLShaderProgram_static_call, proto, qtscript_QGLShaderProgram_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 1; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QGLShaderProgram_static_call,
            qtscript_QGLShaderProgram_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QGLShaderProgram_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    return ctor;
}
