# Центроискатель

Ниже приведен пример скрипта, позволяющего найти центр отверстия.

Перед запуском необходимо подвести инструмент внутрь отверстия. Предварительное обнуление координат не требуется.

Для раннего прерывания исполнения кода в случае отмены ввода радиуса поиска в примере используется конструкция IIFE.

```js
script.importExtension("qt.core");   // Доступ к глобальным объектам Qt
script.importExtension("qt.widgets"); // Доступ к QInputDialog

(function () {
    /* ---------- 1. Получаем радиус поиска ---------- */
    const settings = app.storage.group("HoleCenterFinder");     // группа настроек для этого скрипта
    const storedRadius = settings.value("radius", 10);          // последнее использованное значение (по умолчанию 10 мм)

    const radius = QInputDialog.getDouble(
        app.window,                                 // родительское окно
        "Hole center finder",                       // заголовок диалога
        "Find radius",                              // подпись поля
        storedRadius, 0.0, 100.0, 0,                // значение, min, max, кол-во десятичных
        Qt.Dialog                                   // флаги
    );
    if (!radius) return;                            // пользователь нажал «Отмена»

    settings.setValue("radius", radius);            // сохраняем введённое значение

    /* ---------- 2. Запоминаем текущие координаты ---------- */
    const startX = app.device.work.x;
    const startY = app.device.work.y;

    /* ---------- 3. Поиск центра по оси Y ---------- */
    // Первое касание: двигаемся вперёд на заданный радиус
    app.device.sendCommand("G91G38.2F100Y" + radius);
    app.device.waitResponses();                     // ждём срабатывания щупа
    const probeY = app.device.probe.y;              // фиксируем координату касания

    // Уходим назад в исходную Y, затем двигаемся назад на тот же радиус
    app.device.sendCommands([
        "G90G0Y" + startY,      // абсолютный быстрый возврат
        "G91G38.2Y-" + radius   // относительное движение в обратную сторону
    ]);
    app.device.waitResponses();

    // Перемещаемся в середину между двумя касаниями
    app.device.sendCommand("G90G53G0Y" + (app.device.probe.y + probeY) / 2);

    /* ---------- 4. Поиск центра по оси X (аналогично Y) ---------- */
    app.device.sendCommand("G91G38.2X" + radius);
    app.device.waitResponses();
    const probeX = app.device.probe.x;

    app.device.sendCommands([
        "G90G0X" + startX,
        "G91G38.2X-" + radius
    ]);
    app.device.waitResponses();

    // Финальный переход в абсолютный центр отверстия
    app.device.sendCommand("G90G53G0X" + (app.device.probe.x + probeX) / 2);
})();
```