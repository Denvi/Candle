#include "scriptedit.h"
#include <QKeyEvent>
#include <QMimeData>
#include <QFontDatabase>
#include <QTextBlock>

ScriptEdit::ScriptEdit(QWidget *parent)
    : QTextEdit(parent)
{
    QFontMetrics fontMetrics(font());
    setTabStopDistance(fontMetrics.horizontalAdvance(' ') * 4);

    m_highlighter = new JSHighlighter(document());
}

ScriptEdit::ScriptEdit(const QString& text, QWidget *parent)
    : ScriptEdit(parent)
{
    setText(text);
}

void ScriptEdit::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Tab) {
        handleTabKey();
    }
    else if (event->key() == Qt::Key_Backtab) {
        handleBackTabKey();
    }
    else if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        handleEnterKey();
    }
    else {
        QTextEdit::keyPressEvent(event);
    }
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

void ScriptEdit::insertFromMimeData(const QMimeData *source)
{
    if (source->hasText()) {
        insertPlainText(source->text());
    }
}