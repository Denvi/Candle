#pragma once

#include <QTextBrowser>

class QHelpEngine;

class HelpBrowser : public QTextBrowser
{
public:
    HelpBrowser(QHelpEngine *helpEngine, QWidget *parent = 0);

    QVariant loadResource(int type, const QUrl &name) override;

protected:
    bool event(QEvent *ev) override;

private:
    QHelpEngine *m_helpEngine;
};