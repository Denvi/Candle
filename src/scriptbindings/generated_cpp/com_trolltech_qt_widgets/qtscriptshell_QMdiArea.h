#ifndef QTSCRIPTSHELL_QMDIAREA_H
#define QTSCRIPTSHELL_QMDIAREA_H

#include <qmdiarea.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QMdiArea : public QMdiArea
{
public:
    QtScriptShell_QMdiArea(QWidget*  parent = 0);
    ~QtScriptShell_QMdiArea();

    void actionEvent(QActionEvent*  event);
    void changeEvent(QEvent*  arg__1);
    void childEvent(QChildEvent*  childEvent);
    void closeEvent(QCloseEvent*  event);
    void contextMenuEvent(QContextMenuEvent*  arg__1);
    void customEvent(QEvent*  event);
    int  devType() const;
    void dragEnterEvent(QDragEnterEvent*  arg__1);
    void dragLeaveEvent(QDragLeaveEvent*  arg__1);
    void dragMoveEvent(QDragMoveEvent*  arg__1);
    void dropEvent(QDropEvent*  arg__1);
    void enterEvent(QEvent*  event);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  object, QEvent*  event);
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
    void mouseDoubleClickEvent(QMouseEvent*  arg__1);
    void mouseMoveEvent(QMouseEvent*  arg__1);
    void mousePressEvent(QMouseEvent*  arg__1);
    void mouseReleaseEvent(QMouseEvent*  arg__1);
    void moveEvent(QMoveEvent*  event);
    bool  nativeEvent(const QByteArray&  eventType, void*  message, long*  result);
    QPaintEngine*  paintEngine() const;
    void paintEvent(QPaintEvent*  paintEvent);
    QPaintDevice*  redirected(QPoint*  offset) const;
    void resizeEvent(QResizeEvent*  resizeEvent);
    void scrollContentsBy(int  dx, int  dy);
    void setupViewport(QWidget*  viewport);
    QPainter*  sharedPainter() const;
    void showEvent(QShowEvent*  showEvent);
    void tabletEvent(QTabletEvent*  event);
    void timerEvent(QTimerEvent*  timerEvent);
    bool  viewportEvent(QEvent*  event);
    QSize  viewportSizeHint() const;
    void wheelEvent(QWheelEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QMDIAREA_H
