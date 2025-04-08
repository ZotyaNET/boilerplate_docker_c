// controller.cpp
#include "controller.h"

Controller::Controller(Model& model, View& view) : model(model), view(view) {}

void Controller::run() {
    model.initializeDatabase();

    // Insert some records
    model.insertRecord(Record(1, "Alice"));
    model.insertRecord(Record(2, "Bob"));

    // Load and display records
    std::vector<Record> records = model.loadRecords();
    view.displayRecords(records);
}