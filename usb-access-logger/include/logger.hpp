#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <sqlite3.h>

class Logger {
public:
    Logger(const std::string& dbPath);
    void logAccess(const std::string& deviceInfo);

private:
    sqlite3* db;
    void initDB();
};

#endif

