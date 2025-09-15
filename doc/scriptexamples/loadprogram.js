if (app.senderState == 4) {
    app.loadProgram([
        "G21G90",
        "G0X0Y0Z0",
        "G1X10F100",
        "G1Y10F200",
        "G0Z1",
        "G0X0Y0",
        "M2"
    ]);
}