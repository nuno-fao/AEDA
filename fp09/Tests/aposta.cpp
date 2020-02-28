#include "aposta.h"
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

// a alterar
bool Aposta::contem(unsigned num) const
{
	return numeros.find(num)!=numeros.end();
}

//a alterar
void Aposta::geraAposta(const vector<unsigned> & valores, unsigned n)
{
    for(size_t it=0;it<valores.size();it++){
        if(numeros.find(valores[it])==numeros.end()){
            numeros.insert(valores[it]);
            if(numeros.size()==n){
                break;
            }
        }
    }
}

//a alterar
unsigned Aposta::calculaCertos(const tabHInt & sorteio) const
{
    unsigned counter=0;
    for(tabHInt::const_iterator it=numeros.begin();it!=numeros.end();it++){
        if(sorteio.find(*it)!=sorteio.end()){
            counter++;
        }
    }
    return counter;
}





