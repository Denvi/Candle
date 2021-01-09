#ifndef QTSCRIPTSHELL_QRADIOBUTTON_H
#define QTSCRIPTSHELL_QRADIOBUTTON_H

#include <qradiobutton.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QRadioButton : public QRadioButton
{
public:
    QtScriptShell_QRadioButton(QWidget*  parent = 0);
    QtScriptShell_QRadioButton(const QString&  text, QWidget*  parent = 0);
    ~QtScriptShell_QRadioButton();

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
    void focusInEvent(QFocusEvent*  e);
    bool  focusNextPrevChild(bool  next);
    void focusOutEvent(QFocusEvent*  e);
    bool  hasHeightForWidth() const;
    int  heightForWidth(int  arg__1) const;
    void hideEvent(QHideEvent*  event);
    bool  hitButton(const QPoint&  arg__1) const;
    void initPainter(QPainter*  painter) const;
    void inputMethodEvent(QInputMethodEvent*  arg__1);
    QVariant  inputMethodQuery(Qt::InputMethodQuery  arg__1) const;
    void keyPressEvent(QKeyEvent*  e);
    void keyReleaseEvent(QKeyEvent*  e);
    void leaveEvent(QEvent*  event);
    int  metric(QPaintDevice::PaintDeviceMetric  arg__1) const;
    void mouseDoubleClickEvent(QMouseEvent*  event);
    void mouseMoveEvent(QMouseEvent*  arg__1);
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

#endif // QTSCRIPTSHELL_QRADIOBUTTON_H
