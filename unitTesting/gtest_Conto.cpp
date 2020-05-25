#include "gtest/gtest.h"
#include <string>
#include "Conto.h"


TEST(Conto, ConstructAndCounter) {
    string name = "Lorenzo";
    string account = "Principale";
    int id = 1;
    Conto c = Conto(name, account, 1);
    ASSERT_EQ(0, c.getBalance());
    ASSERT_EQ(1, c.getId());
    ASSERT_EQ(1, c.getTransCounter());
    c.incrementCounter();
    ASSERT_EQ(1, c.getTransCounter());
    ASSERT_EQ(account, c.getAccountName());
    ASSERT_EQ(name, c.getUser());
    
}