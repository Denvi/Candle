# TCP-сервер

Пример показывает, как можно использовать TCP-сокеты для удаленного контроля и управления ЧПУ.

Для возможности отладки диалоговое окно выводится не в модальном режиме.
Скрипт выполняется до тех пор, пока работает ручной цикл обработки событий.

```js
/*  ==========  Настройки Qt-модулей  ==========  */
script.importExtension("qt.core");      // QString, QTextCodec, QEventLoop ...
script.importExtension("qt.network");   // QTcpServer, QTcpSocket
script.importExtension("qt.widgets");   // QDialog, QPlainTextEdit ...

/*  ----------  Вспомогательные константы  ----------  */
const tc = QTextCodec.codecForMib(106); // UTF-8 текстовый кодек

/*  ===================================================
    1.  TCP-СЕРВЕР (слушает 0.0.0.0:9877)
    ===================================================  */
const server  = new QTcpServer();
var   clients = [];                     // активные подключения

/*  При появлении нового клиента...  */
server.newConnection.connect(function () {
    const client = server.nextPendingConnection();
    clients.push(client);

    /*  Чтение строк из сокета  */
    client.readyRead.connect(function () {
        while (client.canReadLine()) {
            /*  Ожидаем JSON-строку, заканчивающуюся \n
                Примеры:
                {"type":"c","cmd":"G0X0"}     – обычная команда
                {"type":"rtc","cmd":"\u0018"} – realtime-команда (Ctrl-X)  */
            const msg = JSON.parse(tc.toUnicode(client.readLine()));

            switch (msg.type) {
            case "c":
                app.device.sendCommand(msg.cmd);
                break;
            case "rtc":
                app.device.sendRuntimeCommand(msg.cmd);
                break;
            }
        }
    });

    /*  Удаляем клиента из списка при отключении  */
    client.disconnected.connect(function () {
        clients = clients.filter(function (c) { return c !== client; });
    });
});

/*  Пересылаем всем клиентам каждый приходящий статус контроллера  */
app.device.statusReceived.connect(function (status) {
    clients.forEach(function (client) {
        client.write(tc.fromUnicode(JSON.stringify({ status: status }) + "\n"));
    });
});

/*  Запускаем сервер на всех интерфейсах, порт 9877  */
server.listen("0.0.0.0", 9877);

/*  ===================================================
    2.  GUI-КЛИЕНТ (простой диалог для тестов)
    ===================================================  */
const d  = new QDialog();               // окно
const el = new QEventLoop();            // ручной цикл событий
const l  = new QVBoxLayout(d);          // компоновщик

const te = new QPlainTextEdit(d);       // поле редактирования JSON-команды
const le = new QLineEdit(d);            // поле последнего принятого ответа
const b  = new QPushButton("Send", d);  // кнопка «Отправить»

le.readOnly = true;                     // только для показа входящих сообщений
te.setPlainText('{"type":"c","cmd":"$J=G21 G91 X1 F1000"}'); // пример команды Jog

/*  По клику шлём текст из te на сервер  */
b.clicked.connect(function () {
    client.write(tc.fromUnicode(te.plainText + "\n"));
});

/*  Компонуем виджеты  */
l.addWidget(le, 0, Qt.Vertical);
l.addWidget(te, 1, Qt.Vertical);
l.addWidget(b, 0, Qt.Vertical);
d.setLayout(l);
d.modal = false;

/*  Закрытие окна – выход из ручного цикла  */
d.finished.connect(function () { el.quit(); });

/*  ===================================================
    3.  TCP-КЛИЕНТ (соединяется с localhost:9877)
    ===================================================  */
const client = new QTcpSocket();

/*  Читаем ответы сервера и показываем их в le  */
client.readyRead.connect(function () {
    while (client.canReadLine()) {
        const msg = tc.toUnicode(client.readLine());
        le.setText(msg);                // последняя строка JSON
    }
});

client.connectToHost("localhost", 9877); // соединяемся с собственным сервером

/*  Показываем окно и запускаем локальный цикл событий  */
d.show();
el.exec();
```