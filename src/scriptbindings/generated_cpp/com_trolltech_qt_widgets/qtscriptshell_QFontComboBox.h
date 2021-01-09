#ifndef QTSCRIPTSHELL_QFONTCOMBOBOX_H
#define QTSCRIPTSHELL_QFONTCOMBOBOX_H

#include <qfontcombobox.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QFontComboBox : public QFontComboBox
{
public:
    QtScriptShell_QFontComboBox(QWidget*  parent = 0);
    ~QtScriptShell_QFontComboBox();

    void actionEvent(QActionEvent*  event);
    void changeEvent(QEvent*  e);
    void childEvent(QChildEvent*  event);
    void closeEvent(QCloseEvent*  event);
    void contextMenuEvent(QContextMenuEvent*  e);
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
    void hideEvent(QHideEvent*  e);
    void hidePopup();
    void initPainter(QPainter*  painter) const;
    void inputMethodEvent(QInputMethodEvent*  arg__1);
    QVariant  inputMethodQuery(Qt::InputMethodQuery  arg__1) const;
    void keyPressEvent(QKeyEvent*  e);
    void keyReleaseEvent(QKeyEvent*  e);
    void leaveEvent(QEvent*  event);
    int  metric(QPaintDevice::PaintDeviceMetric  arg__1) const;
    void mouseDoubleClickEvent(QMouseEvent*  event);
    void mouseMoveEvent(QMouseEvent*  event);
    void mousePressEvent(QMouseEvent*  e);
    void mouseReleaseEvent(QMouseEvent*  e);
    void moveEvent(QMoveEvent*  event);
    bool  nativeEvent(const QByteArray&  eventType, void*  message, long*  result);
    QPaintEngine*  paintEngine() const;
    void paintEvent(QPaintEvent*  e);
    QPaintDevice*  redirected(QPoint*  offset) const;
    void resizeEvent(QResizeEvent*  e);
    QPainter*  sharedPainter() const;
    void showEvent(QShowEvent*  e);
    void showPopup();
    void tabletEvent(QTabletEvent*  event);
    void timerEvent(QTimerEvent*  event);
    void wheelEvent(QWheelEvent*  e);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QFONTCOMBOBOX_H
