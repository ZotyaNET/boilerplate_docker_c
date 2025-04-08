#include <iostream>
#include <sqlite3.h>
#include <vector>
#include <string>

// Data object schema
struct Record {
    int id;
    std::string name;

    Record(int id, const std::string& name) : id(id), name(name) {}
};

// Function to initialize the database and create a table
void initializeDatabase(sqlite3* &db) {
    const char* createTableSQL = R"(
        CREATE TABLE IF NOT EXISTS records (
            id INTEGER PRIMARY KEY,
            name TEXT NOT NULL
        );
    )";

    char* errorMessage = nullptr;
    if (sqlite3_exec(db, createTableSQL, nullptr, nullptr, &errorMessage) != SQLITE_OK) {
        std::cerr << "Error creating table: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
    }
}

// Function to insert a record into the database
void insertRecord(sqlite3* db, const Record& record) {
    const char* insertSQL = "INSERT INTO records (id, name) VALUES (?, ?);";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, insertSQL, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, record.id);
        sqlite3_bind_text(stmt, 2, record.name.c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::cerr << "Error inserting record: " << sqlite3_errmsg(db) << std::endl;
        }
        sqlite3_finalize(stmt);
    } else {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
    }
}

// Function to load all records from the database
std::vector<Record> loadRecords(sqlite3* db) {
    const char* selectSQL = "SELECT id, name FROM records;";
    sqlite3_stmt* stmt;
    std::vector<Record> records;

    if (sqlite3_prepare_v2(db, selectSQL, -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            std::string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            records.emplace_back(id, name);
        }
        sqlite3_finalize(stmt);
    } else {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
    }

    return records;
}

int main() {
    sqlite3* db;
    if (sqlite3_open("data.db", &db) != SQLITE_OK) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        return 1;
    }

    initializeDatabase(db);

    // Insert some records
    insertRecord(db, Record(1, "Alice"));
    insertRecord(db, Record(2, "Bob"));

    // Load and display records
    std::vector<Record> records = loadRecords(db);
    for (const auto& record : records) {
        std::cout << "ID: " << record.id << ", Name: " << record.name << std::endl;
    }

    sqlite3_close(db);
    return 0;
}