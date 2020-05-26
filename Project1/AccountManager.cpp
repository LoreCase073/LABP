#include "AccountManager.h"

#include <iostream>

#include <direct.h>

AccountManager::AccountManager()
{

}

AccountManager::AccountManager(string dir)
{

}

void AccountManager::createAccount(string name, string user)
{
	Conto a = Conto(user, name, accountCounter);
	string dir = this->directory + "\\" + to_string(this->accountCounter);
	_mkdir(dir.c_str());
	string file = this->directory + "\\" + to_string(this->accountCounter) + "\\" + to_string(this->accountCounter) + ".txt";

	this->accounts.push_back(a);
	this->files.push_back(file);
	a.saveOnFile(file);
	this->incrementCounter();
}

void AccountManager::deleteAccount(int id)
{
	bool found = false;
	for (int i =0; i<this->accounts.size(); i++) {
		Conto a = accounts[i];
		if (a.getId()==id) {
			found = true;
			this->accounts.erase(accounts.begin()+i);
			this->files.erase(files.begin()+i);
		}
	}
	if (found) {
		cout << "Account eliminato" << endl;

	}
}
