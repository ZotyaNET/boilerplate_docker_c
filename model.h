// model.h
#ifndef MODEL_H
#define MODEL_H

#include <sqlite3.h>
#include <vector>
#include <string>

struct Record {
    int id;
    std::string name;

    Record(int id, const std::string& name) : id(id), name(name) {}
};

class Model {
public:
    Model(const std::string& dbName);
    ~Model();

    void initializeDatabase();
    void insertRecord(const Record& record);
    std::vector<Record> loadRecords();

private:
    sqlite3* db;
};

#endif