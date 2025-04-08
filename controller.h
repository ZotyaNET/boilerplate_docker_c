// controller.h
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "model.h"
#include "view.h"

class Controller {
public:
    Controller(Model& model, View& view);

    void run();

private:
    Model& model;
    View& view;
};

#endif