#include "logger.hpp"
#include <iostream>
#include <sqlite3.h>

Logger::Logger(const std::string& dbPath) {
    if (sqlite3_open(dbPath.c_str(), &db)) {
        std::cerr << "Failed to open database: " << sqlite3_errmsg(db) << "\n";
        db = nullptr;
    } else {
        const char* sql = "CREATE TABLE IF NOT EXISTS usb_logs ("
                          "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                          "vendor_id INTEGER, "
                          "product_id INTEGER, "
                          "timestamp DATETIME DEFAULT CURRENT_TIMESTAMP);";
        char* errMsg = nullptr;
        if (sqlite3_exec(db, sql, nullptr, nullptr, &errMsg) != SQLITE_OK) {
            std::cerr << "Failed to create table: " << errMsg << "\n";
            sqlite3_free(errMsg);
        }
    }
}

Logger::~Logger() {
    if (db) sqlite3_close(db);
}

void Logger::logDevice(int vendorId, int productId) {
    if (!db) return;

    std::string sql = "INSERT INTO usb_logs (vendor_id, product_id) VALUES (?, ?);";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, vendorId);
        sqlite3_bind_int(stmt, 2, productId);
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::cerr << "Failed to insert data\n";
        }
        sqlite3_finalize(stmt);
    }
}

