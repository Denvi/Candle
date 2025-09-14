#pragma once

#include <QTextEdit>
#include "jshighlighter.h"
#include "customwidgetsshared.h"

class CUSTOMWIDGETS_DLLSPEC ScriptEdit : public QTextEdit
{
    Q_OBJECT

public:
    explicit ScriptEdit(QWidget *parent = nullptr);
    explicit ScriptEdit(const QString& text, QWidget* parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void insertFromMimeData(const QMimeData *source) override;

private:
    void handleTabKey();
    void handleBackTabKey();
    void handleEnterKey();
    JSHighlighter *m_highlighter;
};