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
	string s = to_string(a.id);
	string filedir = dir + "\\" + s;
	_mkdir(filedir.c_str());
	string filename = filedir + "\\" + s;

	std::ofstream ofs(filename);
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
