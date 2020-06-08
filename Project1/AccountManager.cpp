#include "AccountManager.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <direct.h>

AccountManager::AccountManager()
{

}

AccountManager::AccountManager(string dir)
{
	this->directory = dir;
	this->saveOnFile(dir);
}

void AccountManager::saveOnFile(string dir)
{
	AccountManager a(*this);
	// save data to archive


	std::ofstream ofs(dir);
	{
		boost::archive::text_oarchive oa(ofs);
		// write class instance to archive
		oa << a;
		// archive and stream closed when destructors are called
	}
}

AccountManager AccountManager::readFromFile(string dir)
{
	AccountManager newg;
	{
		// create and open an archive for input
		std::ifstream ifs(dir);
		boost::archive::text_iarchive ia(ifs);
		// read class state from archive
		ia >> newg;
		// archive and stream closed when destructors are called
	}
	return  newg;
}

void AccountManager::createAccount(string name, string user)
{
	Conto a = Conto(user, name, accountCounter);
	
	this->accounts.push_back(a);
	
	this->incrementCounter();
	saveOnFile(this->directory);
}

void AccountManager::deleteAccount(int id)
{
	bool found = false;
	for (int i =0; i<this->accounts.size(); i++) {
		Conto a = accounts[i];
		if (a.getId()==id) {
			found = true;
			this->accounts.erase(accounts.begin()+i);
			
		}
	}
	if (found) {
		cout << "Account eliminato" << endl;

	}
	saveOnFile(this->directory);
}


void AccountManager::createTransaction(string trans, int accountId, float importo, int day, int month, int year, int accountId2)
{
	
	int index = this->findAccountIndex(accountId);
	
	
	if (trans=="gain") {
		this->accounts[index].insertGain(importo, day, month, year);
	}
	else if (trans == "expense") {
		this->accounts[index].insertExpense(importo, day, month, year);
	}
	else if (trans == "transfer" && accountId2!=-1) {
		int index2 = this->findAccountIndex(accountId2);
		this->accounts[index].insertTransfer(importo, day, month, year, &this->accounts[index2]);
	}
	else {
		cout << "Errore!" << endl;
	}
	saveOnFile(this->directory);
}

void AccountManager::modifyTransaction(int accountId, int tid, float import, int day, int month, int year)
{
	int index = this->findAccountIndex(accountId);

	if (index == -1) {
		cout << "Errore!" << endl;
	}
	else {
		int c2[2];
		this->accounts[index].modifyTrans(tid, import, day, month, year, c2);
		if (c2[0]!=0) {
			int index2 = this->findAccountIndex(c2[0]);
			if (index2 == -1) {
				cout << "Secondo conto non trovato. Eliminato in precedenza" << endl;
			}
			else {
				this->accounts[index2].modifyTrans(c2[1],import, day, month, year,c2);
			}
		}
	}
	saveOnFile(this->directory);
}

void AccountManager::eraseTransaction(int aid, int tid)
{
	int index = this->findAccountIndex(aid);

	if (index == -1) {
		cout << "Errore!" << endl;
	}
	else {
		int c2[2];
		this->accounts[index].eraseTransfer(tid, c2);
		if (c2[0]!=0 && c2[0]!=-1) {
			int index2 = this->findAccountIndex(c2[0]);
			if (index2 == -1) {
				cout << "Secondo conto non trovato. Eliminato in precedenza" << endl;
			}
			else {
				int tmp[2];
				this->accounts[index2].eraseTransfer(c2[1], tmp);
			}
		}
		else if (c2[0] == -1) {
			cout << "Transazione non trovata" << endl;
		}
	}
	saveOnFile(this->directory);
}


//ritorna -1 se non ha trovato l'account con quell'identificativo
int AccountManager::findAccountIndex(int id)
{
	
	for (int i = 0; i < this->accounts.size(); i++) {
		Conto a = this->accounts[i];
		if (a.getId() == id) {
			return i;
			
		}
	}
	
	return -1;
}

float AccountManager::getAccountBalance(int id)
{
	int index = this->findAccountIndex(id);
	if (index == -1) {
		cout << "Account non trovato!" << endl;
		return 0;
	}
	else
		return this->accounts[index].getBalance();
	 
}

string AccountManager::getAccountName(int id)
{
	int index = this->findAccountIndex(id);
	if (index == -1) {
		cout << "Account non trovato!" << endl;
		return 0;
	}
	else
		return this->accounts[index].getAccountName();
}

string AccountManager::getAccountUser(int id)
{
	int index = this->findAccountIndex(id);
	if (index == -1) {
		cout << "Account non trovato!" << endl;
		return 0;
	}
	else
		return this->accounts[index].getUser();
}

int AccountManager::getNumberOfAccounts()
{
	return this->accounts.size();
}

int AccountManager::getNumberOfTransactions(int id)
{
	int index = this->findAccountIndex(id);
	if (index == -1) {
		cout << "Account non trovato!" << endl;
		return 0;
	}
	else
		return this->accounts[index].getNumberOfTrans();
}


//visualizza i conti presenti 
void AccountManager::visualizeAccounts()
{
	cout << "Lista conti:" << endl;
	for (int i = 0; i < this->accounts.size(); i++){
		cout << "ID: " << this->accounts[i].getId() << "\t";
		cout << "Nome Account: " << this->accounts[i].getAccountName() << "\t";
		cout << "User: " << this->accounts[i].getUser() << "\t";
		cout << "Balance: " << this->accounts[i].getBalance()<<endl << endl;
	}
}

void AccountManager::visualizeTransactions(int d)
{
	int index = this->findAccountIndex(d);
	if (index == -1) {
		cout << "Account non trovato!" << endl;
		
	}
	else {
		this->accounts[index].visualizeTransactions();
	}
}


