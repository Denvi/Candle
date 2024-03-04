#include "scripting.h"
#include <QGuiApplication>
#include <QSettings>
#include <QDir>
#include <QFile>
#include <QScriptEngine>
#include <QScriptValue>
#include <QScriptValueIterator>
#include <QScriptContext>
#include <QDebug>
#include <QTranslator>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QDockWidget>

Scripting::Scripting(Configuration *configuration): m_configuration(configuration)
{
}

void Scripting::loadPlugins(QWidget *ui)
{
    QString pluginsDir = qApp->applicationDirPath() + "/plugins/";

    // Get plugins list
    QStringList pl = QDir(pluginsDir).entryList(QDir::Dirs | QDir::NoDotAndDotDot);

    qDebug() << "Loading plugins:" << pl;

    foreach (QString p, pl) {
        // Config
        QSettings set(pluginsDir + p + "/config.ini", QSettings::IniFormat);
        QString title = set.value("title").toString();
        QString name = set.value("name").toString();
        qDebug() << "Loading plugin:" << p << title << name;

        // Translation
        QString loc = m_configuration->language();
        QString translationFileName = pluginsDir + p + "/translation_" + loc + ".qm";
        if(QFile::exists(translationFileName)) {
            QTranslator *translator = new QTranslator();
            if (translator->load(translationFileName)) qApp->installTranslator(translator);
            else delete translator;
        }

        // Script
        QFile f;
        f.setFileName(pluginsDir + p + "/script.js");
        if (f.open(QFile::ReadOnly)) {
            QScriptEngine *se = new QScriptEngine();

            QScriptValue sv = se->newObject();
            sv.setProperty("importExtension", se->newFunction(Scripting::importExtension));
            sv.setProperty("path", pluginsDir + p);
            se->globalObject().setProperty("script", sv);
            connect(se, &QScriptEngine::signalHandlerException, this, &Scripting::onScriptException);

            // Delegate objects
            // Main form
            QScriptValue app = se->newQObject(&m_scriptFunctions);
            app.setProperty("path", qApp->applicationDirPath());
            se->globalObject().setProperty("app", app);

            // // Settings
            QScriptValue settings = se->newQObject(m_configuration);
            app.setProperty("settings", settings);

            // Stored vars
            QScriptValue vars = se->newQObject(&m_storedVars);
            se->globalObject().setProperty("vars", vars);

            // Translator
            se->installTranslatorFunctions();

            // Run script
            QString script = f.readAll();

            qDebug() << "Starting plugin:" << p;
            sv = se->evaluate(script);
            if (sv.isError()) {
                qDebug() << sv.toString();
                qDebug() << se->uncaughtExceptionBacktrace();
            }

            // Init
            sv = se->evaluate("init()");
            if (sv.isError()) {
                qDebug() << sv.toString();
                qDebug() << se->uncaughtExceptionBacktrace();
            }

            // Panel widget
            sv = se->evaluate("createPanelWidget()");
            if (sv.isError()) {
                qDebug() << sv.toString();
                qDebug() << se->uncaughtExceptionBacktrace();
            } else {
                QWidget *w = qobject_cast<QWidget*>(sv.toQObject());
                if (w) {
                    // Create panel
                    QGroupBox *box = new QGroupBox(ui);
                    QVBoxLayout *layout1 = new QVBoxLayout(box);
                    QWidget *bw = new QWidget(box);
                    QVBoxLayout *layout2 = new QVBoxLayout(bw);
                    box->setObjectName("grp" + name);
                    box->setTitle(tr(title.toLatin1()));
                    box->setLayout(layout1);
                    box->setCheckable(true);
                    box->setProperty("overrided", false);
                    layout1->addWidget(bw);
                    bw->setLayout(layout2);
                    layout2->addWidget(w);
                    layout2->setMargin(0);
                    connect(box, &QGroupBox::toggled, bw, &QWidget::setVisible);

                    // Add panel to user window
                    // @TODO ui
                    // static_cast<QVBoxLayout*>(ui->scrollContentsUser->layout())->insertWidget(0, box);
                }
            }

            // Window widget
            sv = se->evaluate("createWindowWidget()");
            if (sv.isError()) {
                qDebug() << sv.toString();
                qDebug() << se->uncaughtExceptionBacktrace();
            } else {
                QWidget *w = qobject_cast<QWidget*>(sv.toQObject());
                if (w) {
                    // Create dock widget
                    QDockWidget *dock = new QDockWidget(ui);
                    QWidget *contents = new QWidget(dock);
                    QFrame *frame = new QFrame(contents);
                    QVBoxLayout *layout1 = new QVBoxLayout(contents);
                    QVBoxLayout *layout2 = new QVBoxLayout(frame);
                    dock->setObjectName("dock" + name);
                    dock->setWindowTitle(tr(title.toLatin1()));
                    dock->setWidget(contents);
                    contents->setLayout(layout1);
                    layout1->addWidget(frame);
                    QMargins m = layout1->contentsMargins();
                    m.setLeft(0);
                    m.setRight(0);
                    layout1->setContentsMargins(m);
                    frame->setLayout(layout2);
                    layout2->addWidget(w);
                    layout2->setMargin(0);

                    // Add to main form
                    // @TODO ui
                    // this->addDockWidget(Qt::RightDockWidgetArea, dock);
                }
            }

            // Settings widget
            sv = se->evaluate("createSettingsWidget()");
            if (sv.isError()) {
                qDebug() << sv.toString();
                qDebug() << se->uncaughtExceptionBacktrace();
            } else {
                QWidget *w = qobject_cast<QWidget*>(sv.toQObject());
                if (w) {
                    // Create groupbox
                    // @TODO ui settings instead of ui main!
                    QGroupBox *box = new QGroupBox(ui);
                    QVBoxLayout *layout1 = new QVBoxLayout(box);
                    box->setObjectName("grpSettings" + name);
                    box->setTitle(tr(title.toLatin1()));
                    box->setLayout(layout1);
                    layout1->addWidget(w);

                    // Add to settings form
                    // @TODO ui settings
                    // m_settings->addCustomSettings(box);
                }
            }

            f.close();
        }
    }
}

void Scripting::onScriptException(const QScriptValue &exception)
{
    qDebug() << "Script exception:" << exception.toString();
}

QScriptValue Scripting::importExtension(QScriptContext *context, QScriptEngine *engine)
{
    return engine->importExtension(context->argument(0).toString());
}
