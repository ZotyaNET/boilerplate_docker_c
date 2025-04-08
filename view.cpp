// view.cpp
#include "view.h"
#include <iostream>

void View::displayRecords(const std::vector<Record>& records) {
    for (const auto& record : records) {
        std::cout << "ID: " << record.id << ", Name: " << record.name << std::endl;
    }
}