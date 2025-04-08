// view.h
#ifndef VIEW_H
#define VIEW_H

#include "model.h"
#include <vector>

class View {
public:
    void displayRecords(const std::vector<Record>& records);
};

#endif