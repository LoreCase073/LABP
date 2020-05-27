/*
 * Transaction.cpp
 *
 *  Created on: 11 feb 2020
 *      Author: lorec
 */

#include <string>
#include "Transaction.h"
using namespace std;

Transaction::Transaction(string t, float i, string a, int id, int tid, int d, int m, int y, string a2, int aid2, int tid2, bool receiver) {
	this->opType=t;
	this->import=i;
	this->account =a;
	this->aid=id;
	this->tid=tid;
	this->day=d;
	this->month = m;
	this->year=y;
	this->account2=a2;
	this->receiver = receiver;
	this->aid2 = aid2;
	this->tid2 = tid2;

}
Transaction::Transaction(){

}

string Transaction::getType()
{
	return this->opType;
}

float Transaction::getImport()
{
	return this->import;
}

void Transaction::setImport(float i)
{
	this->import = i;
}

string Transaction::getAccount2()
{
	return this->account2;
}

int Transaction::getTransactionId()
{
	return this->tid;
}

int Transaction::getAccountId2()
{
	return this->aid2;
}

int Transaction::getTransactionId2()
{
	return this->tid2;
}

int Transaction::getDay()
{
	return this->day;
}

void Transaction::setDay(int d)
{
	this->day = d;
}

int Transaction::getMonth()
{
	return this->month;
}

void Transaction::setMonth(int m)
{
	this->month = m;
}

int Transaction::getYear()
{
	return this->year;
}

void Transaction::setYear(int y)
{
	this->year = y;
}

bool Transaction::getReceiver()
{
	return this->receiver;
}

Transaction::~Transaction() {
	// TODO Auto-generated destructor stub
}

