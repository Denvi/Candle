# Обход границ

```js
// Подключаем модули Qt, чтобы можно было показать диалог по завершении
script.importExtension("qt.gui");
script.importExtension("qt.widgets");

// Формируем и сразу отправляем в устройство список G-кодов:
// G21 – работа в миллиметрах, G90 – абсолютные координаты, F100 – подача 100 мм/мин
// Далее четыре строки прямоугольного контура по границам рабочей области
// M2 – корректный конец программы; устройство вернёт ответ после выполнения всей траектории
app.device.sendCommands([
    "G21G90F100",
    "G1X" + app.program.lowerBounds.x() + "Y" + app.program.lowerBounds.y(),
    "G1Y" + app.program.upperBounds.y(),
    "G1X" + app.program.upperBounds.x(),
    "G1Y" + app.program.lowerBounds.y(),
    "G1X" + app.program.lowerBounds.x(),
    "M2" // будет отправлен ответ, когда весь путь реально отработан
]);

// Ждём, пока устройство не подтвердит выполнение всех команд (включая M2)
app.device.waitResponses();

// Показываем пользователю модальный диалог «Done» – обработка завершена
QMessageBox.information(app.window, "", "Done");
```