# TCP server

This example shows how to use TCP sockets for remote control and monitoring of the CNC controller.

For easy debugging the dialog is shown **non-modal**; the script keeps running until the manual event-loop is terminated.

```js
/*  ========== Qt module setup ========== */
script.importExtension("qt.core");     // QString, QTextCodec, QEventLoop ...
script.importExtension("qt.network");  // QTcpServer, QTcpSocket
script.importExtension("qt.widgets");  // QDialog, QPlainTextEdit ...

/*  ---------- helpers ----------  */
const tc = QTextCodec.codecForMib(106);   // UTF-8 text codec

/* =====================================================
   1. TCP SERVER (listens on 0.0.0.0:9877)
   ===================================================== */
const server = new QTcpServer();
var clients  = [];                        // active connections

/* when a new client connects ... */
server.newConnection.connect(function () {
    const client = server.nextPendingConnection();
    clients.push(client);

    /* read lines from socket */
    client.readyRead.connect(function () {
        while (client.canReadLine()) {
            /* expect JSON line terminated by \n
               examples:
               {"type":"c","cmd":"G0X0"}     – normal command
               {"type":"rtc","cmd":"\u0018"} – realtime command (Ctrl-X) */
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

    /* remove client from list when disconnected */
    client.disconnected.connect(function () {
        clients = clients.filter(function (c) { return c !== client; });
    });
});

/* forward every controller-status packet to all clients */
app.device.statusReceived.connect(function (status) {
    clients.forEach(function (client) {
        client.write(tc.fromUnicode(JSON.stringify({ status: status }) + "\n"));
    });
});

/* start server on all interfaces, port 9877 */
server.listen("0.0.0.0", 9877);

/* =====================================================
   2. GUI CLIENT (simple test dialog)
   ===================================================== */
const d  = new QDialog();              // window
const el = new QEventLoop();           // manual event loop
const l  = new QVBoxLayout(d);         // layout

const te = new QPlainTextEdit(d);      // JSON command editor
const le = new QLineEdit(d);           // last received reply
const b  = new QPushButton("Send", d); // send button

le.readOnly = true;                                    // view-only
te.setPlainText('{"type":"c","cmd":"$J=G21 G91 X1 F1000"}'); // sample jog cmd

/* send text from te to server when button clicked */
b.clicked.connect(function () {
    client.write(tc.fromUnicode(te.plainText + "\n"));
});

/* assemble widgets */
l.addWidget(le, 0, Qt.Vertical);
l.addWidget(te, 1, Qt.Vertical);
l.addWidget(b, 0, Qt.Vertical);
d.setLayout(l);
d.modal = false;

/* exit manual loop on dialog close */
d.finished.connect(function () { el.quit(); });

/* =====================================================
   3. TCP CLIENT (connects to localhost:9877)
   ===================================================== */
const client = new QTcpSocket();

/* display server replies in le */
client.readyRead.connect(function () {
    while (client.canReadLine()) {
        const msg = tc.toUnicode(client.readLine());
        le.setText(msg);               // latest JSON line
    }
});

client.connectToHost("localhost", 9877); // connect to our own server

/* show window and run local event loop */
d.show();
el.exec();
```