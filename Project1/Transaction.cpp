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

Transaction::~Transaction() {
	// TODO Auto-generated destructor stub
}

