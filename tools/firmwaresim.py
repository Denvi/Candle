#!/usr/bin/env python3
"""TCP firmware simulator for Candle (Settings -> Connection -> Telnet).

Emulates two firmware profiles:
  arm32 (default)  Genmitsu PRO|MAX "Grbl for ARM32" V2.7 style: reset banner is
                   three lines and the second one starts with "Grbl" ("Grbl for
                   ARM32"), settings values carry "(...)" descriptions (issue #731).
  --plain          Standard Grbl 1.1 / grblHAL / FluidNC behaviour: one banner
                   line with a version number, plain numeric settings.

Usage:
  python tools/firmwaresim.py [--port 2323] [--plain]

Then in Candle: Settings -> Connection -> Telnet, 127.0.0.1, port 2323,
keep "Reset on connection" enabled so the banner sequence is exercised.
Real-time characters (0x18 reset, 0x85 jog cancel, '~', '!') are handled
without a feedback line, like the real protocol.
"""

import argparse
import socket
import socketserver
import sys

BANNER_ARM32 = ["Grbl 1.1f ['$' for help]", "Grbl for ARM32", "Version:ARM32 V2.7"]
BANNER_PLAIN = ["Grbl 1.1f ['$' for help]"]

# $130/$131/$132 travel per the machine in issue #731 (3020-PRO MAX V2).
SETTINGS_DESC = [
    ("0", "10", "step pulse,usec"), ("1", "25", "step idle delay,msec"),
    ("2", "0", "stepport invert mask"), ("3", "2", "dirport invert mask"),
    ("4", "0", "stepenable invert,bool"), ("5", "1", "lims pin invert,bool"),
    ("6", "0", "probe invert,bool"), ("10", "2", "status report mask:00000010"),
    ("11", "0.010", "junction deviation,mm"), ("12", "0.002", "arc tolerance,mm"),
    ("13", "0", "report inches,bool"), ("20", "0", "soft limits,bool"),
    ("21", "1", "hard limits,bool"), ("22", "1", "homing cycle,bool"),
    ("23", "3", "homing dir invert mask:00000011"),
    ("24", "500.000", "homing feed,millimeters/min"),
    ("25", "1300.000", "homing seek,millimeters/min"),
    ("26", "250", "homing debounce,microseconds"), ("27", "4.000", "homing pull-off,mm"),
    ("30", "1000.000", "rpm max"), ("31", "0.000", "rpm min"), ("32", "1", "laser mode,bool"),
    ("100", "100.000", "x steps,step/mm"), ("101", "100.000", "y steps,step/mm"),
    ("102", "100.000", "z steps,step/mm"),
    ("110", "1300.000", "x max rate,mm/min"), ("111", "1300.000", "y max rate,mm/min"),
    ("112", "500.000", "z max rate,mm/min"),
    ("120", "10.000", "x accel,mm/sec^2"), ("121", "10.000", "y accel,mm/sec^2"),
    ("122", "10.000", "z accel,mm/sec^2"),
    ("130", "300.000", "x axis max travel:mm"), ("131", "200.000", "y axis max travel:mm"),
    ("132", "80.000", "z axis max travel:mm"),
]

SETTINGS_PLAIN = [(n, v) for (n, v, _) in SETTINGS_DESC]


class Handler(socketserver.StreamRequestHandler):
    # Single-firmware emulation: one client at a time, like a real COM port.
    def handle(self):
        self.request.setsockopt(socket.IPPROTO_TCP, socket.TCP_NODELAY, 1)
        print(f"[sim] client {self.client_address} connected", flush=True)
        buf = b""
        realtime = {0x18: "reset", 0x85: "jog-cancel", 0x21: "feed-hold", 0x7E: "resume"}
        try:
            while True:
                chunk = self.rfile.read(1)
                if not chunk:
                    break
                b = chunk[0]
                if b in realtime:  # real-time commands: no feedback line
                    if b == 0x18:
                        self.banner()
                    continue
                if b in (0x0A, 0x0D):
                    if buf:
                        self.command(buf.decode("ascii", "replace"))
                        buf = b""
                    continue
                buf += chunk
                if len(buf) > 512:
                    buf = b""
        except ConnectionResetError:
            pass  # Candle killed/closed without a clean FIN
        finally:
            print(f"[sim] client {self.client_address} disconnected", flush=True)

    def send_lines(self, lines, final="ok"):
        for line in lines:
            self.wfile.write((line + "\r\n").encode())
        if final:
            self.wfile.write((final + "\r\n").encode())
        self.wfile.flush()

    def banner(self):
        banners = BANNER_PLAIN if self.server.plain else BANNER_ARM32
        for line in banners:
            self.wfile.write((line + "\r\n").encode())
        self.wfile.flush()

    def command(self, cmd):
        print(f"[sim] << {cmd}", flush=True)
        c = cmd.strip()
        # Real-time characters are intercepted per-byte by Grbl, not per-line:
        # "?$$" (Candle's hidden-command form) = status report + "$$".
        if "?" in c:
            self.send_lines(["<Idle|MPos:0.000,0.000,0.000|Bf:15,128|FS:0,0>"], final=None)
            c = c.replace("?", "").strip()
            if not c:
                return
        if c == "$$":
            if self.server.plain:
                self.send_lines([f"${n}={v}" for (n, v) in SETTINGS_PLAIN])
            else:
                self.send_lines([f"${n}={v} ({d})" for (n, v, d) in SETTINGS_DESC])
        elif c == "$#":
            self.send_lines(["G54 X:0.000 Y:0.000 Z:0.000",
                             "G57 X:0.000 Y:0.000 Z:0.000"])
        elif c == "$G":
            self.send_lines(["G0 G54 G17 G21 G90 G94 M5 M9 T0 F0 S0"])
        elif c == "$I":
            banner = "ARM32 V2.7.20240824" if not self.server.plain else "1.1f.20170801"
            self.send_lines([f"[VER:{banner}:]", "[OPT:VZL,35,254]"])
        elif c == "$N":
            self.send_lines(["$N0=", "$N1="])
        elif c == "$":
            self.send_lines(["$G", "$#", "$I", "$N"], final=None)
        elif c.startswith("$") and not c.startswith("$J="):
            self.send_lines([], final="error:3")
        else:
            self.send_lines([])


def main():
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("--host", default="127.0.0.1")
    ap.add_argument("--port", type=int, default=2323)
    ap.add_argument("--plain", action="store_true",
                    help="emulate standard Grbl 1.1 output instead of the ARM32 fork")
    args = ap.parse_args()

    socketserver.TCPServer.allow_reuse_address = True
    with socketserver.ThreadingTCPServer((args.host, args.port), Handler) as srv:
        srv.plain = args.plain
        print(f"[sim] {('plain grbl 1.1' if args.plain else 'ARM32 V2.7')} "
              f"listening on {args.host}:{args.port}", flush=True)
        srv.serve_forever()


if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        sys.exit(0)
