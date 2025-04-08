#include "model.h"
#include "view.h"
#include "controller.h"

int main() {
    Model model("data.db");
    View view;
    Controller controller(model, view);

    controller.run();

    return 0;
}