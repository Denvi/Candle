#include "jshighlighter.h"

JSHighlighter::JSHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    m_keywordFormat.setForeground(Qt::blue);
    m_keywordFormat.setFontWeight(QFont::Bold);

    m_builtInFormat.setForeground(QColor(0, 128, 128));

    m_singleLineCommentFormat.setForeground(Qt::darkGreen);
    m_multiLineCommentFormat.setForeground(Qt::darkGreen);

    m_quotationFormat.setForeground(Qt::darkRed);

    m_functionFormat.setForeground(QColor(200, 0, 100));
    m_functionFormat.setFontItalic(true);

    m_numberFormat.setForeground(Qt::darkBlue);

    m_operatorFormat.setForeground(Qt::darkMagenta);

    QStringList keywordPatterns = {
        "\\bbreak\\b", "\\bcase\\b", "\\bcatch\\b", "\\bcontinue\\b",
        "\\bdebugger\\b", "\\bdefault\\b", "\\bdelete\\b", "\\bdo\\b",
        "\\belse\\b", "\\bfinally\\b", "\\bfor\\b", "\\bfunction\\b",
        "\\bif\\b", "\\bin\\b", "\\binstanceof\\b", "\\bnew\\b",
        "\\breturn\\b", "\\bswitch\\b", "\\bthis\\b", "\\bthrow\\b",
        "\\btry\\b", "\\btypeof\\b", "\\bvar\\b", "\\bvoid\\b",
        "\\bwhile\\b", "\\bwith\\b", "\\bimport\\b", "\\bexport\\b",
        "\\bconst\\b", "\\blet\\b", "\\bclass\\b", "\\bextends\\b",
        "\\bsuper\\b", "\\byield\\b", "\\benum\\b", "\\bawait\\b",
        "\\bimplements\\b", "\\bpackage\\b", "\\bprotected\\b",
        "\\bstatic\\b", "\\binterface\\b", "\\bprivate\\b",
        "\\bpublic\\b", "\\bnull\\b", "\\bundefined\\b",
        "\\btrue\\b", "\\bfalse\\b"
    };

    QStringList builtInPatterns = {
        "\\bArray\\b", "\\bBoolean\\b", "\\bDate\\b", "\\bError\\b",
        "\\bEvalError\\b", "\\bFunction\\b", "\\bJSON\\b", "\\bMath\\b",
        "\\bNumber\\b", "\\bObject\\b", "\\bRangeError\\b", "\\bReferenceError\\b",
        "\\bRegExp\\b", "\\bString\\b", "\\bSyntaxError\\b", "\\bTypeError\\b",
        "\\bURIError\\b", "\\bdocument\\b", "\\bwindow\\b", "\\bconsole\\b",
        "\\blocation\\b", "\\bsetTimeout\\b", "\\bclearTimeout\\b",
        "\\bsetInterval\\b", "\\bclearInterval\\b", "\\bparseInt\\b",
        "\\bparseFloat\\b", "\\bisNaN\\b", "\\bisFinite\\b", "\\bdecodeURI\\b",
        "\\bdecodeURIComponent\\b", "\\bencodeURI\\b", "\\bencodeURIComponent\\b",
        "\\bescape\\b", "\\bunescape\\b", "\\beval\\b", "\\bPromise\\b"
    };

    foreach (const QString &pattern, keywordPatterns) {
        HighlightingRule rule;
        rule.pattern = QRegularExpression(pattern);
        rule.format = m_keywordFormat;
        m_highlightingRules.append(rule);
    }

    foreach (const QString &pattern, builtInPatterns) {
        HighlightingRule rule;
        rule.pattern = QRegularExpression(pattern);
        rule.format = m_builtInFormat;
        m_highlightingRules.append(rule);
    }

    // Operators
    HighlightingRule rule;
    rule.pattern = QRegularExpression("[\\+\\-\\*\\/\\=\\&\\|\\!\\<\\>\\?\\:\\;\\{\\}\\[\\]\\(\\)\\,\\.\\^\\%]");
    rule.format = m_operatorFormat;
    m_highlightingRules.append(rule);

    // Numbers
    rule.pattern = QRegularExpression("\\b[0-9]+\\.?[0-9]*([eE][+-]?[0-9]+)?\\b");
    rule.format = m_numberFormat;
    m_highlightingRules.append(rule);

    // Functions
    rule.pattern = QRegularExpression("\\b[A-Za-z0-9_]+(?=\\()");
    rule.format = m_functionFormat;
    m_highlightingRules.append(rule);

    // Single quote string
    rule.pattern = QRegularExpression("'[^']*'");
    rule.format = m_quotationFormat;
    m_highlightingRules.append(rule);

    // Double quote string
    rule.pattern = QRegularExpression("\"[^\"]*\"");
    rule.format = m_quotationFormat;
    m_highlightingRules.append(rule);

    // Single line comments
    rule.pattern = QRegularExpression("//[^\n]*");
    rule.format = m_singleLineCommentFormat;
    m_highlightingRules.append(rule);

    // Multiline comments
    m_commentStartExpression = QRegularExpression("/\\*");
    m_commentEndExpression = QRegularExpression("\\*/");
}

void JSHighlighter::highlightBlock(const QString &text)
{
    foreach (const HighlightingRule &rule, m_highlightingRules) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }

    // Processing multiline comments
    setCurrentBlockState(0);

    int startIndex = 0;
    if (previousBlockState() != 1)
        startIndex = text.indexOf(m_commentStartExpression);

    while (startIndex >= 0) {
        QRegularExpressionMatch match = m_commentEndExpression.match(text, startIndex);
        int endIndex = match.capturedStart();
        int commentLength = 0;

        if (endIndex == -1) {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else {
            commentLength = endIndex - startIndex + match.capturedLength();
        }

        setFormat(startIndex, commentLength, m_multiLineCommentFormat);
        startIndex = text.indexOf(m_commentStartExpression, startIndex + commentLength);
    }
}