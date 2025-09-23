#include "scriptedit.h"
#include <QKeyEvent>
#include <QMimeData>
#include <QFontDatabase>
#include <QTextBlock>
#include <QAbstractItemView>
#include <QStringListModel>
#include <QScrollBar>

ScriptEdit::ScriptEdit(QWidget *parent)
    : QTextEdit(parent)
{
    QFontMetrics fontMetrics(font());
    setTabStopDistance(fontMetrics.horizontalAdvance(' ') * 4);

    m_highlighter = new JSHighlighter(document());

    m_completer = new QCompleter(this);
    m_completer->setWidget(this);
    m_completer->setCompletionMode(QCompleter::PopupCompletion);
    m_completer->setCaseSensitivity(Qt::CaseSensitive);
    m_completer->setWrapAround(false);
    m_completer->setModel(new QStringListModel(m_apiEntries));

    connect(m_completer, QOverload<const QString&>::of(&QCompleter::activated), this, &ScriptEdit::insertCompletion);
}

ScriptEdit::ScriptEdit(const QString& text, QWidget *parent)
    : ScriptEdit(parent)
{
    setText(text);
}

void ScriptEdit::keyPressEvent(QKeyEvent *e)
{
    if (m_completer && m_completer->popup()->isVisible()) {
        // The following keys are forwarded by the completer to the widget
       switch (e->key()) {
       case Qt::Key_Enter:
       case Qt::Key_Return:
       case Qt::Key_Escape:
       case Qt::Key_Tab:
       case Qt::Key_Backtab:
            e->ignore();
            return; // let the completer do default behavior
       default:
           break;
       }
    }

    if (e->key() == Qt::Key_Tab) {
        handleTabKey();
    }
    else if (e->key() == Qt::Key_Backtab) {
        handleBackTabKey();
    }
    else if (e->key() == Qt::Key_Return || e->key() == Qt::Key_Enter) {
        handleEnterKey();
    }
    else {
        QTextEdit::keyPressEvent(e);
    }

    const bool ctrlOrShift = e->modifiers().testFlag(Qt::ControlModifier) || e->modifiers().testFlag(Qt::ShiftModifier);
    if ((ctrlOrShift && e->text().isEmpty()))
        return;

    auto forbiddenKeys = QList<int> { Qt::Key_Tab, Qt::Key_Backtab, Qt::Key_Return, Qt::Key_Enter, Qt::Key_Delete,
        Qt::Key_Backspace, Qt::Key_Space };
    if (forbiddenKeys.contains(e->key()))
        return;

    static QString eow("~!@#$%^&*()_+{}|:\"<>?,./;'[]\\-="); // end of word
    const bool hasModifier = (e->modifiers() != Qt::NoModifier) && !ctrlOrShift;
    QString completionPrefix = textUnderCursor();
    if ((hasModifier || e->text().isEmpty()|| completionPrefix.length() < 1 || eow.contains(e->text().right(1)))) {
        m_completer->popup()->hide();
        return;
    }

    if (completionPrefix != m_completer->completionPrefix()) {
        m_completer->setCompletionPrefix(completionPrefix);
        m_completer->popup()->setCurrentIndex(m_completer->completionModel()->index(0, 0));
    }

    QRect cr = cursorRect();
    cr.setWidth(m_completer->popup()->sizeHintForColumn(0) + m_completer->popup()->verticalScrollBar()->sizeHint().width());
    m_completer->complete(cr);
}

void ScriptEdit::focusInEvent(QFocusEvent *e)
{
    if (m_completer)
        m_completer->setWidget(this);
    QTextEdit::focusInEvent(e);
}

void ScriptEdit::insertFromMimeData(const QMimeData *source)
{
    if (source->hasText()) {
        insertPlainText(source->text());
    }
}

void ScriptEdit::insertCompletion(const QString &completion)
{
    if (m_completer->widget() != this)
        return;
    QTextCursor tc = textCursor();
    int extra = completion.length() - m_completer->completionPrefix().length();
    tc.movePosition(QTextCursor::Left);
    tc.movePosition(QTextCursor::EndOfWord);
    tc.insertText(completion.right(extra));
    setTextCursor(tc);
}

