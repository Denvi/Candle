#ifndef QTSCRIPTSHELL_QTEXTEDIT_H
#define QTSCRIPTSHELL_QTEXTEDIT_H

#include <qtextedit.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QTextEdit : public QTextEdit
{
public:
    QtScriptShell_QTextEdit(QWidget*  parent = 0);
    QtScriptShell_QTextEdit(const QString&  text, QWidget*  parent = 0);
    ~QtScriptShell_QTextEdit();

    void actionEvent(QActionEvent*  event);
    bool  canInsertFromMimeData(const QMimeData*  source) const;
    void changeEvent(QEvent*  e);
    void childEvent(QChildEvent*  event);
    void closeEvent(QCloseEvent*  event);
    void contextMenuEvent(QContextMenuEvent*  e);
    QMimeData*  createMimeDataFromSelection() const;
    void customEvent(QEvent*  event);
    int  devType() const;
    void doSetTextCursor(const QTextCursor&  cursor);
    void dragEnterEvent(QDragEnterEvent*  e);
    void dragLeaveEvent(QDragLeaveEvent*  e);
    void dragMoveEvent(QDragMoveEvent*  e);
    void dropEvent(QDropEvent*  e);
    void enterEvent(QEvent*  event);
    bool  event(QEvent*  e);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void focusInEvent(QFocusEvent*  e);
    bool  focusNextPrevChild(bool  next);
    void focusOutEvent(QFocusEvent*  e);
    bool  hasHeightForWidth() const;
    int  heightForWidth(int  arg__1) const;
    void hideEvent(QHideEvent*  event);
    void initPainter(QPainter*  painter) const;
    void inputMethodEvent(QInputMethodEvent*  arg__1);
    QVariant  inputMethodQuery(Qt::InputMethodQuery  property) const;
    void insertFromMimeData(const QMimeData*  source);
    void keyPressEvent(QKeyEvent*  e);
    void keyReleaseEvent(QKeyEvent*  e);
    void leaveEvent(QEvent*  event);
    QVariant  loadResource(int  type, const QUrl&  name);
    int  metric(QPaintDevice::PaintDeviceMetric  arg__1) const;
    void mouseDoubleClickEvent(QMouseEvent*  e);
    void mouseMoveEvent(QMouseEvent*  e);
    void mousePressEvent(QMouseEvent*  e);
    void mouseReleaseEvent(QMouseEvent*  e);
    void moveEvent(QMoveEvent*  event);
    bool  nativeEvent(const QByteArray&  eventType, void*  message, long*  result);
    QPaintEngine*  paintEngine() const;
    void paintEvent(QPaintEvent*  e);
    QPaintDevice*  redirected(QPoint*  offset) const;
    void resizeEvent(QResizeEvent*  e);
    void scrollContentsBy(int  dx, int  dy);
    void setupViewport(QWidget*  viewport);
    QPainter*  sharedPainter() const;
    void showEvent(QShowEvent*  arg__1);
    void tabletEvent(QTabletEvent*  event);
    void timerEvent(QTimerEvent*  e);
    bool  viewportEvent(QEvent*  arg__1);
    QSize  viewportSizeHint() const;
    void wheelEvent(QWheelEvent*  e);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QTEXTEDIT_H
