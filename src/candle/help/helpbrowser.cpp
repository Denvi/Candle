#include "helpbrowser.h"
#include <QHelpEngine>
#include <QMouseEvent>
#include <QDebug>

HelpBrowser::HelpBrowser(QHelpEngine *helpEngine, QWidget *parent) : QTextBrowser(parent), m_helpEngine(helpEngine)
{
    document()->setDocumentMargin(11);
    setOpenExternalLinks(true);
}

QVariant HelpBrowser::loadResource(int type, const QUrl &name)
{
    if (name.scheme() == "qthelp")
    {
        return QVariant(m_helpEngine->fileData(name));
    }
    else
    {
        return QTextBrowser::loadResource(type, name);
    }
}

bool HelpBrowser::event(QEvent *ev)
{
    if (ev->type() == QEvent::MouseButtonPress)
    {
        auto *me = static_cast<QMouseEvent*>(ev);

        if (me->button() == Qt::XButton1) {
            backward();
            return true;
        }
        if (me->button() == Qt::XButton2) {
            forward();
            return true;
        }
    }

    return QTextBrowser::event(ev);
}