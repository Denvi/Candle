#ifndef QTSCRIPTSHELL_QPUSHBUTTON_H
#define QTSCRIPTSHELL_QPUSHBUTTON_H

#include <qpushbutton.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QPushButton : public QPushButton
{
public:
    QtScriptShell_QPushButton(QWidget*  parent = 0);
    QtScriptShell_QPushButton(const QIcon&  icon, const QString&  text, QWidget*  parent = 0);
    QtScriptShell_QPushButton(const QString&  text, QWidget*  parent = 0);
    ~QtScriptShell_QPushButton();

    void actionEvent(QActionEvent*  event);
    void changeEvent(QEvent*  e);
    void checkStateSet();
    void childEvent(QChildEvent*  event);
    void closeEvent(QCloseEvent*  event);
    void contextMenuEvent(QContextMenuEvent*  event);
    void customEvent(QEvent*  event);
    int  devType() const;
    void dragEnterEvent(QDragEnterEvent*  event);
    void dragLeaveEvent(QDragLeaveEvent*  event);
    void dragMoveEvent(QDragMoveEvent*  event);
    void dropEvent(QDropEvent*  event);
    void enterEvent(QEvent*  event);
    bool  event(QEvent*  e);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    void focusInEvent(QFocusEvent*  arg__1);
    bool  focusNextPrevChild(bool  next);
    void focusOutEvent(QFocusEvent*  arg__1);
    bool  hasHeightForWidth() const;
    int  heightForWidth(int  arg__1) const;
    void hideEvent(QHideEvent*  event);
    bool  hitButton(const QPoint&  pos) const;
    void initPainter(QPainter*  painter) const;
    void inputMethodEvent(QInputMethodEvent*  arg__1);
    QVariant  inputMethodQuery(Qt::InputMethodQuery  arg__1) const;
    void keyPressEvent(QKeyEvent*  arg__1);
    void keyReleaseEvent(QKeyEvent*  e);
    void leaveEvent(QEvent*  event);
    int  metric(QPaintDevice::PaintDeviceMetric  arg__1) const;
    void mouseDoubleClickEvent(QMouseEvent*  event);
    void mouseMoveEvent(QMouseEvent*  e);
    void mousePressEvent(QMouseEvent*  e);
    void mouseReleaseEvent(QMouseEvent*  e);
    void moveEvent(QMoveEvent*  event);
    bool  nativeEvent(const QByteArray&  eventType, void*  message, long*  result);
    void nextCheckState();
    QPaintEngine*  paintEngine() const;
    void paintEvent(QPaintEvent*  arg__1);
    QPaintDevice*  redirected(QPoint*  offset) const;
    void resizeEvent(QResizeEvent*  event);
    QPainter*  sharedPainter() const;
    void showEvent(QShowEvent*  event);
    void tabletEvent(QTabletEvent*  event);
    void timerEvent(QTimerEvent*  e);
    void wheelEvent(QWheelEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QPUSHBUTTON_H
