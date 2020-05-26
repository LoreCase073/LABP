#include "gtest/gtest.h"
#include <string>
#include "../Project1/Conto.h"

TEST(Conto, ConstructAndCounter) {
    Conto c;
    string name = "Lorenzo";
    string account = "Principale";
    int id = 1;
    ASSERT_EQ(0, c.getBalance());
    ASSERT_EQ(1, c.getId());
    ASSERT_EQ(1, c.getTransCounter());
    c.incrementCounter();
    ASSERT_EQ(1, c.getTransCounter());
    ASSERT_EQ(account, c.getAccountName());
    ASSERT_EQ(name, c.getUser());
    
}