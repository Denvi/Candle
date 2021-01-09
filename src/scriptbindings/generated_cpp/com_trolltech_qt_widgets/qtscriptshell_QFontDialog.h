#ifndef QTSCRIPTSHELL_QFONTDIALOG_H
#define QTSCRIPTSHELL_QFONTDIALOG_H

#include <qfontdialog.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QFontDialog : public QFontDialog
{
public:
    QtScriptShell_QFontDialog(QWidget*  parent = 0);
    QtScriptShell_QFontDialog(const QFont&  initial, QWidget*  parent = 0);
    ~QtScriptShell_QFontDialog();

    void accept();
    void actionEvent(QActionEvent*  event);
    void changeEvent(QEvent*  event);
    void childEvent(QChildEvent*  event);
    void closeEvent(QCloseEvent*  arg__1);
    void contextMenuEvent(QContextMenuEvent*  arg__1);
    void customEvent(QEvent*  event);
    int  devType() const;
    void done(int  result);
    void dragEnterEvent(QDragEnterEvent*  event);
    void dragLeaveEvent(QDragLeaveEvent*  event);
    void dragMoveEvent(QDragMoveEvent*  event);
    void dropEvent(QDropEvent*  event);
    void enterEvent(QEvent*  event);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  object, QEvent*  event);
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

#endif // QTSCRIPTSHELL_QFONTDIALOG_H
