#include "gtest/gtest.h"
#include "model.h"

TEST(ModelTest, InitializeDatabase) {
    Model model(":memory:"); // Use in-memory database for testing
    EXPECT_NO_THROW(model.initializeDatabase());
}

TEST(ModelTest, InsertAndLoadRecords) {
    Model model(":memory:");
    model.initializeDatabase();

    model.insertRecord(Record(1, "Alice"));
    model.insertRecord(Record(2, "Bob"));

    auto records = model.loadRecords();
    ASSERT_EQ(records.size(), 2);
    EXPECT_EQ(records[0].id, 1);
    EXPECT_EQ(records[0].name, "Alice");
    EXPECT_EQ(records[1].id, 2);
    EXPECT_EQ(records[1].name, "Bob");
}