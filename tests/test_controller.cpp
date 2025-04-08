#include "gtest/gtest.h"
#include "controller.h"

TEST(ControllerTest, Run) {
    Model model(":memory:");
    View view;
    Controller controller(model, view);

    EXPECT_NO_THROW(controller.run());
}