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
    
    ASSERT_EQ(account, c.getAccountName());
    ASSERT_EQ(name, c.getUser());
}

TEST_F(ContoTest, TransactionGain) {
    //test inserimento in conto della transazione gain
    Date d = Date(25,05,2020);
    c.insertTransaction(Type::Gain,1, 200,d);
    ASSERT_EQ(200, c.getBalance());

}

TEST_F(ContoTest, TransactionExpense) {
    //test inserimento expense
    Date d = Date(25, 05, 2020);
    c.insertTransaction(Type::Expense, 1, 500, d);
    ASSERT_EQ(-500, c.getBalance());

}

TEST_F(ContoTest, TransactionTransfer) {
    //test inserimento transfer
    Conto c2 = Conto("Lorenzo", "Secondario", 2);
    Date d = Date(25, 05, 2020);
    c.insertTransaction(Type::Transfer, 1, 500, d,&c2);
    ASSERT_EQ(-500, c.getBalance());
    ASSERT_EQ(500, c2.getBalance());

}

TEST_F(ContoTest, GainExpenseTransfer) {
    //test inserimento gain, expense e transfer
    Date d = Date(25, 05, 2020);
    Conto c2 = Conto("Lorenzo", "Secondario", 2);
    c.insertTransaction(Type::Gain,1,500,d);
    c2.insertTransaction(Type::Expense,2,500, d);
    c.insertTransaction(Type::Transfer, 3,500,d,&c2);
    ASSERT_EQ(0, c.getBalance());
    ASSERT_EQ(0, c2.getBalance());
}

