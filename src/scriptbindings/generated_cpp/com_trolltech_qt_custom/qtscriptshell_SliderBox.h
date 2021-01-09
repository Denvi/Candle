#ifndef QTSCRIPTSHELL_SLIDERBOX_H
#define QTSCRIPTSHELL_SLIDERBOX_H

#include <sliderbox.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_SliderBox : public SliderBox
{
public:
    QtScriptShell_SliderBox(QWidget*  parent = 0);
    ~QtScriptShell_SliderBox();

    void actionEvent(QActionEvent*  event);
    void changeEvent(QEvent*  arg__1);
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
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  watched, QEvent*  event);
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
    QSize  minimumSizeHint() const;
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
    QSize  sizeHint() const;
    void tabletEvent(QTabletEvent*  event);
    void timerEvent(QTimerEvent*  event);
    void wheelEvent(QWheelEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_SLIDERBOX_H
