#ifndef QTSCRIPTSHELL_QLISTWIDGET_H
#define QTSCRIPTSHELL_QLISTWIDGET_H

#include <qlistwidget.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QListWidget : public QListWidget
{
public:
    QtScriptShell_QListWidget(QWidget*  parent = 0);
    ~QtScriptShell_QListWidget();

    void actionEvent(QActionEvent*  event);
    void changeEvent(QEvent*  arg__1);
    void childEvent(QChildEvent*  event);
    void closeEditor(QWidget*  editor, QAbstractItemDelegate::EndEditHint  hint);
    void closeEvent(QCloseEvent*  event);
    void commitData(QWidget*  editor);
    void contextMenuEvent(QContextMenuEvent*  arg__1);
    void currentChanged(const QModelIndex&  current, const QModelIndex&  previous);
    void customEvent(QEvent*  event);
    void dataChanged(const QModelIndex&  topLeft, const QModelIndex&  bottomRight, const QVector<int >&  roles);
    int  devType() const;
    void doItemsLayout();
    void dragEnterEvent(QDragEnterEvent*  event);
    void dragLeaveEvent(QDragLeaveEvent*  e);
    void dragMoveEvent(QDragMoveEvent*  e);
    void dropEvent(QDropEvent*  event);
    bool  dropMimeData(int  index, const QMimeData*  data, Qt::DropAction  action);
    bool  edit(const QModelIndex&  index, QAbstractItemView::EditTrigger  trigger, QEvent*  event);
    void editorDestroyed(QObject*  editor);
    void enterEvent(QEvent*  event);
    bool  event(QEvent*  e);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void focusInEvent(QFocusEvent*  event);
    bool  focusNextPrevChild(bool  next);
    void focusOutEvent(QFocusEvent*  event);
    bool  hasHeightForWidth() const;
    int  heightForWidth(int  arg__1) const;
    void hideEvent(QHideEvent*  event);
    int  horizontalOffset() const;
    void horizontalScrollbarAction(int  action);
    void horizontalScrollbarValueChanged(int  value);
    QModelIndex  indexAt(const QPoint&  p) const;
    void initPainter(QPainter*  painter) const;
    void inputMethodEvent(QInputMethodEvent*  event);
    QVariant  inputMethodQuery(Qt::InputMethodQuery  query) const;
    bool  isIndexHidden(const QModelIndex&  index) const;
    void keyPressEvent(QKeyEvent*  event);
    void keyReleaseEvent(QKeyEvent*  event);
    void keyboardSearch(const QString&  search);
    void leaveEvent(QEvent*  event);
    int  metric(QPaintDevice::PaintDeviceMetric  arg__1) const;
    QStringList  mimeTypes() const;
    void mouseDoubleClickEvent(QMouseEvent*  event);
    void mouseMoveEvent(QMouseEvent*  e);
    void mousePressEvent(QMouseEvent*  event);
    void mouseReleaseEvent(QMouseEvent*  e);
    void moveEvent(QMoveEvent*  event);
    bool  nativeEvent(const QByteArray&  eventType, void*  message, long*  result);
    QPaintEngine*  paintEngine() const;
    void paintEvent(QPaintEvent*  e);
    QPaintDevice*  redirected(QPoint*  offset) const;
    void reset();
    void resizeEvent(QResizeEvent*  e);
    void rowsAboutToBeRemoved(const QModelIndex&  parent, int  start, int  end);
    void rowsInserted(const QModelIndex&  parent, int  start, int  end);
    void scrollContentsBy(int  dx, int  dy);
    void scrollTo(const QModelIndex&  index, QAbstractItemView::ScrollHint  hint);
    void selectAll();
    QList<QModelIndex >  selectedIndexes() const;
    void selectionChanged(const QItemSelection&  selected, const QItemSelection&  deselected);
    QItemSelectionModel::SelectionFlags  selectionCommand(const QModelIndex&  index, const QEvent*  event) const;
    void setRootIndex(const QModelIndex&  index);
    void setSelection(const QRect&  rect, QItemSelectionModel::SelectionFlags  command);
    void setSelectionModel(QItemSelectionModel*  selectionModel);
    void setupViewport(QWidget*  viewport);
    QPainter*  sharedPainter() const;
    void showEvent(QShowEvent*  event);
    int  sizeHintForColumn(int  column) const;
    int  sizeHintForRow(int  row) const;
    void startDrag(Qt::DropActions  supportedActions);
    Qt::DropActions  supportedDropActions() const;
    void tabletEvent(QTabletEvent*  event);
    void timerEvent(QTimerEvent*  e);
    void updateEditorData();
    void updateEditorGeometries();
    void updateGeometries();
    int  verticalOffset() const;
    void verticalScrollbarAction(int  action);
    void verticalScrollbarValueChanged(int  value);
    QStyleOptionViewItem  viewOptions() const;
    bool  viewportEvent(QEvent*  event);
    QSize  viewportSizeHint() const;
    QRect  visualRect(const QModelIndex&  index) const;
    QRegion  visualRegionForSelection(const QItemSelection&  selection) const;
    void wheelEvent(QWheelEvent*  e);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QLISTWIDGET_H
