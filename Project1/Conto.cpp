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
	this->balance = 0;

}

Conto::Conto(const Conto& copy)
{
	this->user = copy.user;
	this->accountName = copy.accountName;
	this->id = copy.id;
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


void Conto::insertTransaction(Type type, int tid, float import, int day, int month, int year, Conto* account2)
{
	if (type == Type::Gain) {
		Transaction t = Transaction(type, import, this->id, tid, day, month, year);

		this->balance = this->balance + import;

		this->transactions.push_back(t);
	}
	else if (type == Type::Expense) {
		Transaction t = Transaction(type, import, this->id, tid, day, month, year);

		this->balance = this->balance - import;

		this->transactions.push_back(t);
	}
	else {
		Transaction t;

		t = Transaction(type, import, this->id, tid, day, month, year, account2->getId());
		this->transactions.push_back(t);
		this->balance = this->balance - import;

		account2->transactions.push_back(t);
		account2->balance = account2->balance + import;
	}
}



void Conto::modifyTrans(int tid, float import, int day, int month, int year, int* ar)
{
	ar[0] = 0;
	ar[1] = 0;
	list<Transaction>::iterator it;
	for (it = this->transactions.begin(); it != this->transactions.end(); ++it) {
		if (it->getTransactionId() == tid) {
			it->setDate(year, month, day);

			float difference = it->getImport() - import;
			if (it->getType()==Type::Gain) {
				this->balance = this->balance - difference;
			}
			else if (it->getType() == Type::Expense) {
				this->balance = this->balance + difference;
			}
			else if (it->getAccountIdFrom() == this->getId()) {
				this->balance = this->balance + difference;
			}
			else {
				this->balance = this->balance - difference;
			}
			it->setImport(import);
			if (it->getType()==Type::Transfer) {
				if (it->getAccountIdFrom() == this->getId()) {
					ar[0] = it->getAccountIdTo();
					ar[1] = it->getTransactionId();
				}
				else {
					ar[0] = it->getAccountIdFrom();
					ar[1] = it->getTransactionId();
				}
			}
		}
	}
	
}

void Conto::eraseTrans(int tid, int* ar)
{
	//se valore rimane -1, allora vuol dire che la transazione non esiste
	ar[0] = -1;
	ar[1] = -1; 
	list<Transaction>::iterator it;
	for (it = this->transactions.begin(); it != this->transactions.end(); it++) {
		if (it->getTransactionId() == tid) {

			float difference = it->getImport();
			if (it->getType() == Type::Gain) {
				this->balance = this->balance - difference;
			}
			else if (it->getType() == Type::Expense) {
				this->balance = this->balance + difference;
			}
			else if (it->getAccountIdFrom() == this->getId()) {
				this->balance = this->balance + difference;
			}
			else {
				this->balance = this->balance - difference;
			}
			if (it->getType() == Type::Transfer) {
				if (it->getAccountIdFrom() == this->getId()) {
					ar[0] = it->getAccountIdTo();
					ar[1] = it->getTransactionId();
				}
				else {
					ar[0] = it->getAccountIdFrom();
					ar[1] = it->getTransactionId();
				}
			}
			else {
				ar[0] = 0;
				ar[1] = 0;
			}
			it = this->transactions.erase(it);
		}
	}
	
}

void Conto::visualizeTransactions()
{
	cout << "Lista transazione del conto: " << this->getAccountName()<<endl;
	list<Transaction>::iterator it;
	for (it = this->transactions.begin(); it != this->transactions.end(); it++) {
		cout << "Transaction ID: " << it->getTransactionId() << "\t";
		cout << "Import: " << it->getImport() << "\t";

		cout << "Day: " << it->getDay() << "\t";
		cout << "Month: " << it->getMonth() << "\t";
		cout << "year: " << it->getYear() << "\t";

		
	}
}
