#pragma once

#include <QTextBrowser>

class QHelpEngine;

class HelpBrowser : public QTextBrowser
{
public:
    HelpBrowser(QWidget *parent = 0);

    void setHelpEngine(QHelpEngine *helpEngine);

    QVariant loadResource(int type, const QUrl &name) override;

protected:
    bool event(QEvent *ev) override;

private:
    QHelpEngine *m_helpEngine;
};