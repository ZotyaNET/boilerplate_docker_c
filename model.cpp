#include "model.h"
#include <stdexcept>
#include <iostream>

Model::Model(const std::string& dbName) {
    if (sqlite3_open(dbName.c_str(), &db) != SQLITE_OK) {
        throw std::runtime_error("Failed to open database");
    }
}

Model::~Model() {
    if (db) {
        sqlite3_close(db);
    }
}

void Model::initializeDatabase() {
    const char* sql = "CREATE TABLE IF NOT EXISTS records (id INTEGER PRIMARY KEY, name TEXT UNIQUE)";
    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::string error = "Failed to initialize database: ";
        error += errMsg;
        sqlite3_free(errMsg);
        throw std::runtime_error(error);
    }
}

void Model::insertRecord(const Record& record) {
    const char* sql = "INSERT INTO records (id, name) VALUES (?, ?)";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error("Failed to prepare insert statement");
    }
    sqlite3_bind_int(stmt, 1, record.id);
    sqlite3_bind_text(stmt, 2, record.name.c_str(), -1, SQLITE_STATIC);
    int result = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if (result != SQLITE_DONE) {
        if (result == SQLITE_CONSTRAINT) {
            throw std::runtime_error("UNIQUE constraint failed: Duplicate record");
        }
        throw std::runtime_error("Failed to insert record");
    }
}

std::vector<Record> Model::loadRecords() {
    const char* sql = "SELECT id, name FROM records";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error("Failed to prepare select statement");
    }
    std::vector<Record> records;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        std::string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        records.emplace_back(id, name);
    }
    sqlite3_finalize(stmt);
    return records;
}

void Model::updateOrCreate(const Record& record) {
    try {
        // Attempt to update the record
        const char* updateSQL = "UPDATE records SET name = ? WHERE id = ?";
        sqlite3_stmt* stmt;
        if (sqlite3_prepare_v2(db, updateSQL, -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error("Failed to prepare update statement");
        }
        sqlite3_bind_text(stmt, 1, record.name.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 2, record.id);

        int result = sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        if (result == SQLITE_DONE && sqlite3_changes(db) > 0) {
            // Record updated successfully
            return;
        }

        // If no rows were updated, insert the record
        const char* insertSQL = "INSERT INTO records (id, name) VALUES (?, ?)";
        if (sqlite3_prepare_v2(db, insertSQL, -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error("Failed to prepare insert statement");
        }
        sqlite3_bind_int(stmt, 1, record.id);
        sqlite3_bind_text(stmt, 2, record.name.c_str(), -1, SQLITE_STATIC);

        result = sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        if (result != SQLITE_DONE) {
            throw std::runtime_error("Failed to insert record");
        }
    } catch (const std::exception& e) {
        std::cerr << "Error in updateOrCreate: " << e.what() << std::endl;
    }
}