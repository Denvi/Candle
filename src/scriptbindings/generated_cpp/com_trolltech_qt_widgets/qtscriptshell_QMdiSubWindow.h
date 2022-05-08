#ifndef QTSCRIPTSHELL_QMDISUBWINDOW_H
#define QTSCRIPTSHELL_QMDISUBWINDOW_H

#include <qmdisubwindow.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QMdiSubWindow : public QMdiSubWindow
{
public:
    QtScriptShell_QMdiSubWindow(QWidget*  parent = 0, Qt::WindowFlags  flags = Qt::WindowFlags());
    ~QtScriptShell_QMdiSubWindow();

    void actionEvent(QActionEvent*  event);
    void changeEvent(QEvent*  changeEvent);
    void childEvent(QChildEvent*  childEvent);
    void closeEvent(QCloseEvent*  closeEvent);
    void contextMenuEvent(QContextMenuEvent*  contextMenuEvent);
    void customEvent(QEvent*  event);
    int  devType() const;
    void dragEnterEvent(QDragEnterEvent*  event);
    void dragLeaveEvent(QDragLeaveEvent*  event);
    void dragMoveEvent(QDragMoveEvent*  event);
    void dropEvent(QDropEvent*  event);
    void enterEvent(QEvent*  event);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  object, QEvent*  event);
    void focusInEvent(QFocusEvent*  focusInEvent);
    bool  focusNextPrevChild(bool  next);
    void focusOutEvent(QFocusEvent*  focusOutEvent);
    bool  hasHeightForWidth() const;
    int  heightForWidth(int  arg__1) const;
    void hideEvent(QHideEvent*  hideEvent);
    void initPainter(QPainter*  painter) const;
    void inputMethodEvent(QInputMethodEvent*  arg__1);
    QVariant  inputMethodQuery(Qt::InputMethodQuery  arg__1) const;
    void keyPressEvent(QKeyEvent*  keyEvent);
    void keyReleaseEvent(QKeyEvent*  event);
    void leaveEvent(QEvent*  leaveEvent);
    int  metric(QPaintDevice::PaintDeviceMetric  arg__1) const;
    void mouseDoubleClickEvent(QMouseEvent*  mouseEvent);
    void mouseMoveEvent(QMouseEvent*  mouseEvent);
    void mousePressEvent(QMouseEvent*  mouseEvent);
    void mouseReleaseEvent(QMouseEvent*  mouseEvent);
    void moveEvent(QMoveEvent*  moveEvent);
    bool  nativeEvent(const QByteArray&  eventType, void*  message, long*  result);
    QPaintEngine*  paintEngine() const;
    void paintEvent(QPaintEvent*  paintEvent);
    QPaintDevice*  redirected(QPoint*  offset) const;
    void resizeEvent(QResizeEvent*  resizeEvent);
    QPainter*  sharedPainter() const;
    void showEvent(QShowEvent*  showEvent);
    void tabletEvent(QTabletEvent*  event);
    void timerEvent(QTimerEvent*  timerEvent);
    void wheelEvent(QWheelEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QMDISUBWINDOW_H
