# NOPF-server

Instead of connecting via port forwarding, connect using TCP hole punching.

## Usage

**You should not use nopf-core and nopf-server in the same public IP address**

Add iptables rules to block RST, RST+ACK, FIN+ACK

```bash
iptables -A OUTPUT -p tcp -m tcp --sport 3012 --tcp-flags FIN,ACK FIN,ACK -j DROP
iptables -A OUTPUT -p tcp -m tcp --sport 3012 --tcp-flags RST,ACK RST,ACK -j DROP
iptables -A OUTPUT -p tcp -m tcp --sport 3012 --tcp-flags RST RST -j DROP
```

Run nopf-server

```bash
./nopf-server
```

See also: https://github.com/smiilliin/nopf-core

## Development

### CMake

- `./run.bat debug`: run cmake with debug mode
- `./run.bat release`: run cmake with release mode

### Build or Run

- `./run.bat build`: build with gcc
- `./run.bat run`: run with gcc
- `./run.bat brun`: build and run
