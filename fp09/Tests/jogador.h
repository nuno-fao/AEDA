#ifndef JOGADOR_H_
#define JOGADOR_H_

#include "aposta.h"
#include <string>

using namespace std;

//a alterar
struct apostaHash
{
	int operator() (const Aposta & ap) const
	{
		unsigned total=0;
        for(tabHInt::const_iterator it=ap.getNumeros().begin();it!=ap.getNumeros().end();it++){
            total+=*it;
        }
        return total%12;
	}
	
	bool operator() (const Aposta & ap1, const Aposta & ap2) const
	{
	    if(ap1.getNumeros().size()==ap2.getNumeros().size()){
            tabHInt::const_iterator it2=ap2.getNumeros().begin();
	        return (ap1.calculaCertos(ap2.getNumeros())==ap1.getNumeros().size());
	    }
	    return false;
	}
};



typedef unordered_set<Aposta, apostaHash, apostaHash> tabHAposta;

class Jogador
{
	tabHAposta apostas;
	string nome;
public:
	Jogador(string nm="anonimo") { nome=nm; }
	void adicionaAposta(const Aposta & ap);
	unsigned apostasNoNumero(unsigned num) const;
	tabHAposta apostasPremiadas(const tabHInt & sorteio) const;
	unsigned getNumApostas() const { return apostas.size(); }
};

#endif /*JOGADOR1_H_*/
