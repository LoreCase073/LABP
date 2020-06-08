#include "gtest/gtest.h"
#include "..\Users\lorec\source\repos\LABP\Project1\Conto.h"
#include "..\Users\lorec\source\repos\LABP\Project1\AccountManager.h"

class ContoTest : public ::testing::Test
{
protected:
    Conto c;
    virtual void SetUp() {
        c = Conto("Lorenzo", "Principale", 1);
    }

};

TEST_F(ContoTest, ConstructBalanceId) {
    //test se creazione oggetto è andata a buon fine

    int id = 1;
    
    ASSERT_EQ(0, c.getBalance());
    ASSERT_EQ(1, c.getId());
}


TEST_F(ContoTest, CounterIncrementAccountName) {

    //test se incremento del contatore di transazioni è corretto e altre informazioni
    string name = "Lorenzo";
    string account = "Principale";
    
    
    ASSERT_EQ(1, c.getTransCounter());
    c.incrementCounter();
    ASSERT_EQ(2, c.getTransCounter());
    ASSERT_EQ(account, c.getAccountName());
    ASSERT_EQ(name, c.getUser());
}

TEST_F(ContoTest, TransactionGain) {
    //test inserimento in conto della transazione gain
    c.insertGain(200, 25, 05, 2020);
    ASSERT_EQ(200, c.getBalance());

}

TEST_F(ContoTest, TransactionExpense) {
    //test inserimento expense
    c.insertExpense(500, 25, 05, 2020);
    ASSERT_EQ(-500, c.getBalance());

}

TEST_F(ContoTest, TransactionTransfer) {
    //test inserimento transfer
    Conto c2 = Conto("Lorenzo", "Secondario", 2);
    c.insertTransfer(500, 25, 05, 2020,&c2);
    ASSERT_EQ(-500, c.getBalance());
    ASSERT_EQ(500, c2.getBalance());

}

TEST_F(ContoTest, GainExpenseTransfer) {
    //test inserimento gain, expense e transfer
    Conto c2 = Conto("Lorenzo", "Secondario", 2);
    c.insertGain(500,26,05,2020);
    c2.insertExpense(500, 26,05,2020);
    c.insertTransfer(500,26,05,2020,&c2);
    ASSERT_EQ(0, c.getBalance());
    ASSERT_EQ(0, c2.getBalance());
}

