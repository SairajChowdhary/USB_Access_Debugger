#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <sqlite3.h>

class Logger {
public:
    Logger(const std::string& dbPath);
    ~Logger();
    void logDevice(int vendorId, int productId);

private:
    sqlite3* db;
};

#endif 

