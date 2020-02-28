/*
 * Purchase.cpp
 *
 *  Created on: Nov 16, 2016
 *      Author: hlc
 */

#include "Purchase.h"

using namespace std;

Purchase::Purchase(long cli) : client (cli) {
}

long Purchase::getClient() const {
	return client;
}

list< stack<Article*> > Purchase::getBags() const {
	return bags;
}

/**
 * Create an Article associated with the client of this purchase.
 */
Article* Purchase::createArticle(long barCode, bool present, bool deliverHome) {

	Article *out= new Article(client,barCode);
    out->setPresent(present);
    out->setDeliverHome(deliverHome);
	return out;

}

/**
 * Add an Article to the bags of this purchase. A new bag is added when the last bag is full.
 */
void Purchase::putInBag(Article* article) {

    if(bags.back().size()<BAG_SIZE){
        bags.back().push(article);
    }
    else{
        stack<Article*> s;
        s.push(article);
        bags.push_back(s);
    }
}

/**
 * Pop from the bags all articles that are presents.
 * All other articles are pushed back into the bags where they were, maintaining order.
 */
vector<Article*> Purchase::popPresents() {
    stack<Article*> copia;
    vector<Article*> presents;
	for(list<stack<Article*>>::iterator it=bags.begin();it!=bags.end();it++){
	    while(!(it->empty())){
	        if(it->top()->getPresent()){
	            presents.push_back(it->top());
	        }
	        else{
	            copia.push(it->top());
	        }
	        it->pop();
	    }
	    while(!copia.empty()){
	        it->push(copia.top());
	        copia.pop();
	    }
	}


	return presents;

}

