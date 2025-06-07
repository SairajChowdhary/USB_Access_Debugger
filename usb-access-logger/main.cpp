#include "usb_monitor.hpp"
#include "logger.hpp"

int main() {
    Logger logger("logs/access_log.db");
    USBMonitor monitor;

    monitor.startMonitoring(logger);

    return 0;
}

