#include "helpbrowser.h"
#include <QHelpEngine>
#include <QMouseEvent>
#include <QDesktopServices>
#include <QDebug>

HelpBrowser::HelpBrowser(QWidget *parent) : QTextBrowser(parent)
{
    document()->setDocumentMargin(11);
    setOpenExternalLinks(false);
    setOpenLinks(false);

    connect(this, &QTextBrowser::anchorClicked, [this](const QUrl &url) {
        if (url.scheme().startsWith("http")) {
            QDesktopServices::openUrl(url);
        } else {
            setSource(url);
        }
    });
}

void HelpBrowser::setHelpEngine(QHelpEngine *helpEngine)
{
    m_helpEngine = helpEngine;
}

QVariant HelpBrowser::loadResource(int type, const QUrl &name)
{
    if (name.scheme() == "qthelp" && m_helpEngine)
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