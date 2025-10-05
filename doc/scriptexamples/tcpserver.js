script.importExtension("qt.core");
script.importExtension("qt.network");
script.importExtension("qt.widgets");

// Helpers
const tc = QTextCodec.codecForMib(106); // UTF8

// TCP server
const server = new QTcpServer();
var clients = [];

server.newConnection.connect(function() {
    const client = server.nextPendingConnection();
    clients.push(client);

    client.readyRead.connect(function() {
        while (client.canReadLine()) {
            const msg = JSON.parse(tc.toUnicode(client.readLine()));
            // {"type": "c", "cmd": "G0X0"} // Regular command
            // {"type": "rtc", "cmd": "\u0018"} // CTRL+X
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

    client.disconnected.connect(function() {
        clients = clients.filter(function(c) { return c !== client; });
    });
});

app.device.statusReceived.connect(function(status) {
    clients.forEach(function(client) {
        client.write(tc.fromUnicode(JSON.stringify({"status": status}) + "\n"));
    });
});

server.listen("0.0.0.0", 9877);

// Client form
const d = new QDialog();
const el = new QEventLoop();
const l = new QVBoxLayout(d);
const te = new QPlainTextEdit(d);
const le = new QLineEdit(d);
const b = new QPushButton("Send", d);

le.readOnly = true;
te.setPlainText('{"type": "c", "cmd": "$J=G21 G91 X1 F1000"}');

b.clicked.connect(function() {
    client.write(tc.fromUnicode(te.plainText + "\n"));
});

l.addWidget(le, 0, Qt.Vertical);
l.addWidget(te, 1, Qt.Vertical);
l.addWidget(b, 0, Qt.Vertical);
d.setLayout(l);

d.modal = false;
d.finished.connect(function() {
    el.quit();
});

// TCP client
const client = new QTcpSocket();

client.readyRead.connect(function() {
    while (client.canReadLine()) {
        const msg = tc.toUnicode(client.readLine());
        le.setText(msg);
    }
});

client.connectToHost("localhost", 9877);

d.show();
el.exec();