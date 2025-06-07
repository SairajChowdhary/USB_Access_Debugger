#include "usb_monitor.hpp"
#include <libusb-1.0/libusb.h>
#include <iostream>

void USBMonitor::startMonitoring(Logger& logger) {
    libusb_context* ctx = nullptr;
    libusb_device** devs;
    ssize_t cnt;

    if (libusb_init(&ctx) < 0) {
        std::cerr << "Failed to initialize libusb\n";
        return;
    }

    cnt = libusb_get_device_list(ctx, &devs);
    if (cnt < 0) {
        std::cerr << "Error getting device list\n";
        libusb_exit(ctx);
        return;
    }

    for (ssize_t i = 0; i < cnt; ++i) {
        libusb_device_descriptor desc;
        if (libusb_get_device_descriptor(devs[i], &desc) == 0) {
            std::string info = "Vendor ID: " + std::to_string(desc.idVendor) +
                               ", Product ID: " + std::to_string(desc.idProduct);
            logger.logAccess(info);
        }
    }

    libusb_free_device_list(devs, 1);
    logger.logDeviceCount(cnt);
    libusb_exit(ctx);
}

