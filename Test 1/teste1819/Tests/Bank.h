/*
 * Bank.h
 */

#ifndef SRC_BANK_H_
#define SRC_BANK_H_

#include "Account.h"
#include <vector>

#include "BankOfficer.h"


class Bank {
	vector<Account *> accounts;
	vector<BankOfficer> bankOfficers;
public:
	Bank();
	void addAccount(Account *a);
	void addBankOfficer(BankOfficer b);
	vector<BankOfficer> getBankOfficers() const;
	vector<Account *> getAccounts() const;

	//-------
	double getWithdraw(string cod1) const;
	vector<Account *> removeBankOfficer(string name);
	const BankOfficer& addAccountToBankOfficer(Account *ac, string name);
	void sortAccounts();
};

template <class T>
unsigned int numberDifferent (const vector<T> & v1){
    vector<T> temp;
    for(unsigned it=0;it<v1.size();++it){
        bool diff=true;
        for(unsigned it2=0;it2<temp.size();++it2){
            if(temp.at(it2)==v1.at(it)){
                diff=false;
                break;
            }
        }
        if(diff) {
            temp.push_back(v1.at(it));
        }
    }
    return temp.size();
}

#endif /* SRC_BANK_H_ */

class NoBankOfficerException {
        string name;
    public:
        NoBankOfficerException(string nm): name(nm){}
        string getName(){return name;}
 };