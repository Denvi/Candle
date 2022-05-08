#ifndef QTSCRIPTSHELL_QERRORMESSAGE_H
#define QTSCRIPTSHELL_QERRORMESSAGE_H

#include <qerrormessage.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QErrorMessage : public QErrorMessage
{
public:
    QtScriptShell_QErrorMessage(QWidget*  parent = 0);
    ~QtScriptShell_QErrorMessage();

    void accept();
    void actionEvent(QActionEvent*  event);
    void changeEvent(QEvent*  e);
    void childEvent(QChildEvent*  event);
    void closeEvent(QCloseEvent*  arg__1);
    void contextMenuEvent(QContextMenuEvent*  arg__1);
    void customEvent(QEvent*  event);
    int  devType() const;
    void done(int  arg__1);
    void dragEnterEvent(QDragEnterEvent*  event);
    void dragLeaveEvent(QDragLeaveEvent*  event);
    void dragMoveEvent(QDragMoveEvent*  event);
    void dropEvent(QDropEvent*  event);
    void enterEvent(QEvent*  event);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    int  exec();
    void focusInEvent(QFocusEvent*  event);
    bool  focusNextPrevChild(bool  next);
    void focusOutEvent(QFocusEvent*  event);
    bool  hasHeightForWidth() const;
    int  heightForWidth(int  arg__1) const;
    void hideEvent(QHideEvent*  event);
    void initPainter(QPainter*  painter) const;
    void inputMethodEvent(QInputMethodEvent*  arg__1);
    QVariant  inputMethodQuery(Qt::InputMethodQuery  arg__1) const;
    void keyPressEvent(QKeyEvent*  arg__1);
    void keyReleaseEvent(QKeyEvent*  event);
    void leaveEvent(QEvent*  event);
    int  metric(QPaintDevice::PaintDeviceMetric  arg__1) const;
    void mouseDoubleClickEvent(QMouseEvent*  event);
    void mouseMoveEvent(QMouseEvent*  event);
    void mousePressEvent(QMouseEvent*  event);
    void mouseReleaseEvent(QMouseEvent*  event);
    void moveEvent(QMoveEvent*  event);
    bool  nativeEvent(const QByteArray&  eventType, void*  message, long*  result);
    void open();
    QPaintEngine*  paintEngine() const;
    void paintEvent(QPaintEvent*  event);
    QPaintDevice*  redirected(QPoint*  offset) const;
    void reject();
    void resizeEvent(QResizeEvent*  arg__1);
    QPainter*  sharedPainter() const;
    void showEvent(QShowEvent*  arg__1);
    void tabletEvent(QTabletEvent*  event);
    void timerEvent(QTimerEvent*  event);
    void wheelEvent(QWheelEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QERRORMESSAGE_H
