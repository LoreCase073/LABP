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
	for (int i = 0; i < this->transactions.size(); i++) {
		if (this->transactions[i].getTransactionId() == tid) {
			this->transactions[i].setDate(year, month, day);

			float difference = this->transactions[i].getImport() - import;
			if (this->transactions[i].getType()==Type::Gain) {
				this->balance = this->balance - difference;
			}
			else if (this->transactions[i].getType() == Type::Expense) {
				this->balance = this->balance + difference;
			}
			else if (this->transactions[i].getAccountIdFrom() == this->getId()) {
				this->balance = this->balance + difference;
			}
			else {
				this->balance = this->balance - difference;
			}
			this->transactions[i].setImport(import);
			if (this->transactions[i].getType()==Type::Transfer) {
				if (this->transactions[i].getAccountIdFrom() == this->getId()) {
					ar[0] = this->transactions[i].getAccountIdTo();
					ar[1] = this->transactions[i].getTransactionId();
				}
				else {
					ar[0] = this->transactions[i].getAccountIdFrom();
					ar[1] = this->transactions[i].getTransactionId();
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
	for (int i = 0; i < this->transactions.size(); i++) {
		if (this->transactions[i].getTransactionId() == tid) {

			float difference = this->transactions[i].getImport();
			if (this->transactions[i].getType() == Type::Gain) {
				this->balance = this->balance - difference;
			}
			else if (this->transactions[i].getType() == Type::Expense) {
				this->balance = this->balance + difference;
			}
			else if (this->transactions[i].getAccountIdFrom() == this->getId()) {
				this->balance = this->balance + difference;
			}
			else {
				this->balance = this->balance - difference;
			}
			if (this->transactions[i].getType() == Type::Transfer) {
				if (this->transactions[i].getAccountIdFrom() == this->getId()) {
					ar[0] = this->transactions[i].getAccountIdTo();
					ar[1] = this->transactions[i].getTransactionId();
				}
				else {
					ar[0] = this->transactions[i].getAccountIdFrom();
					ar[1] = this->transactions[i].getTransactionId();
				}
			}
			else {
				//serve per controllo, vuol dire che non è un transfer
				//modificare con eccezioni
				ar[0] = 0;
				ar[1] = 0;
			}
			this->transactions.erase(this->transactions.begin() + i);
			
		}
	}
	
}

void Conto::visualizeTransactions()
{
	cout << "Lista transazione del conto: " << this->getAccountName()<<endl;
	for (int i = 0; i < this->transactions.size(); i++) {
		cout << "Transaction ID: " << this->transactions[i].getTransactionId() << "\t";
		cout << "Import: " << this->transactions[i].getImport() << "\t";

		cout << "Day: " << this->transactions[i].getDay() << "\t";
		cout << "Month: " << this->transactions[i].getMonth() << "\t";
		cout << "year: " << this->transactions[i].getYear() << "\t";

		
	}
}
