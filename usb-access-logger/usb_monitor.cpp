#include "usb_monitor.hpp"
#include "logger.hpp"
#include <libusb-1.0/libusb.h>
#include <iostream>

void USBMonitor::startMonitoring(Logger& logger) {
    libusb_context* ctx = nullptr;
    libusb_device** devs;
    ssize_t cnt;

    if (libusb_init(&ctx) < 0) {
        std::cerr << "Failed to initialize libusb.\n";
        return;
    }

    cnt = libusb_get_device_list(ctx, &devs);
    if (cnt < 0) {
        std::cerr << "Failed to get device list.\n";
        libusb_exit(ctx);
        return;
    }

    std::cout << "Connected USB Devices:\n";
    for (ssize_t i = 0; i < cnt; ++i) {
        libusb_device_descriptor desc;
        if (libusb_get_device_descriptor(devs[i], &desc) == 0) {
            logger.logDevice(desc.idVendor, desc.idProduct);
            std::cout << "Vendor ID: " << std::hex << desc.idVendor
                      << ", Product ID: " << std::hex << desc.idProduct << "\n";
        }
    }

    libusb_free_device_list(devs, 1);
    libusb_exit(ctx);
}

