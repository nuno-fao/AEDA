/*
 * AfterSalesService.cpp
 *
 *  Created on: Nov 16, 2016
 *      Author: hlc
 */

#include <algorithm>
#include "AfterSalesService.h"

using namespace std;

int AfterSalesService::tableOrdinal = 0;

AfterSalesService::AfterSalesService(int toWrapQS) : toWrapQueueSize(toWrapQS) {
}

vector<Article*> AfterSalesService::getPresentsTable() const {
	return presentsTable;
}

queue<Article*> AfterSalesService::getToWrap() const {
	return toWrap;
}

queue<Article*> AfterSalesService::getToDeliver() const {
	return toDeliver;
}

/**
 *  Place presents on the presents table, assigning them a relative present number and a sequential number.
 *  Assumes all given presents are from the same client.
 */
void AfterSalesService::dropPresentsOnTable(vector<Article*> presents) {
	for(vector<Article*>::size_type i = 0; i<presents.size(); i++) {
		presents[i]->setPresentNumber(i+1);
		presents[i]->setArrivalNumber(++tableOrdinal);
		presentsTable.push_back(presents[i]);
	}
}

/**
 * Remove from the table all articles of a given client.
 */
vector<Article*> AfterSalesService::pickPresentsFromTable(long client) {

	vector<Article*> clientPresents;
	vector<Article*>::iterator it=presentsTable.begin();
	while(it!=presentsTable.end()){
	    if((*it)->getClient()==client){
	        clientPresents.push_back(*it);
	        presentsTable.erase(it);
	    }
	    else{
	        it++;
	    }
	}
	return clientPresents;
}

/**
 * Sort the first 10 articles in the presents table:
 *   (i) give priority to articles that are NOT to be delivered at home (client is waiting);
 *  (ii) if two articles have (relative) present numbers differing more than 2,
 *       the one with lower present number should have priority (clients should not wait too much);
 * (iii) else, maintain article order in the table.
 */
bool cmp(Article* a1, Article* a2){
    if(abs(a1->getPresentNumber()-a2->getPresentNumber())>2){
        return (a1->getPresentNumber()<a2->getPresentNumber());

    }
    else {
        return a1->getArrivalNumber() > a2->getArrivalNumber();
    }
}
void AfterSalesService::sortArticles() {
    int counter = 0;
    for(auto it = presentsTable.begin(); it != presentsTable.begin()+10; it++){
        if ((*it)->getDeliverHome()) {
            presentsTable.insert(presentsTable.begin()+10,*it);
            it = -- presentsTable.erase(it);
            counter++;
        }
    }
	sort(presentsTable.begin(),presentsTable.begin()+10-counter,cmp);

}

/**
 * Move the first presents in the table to the queue of presents to wrap, taking into account the size of the queue.
 */
void AfterSalesService::enqueueArticles() {

	while(toWrap.size()!=AfterSalesService::toWrapQueueSize && presentsTable.size()>0){
	    toWrap.push(presentsTable.front());
	    presentsTable.erase(presentsTable.begin());
	}

}

/**
 * Process the first present to wrap. If it is an article to deliver home, the article is placed in the toDeliver queue.
 */
Article* AfterSalesService::wrapNext() {

	if(toWrap.front()->getDeliverHome()){
	    toDeliver.push(toWrap.front());
	    toWrap.pop();
	    return NULL;
	}
	else{
	    Article* out = toWrap.front();
	    toWrap.pop();
	    return out;
	}


}

