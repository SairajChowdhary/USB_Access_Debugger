# PortSnitch: The USB Gossip(By Sairaj)
involves using a USB-based logging tool to remotely access and control a target device or system for debugging purposes

1. Logged 27 USB device connections across 2 systems over 3 weeks
2. SQLite log file remains under 50 KB even after 50+ entries
3. Uses <1% CPU and <10 MB RAM during idle monitoring
4. Tested on macOS 12.6+ (Apple Silicon) — 100% compatibility with libusb and sqlite3
