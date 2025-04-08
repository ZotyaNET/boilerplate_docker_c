#include "gtest/gtest.h"
#include "view.h"
#include <sstream>

TEST(ViewTest, DisplayRecords) {
    std::vector<Record> records = {Record(1, "Alice"), Record(2, "Bob")};
    View view;

    std::ostringstream output;
    std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf()); // Redirect std::cout

    view.displayRecords(records);

    std::cout.rdbuf(oldCout); // Restore std::cout
    EXPECT_EQ(output.str(), "ID: 1, Name: Alice\nID: 2, Name: Bob\n");
}