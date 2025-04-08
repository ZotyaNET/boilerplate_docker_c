#include "model.h"
#include "view.h"
#include "controller.h"

int main() {
    // Use the .storage/data.db path for the SQLite database
    Model model("data.db");
    View view;
    Controller controller(model, view);

    controller.run();

    return 0;
}