void ScriptEdit::handleTabKey()
{
    QTextCursor cursor = textCursor();

    if (cursor.hasSelection()) {
        int start = cursor.selectionStart();
        int end = cursor.selectionEnd();

        cursor.setPosition(start);
        cursor.movePosition(QTextCursor::StartOfBlock);
        int startBlockPos = cursor.position();

        cursor.setPosition(end);
        bool endAtBlockStart = cursor.atBlockStart() && cursor.position() > 0;

        if (endAtBlockStart) {
            cursor.movePosition(QTextCursor::PreviousBlock);
        }

        cursor.movePosition(QTextCursor::EndOfBlock);
        int endBlockPos = cursor.position();

        int originalStart = start;
        int originalEnd = end;

        cursor.setPosition(startBlockPos);
        cursor.beginEditBlock();

        while (cursor.position() <= endBlockPos ||
              (endAtBlockStart && cursor.block().position() <= end)) {
            cursor.movePosition(QTextCursor::StartOfBlock);
            cursor.insertText("    ");

            if (cursor.position() <= originalStart)
                originalStart += 4;
            originalEnd += 4;
            endBlockPos += 4;

            if (!cursor.movePosition(QTextCursor::NextBlock)) {
                break;
            }
        }

        cursor.endEditBlock();

        cursor.setPosition(originalStart);
        cursor.setPosition(originalEnd, QTextCursor::KeepAnchor);
        setTextCursor(cursor);
    }
    else {
        cursor.insertText("    ");
    }
}

void ScriptEdit::handleBackTabKey()
{
    QTextCursor cursor = textCursor();

    cursor.beginEditBlock();

    if (cursor.hasSelection()) {
        int start = cursor.selectionStart();
        int end = cursor.selectionEnd();

        cursor.setPosition(start);
        cursor.movePosition(QTextCursor::StartOfBlock);
        int startBlockPos = cursor.position();

        cursor.setPosition(end);
        bool endAtBlockStart = cursor.atBlockStart() && cursor.position() > 0;

        if (endAtBlockStart) {
            cursor.movePosition(QTextCursor::PreviousBlock);
        }

        cursor.movePosition(QTextCursor::EndOfBlock);
        int endBlockPos = cursor.position();

        int originalStart = start;
        int originalEnd = end;

        cursor.setPosition(startBlockPos);

        while (cursor.position() <= endBlockPos ||
              (endAtBlockStart && cursor.block().position() <= end)) {
            cursor.movePosition(QTextCursor::StartOfBlock);

            QTextBlock block = cursor.block();
            QString text = block.text();
            int removeCount = 0;

            for (int i = 0; i < qMin(4, text.length()); ++i) {
                if (text[i] == ' ') {
                    removeCount++;
                } else {
                    break;
                }
            }

            if (removeCount > 0) {
                cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, removeCount);
                cursor.removeSelectedText();

                if (cursor.position() < originalStart)
                    originalStart -= removeCount;
                originalEnd -= removeCount;
                endBlockPos -= removeCount;
            }

            if (!cursor.movePosition(QTextCursor::NextBlock)) {
                break;
            }
        }

        cursor.endEditBlock();

        cursor.setPosition(originalStart);
        cursor.setPosition(originalEnd, QTextCursor::KeepAnchor);
        setTextCursor(cursor);
    }
    else {
        cursor.movePosition(QTextCursor::StartOfBlock);
        QTextBlock block = cursor.block();
        QString text = block.text();
        int removeCount = 0;

        for (int i = 0; i < qMin(4, text.length()); ++i) {
            if (text[i] == ' ') {
                removeCount++;
            } else {
                break;
            }
        }

        if (removeCount > 0) {
            cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, removeCount);
            cursor.removeSelectedText();
        }

        cursor.endEditBlock();
    }
}

void ScriptEdit::handleEnterKey()
{
    QTextCursor cursor = textCursor();
    QString currentLine = cursor.block().text();

    QTextEdit::insertPlainText("\n");

    QString indentation;
    for (int i = 0; i < currentLine.length(); ++i) {
        if (currentLine[i] == ' ' || currentLine[i] == '\t') {
            indentation += currentLine[i];
        } else {
            break;
        }
    }

    if (!indentation.isEmpty()) {
        QTextEdit::insertPlainText(indentation);
    }
}

QString ScriptEdit::textUnderCursor() const
{
    QTextCursor tc = textCursor();
    tc.select(QTextCursor::WordUnderCursor);
    return tc.selectedText();
}