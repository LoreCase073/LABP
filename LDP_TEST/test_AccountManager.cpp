#include "gtest/gtest.h"
#include "..\Users\lorec\source\repos\LABP\Project1\Conto.h"
#include "..\Users\lorec\source\repos\LABP\Project1\AccountManager.h"

class AccountManagerTest : public ::testing::Test
{
protected:
    AccountManager ac;
    string dir = "C:\\Users\\lorec\\source\\repos\\Project1\\Project1\\Accounts.txt";
    virtual void SetUp() {
        ac = AccountManager(dir);
        ac.createAccount("Principale", "Lorenzo");
        ac.createAccount("Secondario", "Lorenzo");
    }

};


TEST_F(AccountManagerTest, ReadFromFile) {
    //provo a leggere ciò che vi è scritto nell'account creato
    AccountManager a = a.readFromFile("C:\\Users\\lorec\\source\\repos\\Project1\\Project1\\Accounts.txt");
    ASSERT_EQ(0, a.getAccountBalance(1));
    ASSERT_EQ("Principale", a.getAccountName(1));
    ASSERT_EQ("Lorenzo", a.getAccountUser(1));
    ASSERT_EQ(0, a.getAccountBalance(2));
    ASSERT_EQ("Secondario", a.getAccountName(2));
    ASSERT_EQ("Lorenzo", a.getAccountUser(2));
}

TEST_F(AccountManagerTest, Constructor2Accounts) {
    //controllo la costruzione dei due account è corretta
    ASSERT_EQ(0, ac.getAccountBalance(1));
    ASSERT_EQ("Principale", ac.getAccountName(1));
    ASSERT_EQ("Lorenzo", ac.getAccountUser(1));
    ASSERT_EQ(0, ac.getAccountBalance(2));
    ASSERT_EQ("Secondario", ac.getAccountName(2));
    ASSERT_EQ("Lorenzo", ac.getAccountUser(2));
}

TEST_F(AccountManagerTest, CreateAccount) {
    //testo creazione nuovo account
    ac.createAccount("Principale", "Pippo");
    
    ASSERT_EQ(0, ac.getAccountBalance(3));
    ASSERT_EQ("Principale", ac.getAccountName(3));
    ASSERT_EQ("Pippo", ac.getAccountUser(3));
}

TEST_F(AccountManagerTest, DeleteAccounts) {
    //test cancellazione di un account e test se numero account è corretto
    ac.createAccount("Principale", "Pippo");

    ASSERT_EQ(0, ac.getAccountBalance(3));
    ASSERT_EQ("Principale", ac.getAccountName(3));
    ASSERT_EQ("Pippo", ac.getAccountUser(3));
    ASSERT_EQ(3, ac.getNumberOfAccounts());
    ac.deleteAccount(2);
    ASSERT_EQ(2, ac.getNumberOfAccounts());
    ac.deleteAccount(3);
    ASSERT_EQ(1, ac.getNumberOfAccounts());
}


TEST_F(AccountManagerTest, DeleteWrongAccount) {
    //test cancellazione di un account e test se numero account è sbagliato
    EXPECT_THROW(ac.deleteAccount(5), range_error);
}

TEST_F(AccountManagerTest, InsertTransactionGainExpense) {
    //test inserimento di transazioni gain ed expense
    Date d = Date(25, 05, 2020);
    ac.createTransaction(Type::Gain, 1, 500.5, d);
    ac.createTransaction(Type::Expense, 2, 400, d);

    ASSERT_EQ(500.5,ac.getAccountBalance(1));
    ASSERT_EQ(-400, ac.getAccountBalance(2));
}


TEST_F(AccountManagerTest, InsertTransactionTransfer) {
    //test inserimento di transazioni gain, expense e transfer
    Date d = Date(25, 05, 2020);
    ac.createTransaction(Type::Gain, 1, 500.5, d);
    ac.createTransaction(Type::Expense, 2, 400, d);
    ac.createTransaction(Type::Transfer, 1, 100, d,2);

    ASSERT_EQ(400.5, ac.getAccountBalance(1));
    ASSERT_EQ(-300, ac.getAccountBalance(2));
}

TEST_F(AccountManagerTest, ModifyTransactions) {
    //test modifica di una transazione
    Date d = Date(25, 05, 2020);
    ac.createTransaction(Type::Gain, 1, 500.5, d);
    ac.createTransaction(Type::Expense, 2, 400, d);
    ac.createTransaction(Type::Transfer, 1, 100, d, 2);

    ac.modifyTransaction(1,1,300,d);
    ac.modifyTransaction(2, 2, 300, d);
    ASSERT_EQ(200, ac.getAccountBalance(1));
    ASSERT_EQ(-200, ac.getAccountBalance(2));
    ac.modifyTransaction(1, 3, 300, d);

    ASSERT_EQ(0, ac.getAccountBalance(1));
    ASSERT_EQ(0, ac.getAccountBalance(2));
}


TEST_F(AccountManagerTest, ModifyTransactionsAndReadFromFile) {
    //test inserimento transazioni, e lettura da file
    Date d = Date(25, 05, 2020);
    ac.createTransaction(Type::Gain, 1, 500.5, d);
    ac.createTransaction(Type::Expense, 2, 400, d);
    ac.createTransaction(Type::Transfer, 1, 100,d, 2);

    ac.modifyTransaction(1, 1, 300,d);
    ac.modifyTransaction(2, 2, 300, d);
    ASSERT_EQ(200, ac.getAccountBalance(1));
    ASSERT_EQ(-200, ac.getAccountBalance(2));

    AccountManager a;
    a=a.readFromFile("C:\\Users\\lorec\\source\\repos\\Project1\\Project1\\Accounts.txt");
    ASSERT_EQ(200, a.getAccountBalance(1));
    ASSERT_EQ(-200, a.getAccountBalance(2));
    

}



TEST_F(AccountManagerTest, CancelTransactions) {
    //test cancellazione di una transazione
    Date d = Date(25, 05, 2020);
    ac.createTransaction(Type::Gain, 1, 500.5, d);
    ac.createTransaction(Type::Expense, 2, 400, d);
    ac.createTransaction(Type::Transfer, 1, 100, d, 2);

    ac.modifyTransaction(1, 1, 300, d);
    ac.modifyTransaction(2, 2, 300, d);
    ASSERT_EQ(200, ac.getAccountBalance(1));
    ASSERT_EQ(-200, ac.getAccountBalance(2));
    ac.modifyTransaction(1, 3, 300, d);
    ac.eraseTransaction(2,2);

    ASSERT_EQ(0, ac.getAccountBalance(1));
    ASSERT_EQ(300, ac.getAccountBalance(2));
}