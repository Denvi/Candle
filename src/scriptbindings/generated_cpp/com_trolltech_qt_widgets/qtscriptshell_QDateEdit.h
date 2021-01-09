#ifndef QTSCRIPTSHELL_QDATEEDIT_H
#define QTSCRIPTSHELL_QDATEEDIT_H

#include <qdatetimeedit.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QDateEdit : public QDateEdit
{
public:
    QtScriptShell_QDateEdit(QWidget*  parent = 0);
    QtScriptShell_QDateEdit(const QDate&  date, QWidget*  parent = 0);
    ~QtScriptShell_QDateEdit();

    void actionEvent(QActionEvent*  event);
    void changeEvent(QEvent*  event);
    void childEvent(QChildEvent*  event);
    void clear();
    void closeEvent(QCloseEvent*  event);
    void contextMenuEvent(QContextMenuEvent*  event);
    void customEvent(QEvent*  event);
    QDateTime  dateTimeFromText(const QString&  text) const;
    int  devType() const;
    void dragEnterEvent(QDragEnterEvent*  event);
    void dragLeaveEvent(QDragLeaveEvent*  event);
    void dragMoveEvent(QDragMoveEvent*  event);
    void dropEvent(QDropEvent*  event);
    void enterEvent(QEvent*  event);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    void fixup(QString&  input) const;
    void focusInEvent(QFocusEvent*  event);
    bool  focusNextPrevChild(bool  next);
    void focusOutEvent(QFocusEvent*  event);
    bool  hasHeightForWidth() const;
    int  heightForWidth(int  arg__1) const;
    void hideEvent(QHideEvent*  event);
    void initPainter(QPainter*  painter) const;
    void inputMethodEvent(QInputMethodEvent*  arg__1);
    QVariant  inputMethodQuery(Qt::InputMethodQuery  arg__1) const;
    void keyPressEvent(QKeyEvent*  event);
    void keyReleaseEvent(QKeyEvent*  event);
    void leaveEvent(QEvent*  event);
    int  metric(QPaintDevice::PaintDeviceMetric  arg__1) const;
    void mouseDoubleClickEvent(QMouseEvent*  event);
    void mouseMoveEvent(QMouseEvent*  event);
    void mousePressEvent(QMouseEvent*  event);
    void mouseReleaseEvent(QMouseEvent*  event);
    void moveEvent(QMoveEvent*  event);
    bool  nativeEvent(const QByteArray&  eventType, void*  message, long*  result);
    QPaintEngine*  paintEngine() const;
    void paintEvent(QPaintEvent*  event);
    QPaintDevice*  redirected(QPoint*  offset) const;
    void resizeEvent(QResizeEvent*  event);
    QPainter*  sharedPainter() const;
    void showEvent(QShowEvent*  event);
    void stepBy(int  steps);
    QAbstractSpinBox::StepEnabled  stepEnabled() const;
    void tabletEvent(QTabletEvent*  event);
    QString  textFromDateTime(const QDateTime&  dt) const;
    void timerEvent(QTimerEvent*  event);
    QValidator::State  validate(QString&  input, int&  pos) const;
    void wheelEvent(QWheelEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QDATEEDIT_H
