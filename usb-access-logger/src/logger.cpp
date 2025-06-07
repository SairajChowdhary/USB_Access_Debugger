#include "logger.hpp"
#include <iostream>

Logger::Logger(const std::string& dbPath) {
    if (sqlite3_open(dbPath.c_str(), &db)) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        db = nullptr;
    } else {
        initDB();
    }
}

void Logger::initDB() {
    const char* sql = "CREATE TABLE IF NOT EXISTS access_log ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                      "timestamp DATETIME DEFAULT CURRENT_TIMESTAMP,"
                      "device_info TEXT);";
    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "DB Init Error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

void Logger::logAccess(const std::string& deviceInfo) {
    std::string sql = "INSERT INTO access_log (device_info) VALUES ('" + deviceInfo + "');";
    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "Insert Error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

