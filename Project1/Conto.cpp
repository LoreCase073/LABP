/*
 * Conto.cpp
 *
 *  Created on: 11 feb 2020
 *      Author: lorec
 */

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <direct.h>

#include "Conto.h"
#include "Transaction.h"
using namespace std;

Conto::Conto(string p, string nc, int id) {
	this->user = p;
	this->accountName = nc;
	this->id = id;
	this->transCounter=1;
	this->balance = 0;

}

Conto::Conto(const Conto& copy)
{
	this->user = copy.user;
	this->accountName = copy.accountName;
	this->id = copy.id;
	this->transCounter = copy.transCounter;
	this->balance = copy.balance;
	this->transactions = copy.transactions;
}

Conto::Conto(){}

Conto::~Conto() {
	// TODO Auto-generated destructor stub
}

void Conto::setUser(string x){
	this->user = x;
}

string Conto::getUser(){
	return this->user;
}

void Conto::setAccountName(string n){
	this->accountName = n;
}

string Conto::getAccountName(){
	return this->accountName;
}

float Conto::getBalance(){
	return this-> balance;
}

int Conto::getId(){
	return this-> id;
}

int Conto::getTransCounter(){
	return this-> transCounter;
}

void Conto::incrementCounter(){
	this->transCounter=this->transCounter+1;
}

void Conto::saveOnFile(string dir)
{
	Conto a(*this);
	// save data to archive
	

	std::ofstream ofs(dir);
	{
		boost::archive::text_oarchive oa(ofs);
		// write class instance to archive
		oa << a;
		// archive and stream closed when destructors are called
	}
}




Conto Conto::readFromFile(string dir, int id)
{
	string s = to_string(id);
	string filedir = dir + "\\" + s;
	string filename = filedir + "\\" + s;
	Conto newg;
	{
		// create and open an archive for input
		std::ifstream ifs(filename);
		boost::archive::text_iarchive ia(ifs);
		// read class state from archive
		ia >> newg;
		// archive and stream closed when destructors are called
	}
	return  newg;
}

void Conto::insertTransfer(float import, int day, int month, int year, Conto* account2){
	if(account2 == NULL) //we can't transfer without a destination
	{
		cout<<"Error! You have to select an account to transfer to!"<<endl;
	}
	else {
		Transaction t;

		t = Transaction("transfer", import, this->accountName, this->id, this->getTransCounter(), day, month, year, account2->getAccountName(), account2->getId(), account2->getTransCounter(), false);
		this->transactions.push_back(t);
		this->balance = this->balance - import;

		Transaction t2 = Transaction("transfer", import, account2->accountName, account2->getId(), account2->getTransCounter(), day, month, year, this->getAccountName(), this->getId(), this->getTransCounter(), true);

		account2->transactions.push_back(t2);
		account2->balance = account2->balance + import;

		this->incrementCounter();
		account2->incrementCounter();
			
			
		
	}

}

void Conto::modifyTrans(int tid, float import, int day, int month, int year, int* ar)
{
	ar[0] = 0;
	ar[1] = 0;
	for (int i = 0; i < this->transactions.size(); i++) {
		if (this->transactions[i].getTransactionId() == tid) {
			this->transactions[i].setDay(day);
			this->transactions[i].setMonth(month);
			this->transactions[i].setYear(year);

			float difference = this->transactions[i].getImport() - import;
			if (this->transactions[i].getType()=="gain") {
				this->balance = this->balance - difference;
			}
			else if (this->transactions[i].getType() == "expense") {
				this->balance = this->balance + difference;
			}
			else if (this->transactions[i].getReceiver()==true) {
				this->balance = this->balance - difference;
			}
			else {
				this->balance = this->balance + difference;
			}
			this->transactions[i].setImport(import);
			if (this->transactions[i].getType()=="transfer") {
				ar[0] = this->transactions[i].getAccountId2();
				ar[1] = this->transactions[i].getTransactionId2();
			}
		}
	}
	
}

void Conto::eraseTransfer(int tid, int* ar)
{
	ar[0] = -1;
	ar[1] = -1;
	for (int i = 0; i < this->transactions.size(); i++) {
		if (this->transactions[i].getTransactionId() == tid) {

			float difference = this->transactions[i].getImport();
			if (this->transactions[i].getType() == "gain") {
				this->balance = this->balance - difference;
			}
			else if (this->transactions[i].getType() == "expense") {
				this->balance = this->balance + difference;
			}
			else if (this->transactions[i].getReceiver() == true) {
				this->balance = this->balance - difference;
			}
			else {
				this->balance = this->balance + difference;
			}
			if (this->transactions[i].getType() == "transfer") {
				
				ar[0] = this->transactions[i].getAccountId2();
				ar[1] = this->transactions[i].getTransactionId2();
				this->transactions.erase(this->transactions.begin()+i);
				
			}
			else {
				ar[0] = 0;
				ar[1] = 0;
			}
			this->transactions.erase(this->transactions.begin() + i);
			
		}
	}
	
}

void Conto::insertGain(float import, int day, int month, int year)
{
	Transaction t = Transaction("gain", import, this->accountName, this->id, this->getTransCounter(), day, month, year);
	
	this->balance = this->balance + import;
	
	this->incrementCounter();

	this->transactions.push_back(t);
}

void Conto::insertExpense(float import, int day, int month, int year)
{
	Transaction t = Transaction("expense", import, this->accountName, this->id, this->getTransCounter(), day, month, year);

	this->balance = this->balance - import;

	this->incrementCounter();

	this->transactions.push_back(t);
}

int Conto::getNumberOfTrans()
{
	return this->transactions.size();
}

void Conto::visualizeTransactions()
{
	cout << "Lista transazione del conto: " << this->getAccountName()<<endl;
	for (int i = 0; i < this->transactions.size(); i++) {
		cout << "Transaction ID: " << this->transactions[i].getTransactionId() << "\t";
		cout << "Type: " << this->transactions[i].getType() << "\t";
		cout << "Import: " << this->transactions[i].getImport() << "\t";

		cout << "Day: " << this->transactions[i].getDay() << "\t";
		cout << "Month: " << this->transactions[i].getMonth() << "\t";
		cout << "year: " << this->transactions[i].getYear() << "\t";

		if (this->transactions[i].getType() == "transfer") {
			if (this->transactions[i].getReceiver()) {
				
			}
			else {
				cout << "Trasferimento in uscita " << "\t";
			}
			
			cout << "Conto Coinvolto: " << this->transactions[i].getAccount2() << "\t";
			cout << "ID2: " << this->transactions[i].getAccountId2() << "\t";
			cout << "Transaction ID2: " << this->transactions[i].getTransactionId2() << "\t";

		}
	}
}
