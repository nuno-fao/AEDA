/*
 * jogo.cpp
 */

#include "jogo.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;


unsigned int Jogo::numPalavras(string frase)
{
  if ( frase.length() == 0 ) return 0;

  unsigned n=1;
  size_t pos = frase.find(' ');
  while (pos != string::npos) {
    frase = frase.substr(pos+1);
    pos = frase.find(' ');
    n++;
  }
  return n;
}

Jogo::Jogo()
= default;

Jogo::Jogo(list<Crianca>& lc2)
{
    criancas = lc2;
}

void Jogo::insereCrianca(const Crianca &c1)
{
    criancas.push_back(c1);
}

list<Crianca> Jogo::getCriancasJogo() const
{
    list<Crianca> res;
    res=criancas;
    return res;
}

string Jogo::escreve() const
{
    string res;
    for (list<Crianca>::const_iterator it=criancas.begin(); it != criancas.end(); ++it){
        res+=it->escreve()+"\n";
    }
    return res;
}

Crianca& Jogo::perdeJogo(string frase)
{
    Crianca *c1 = new Crianca();
    int total_palavras = numPalavras(frase);
    int counter=1;
    list<Crianca>::iterator it;
    while(true){
        it=criancas.begin();
        while(it!=criancas.end()){
            if(counter==total_palavras){
                criancas.erase(it++);
                counter=1;
                if(criancas.size()==1){
                    *c1=criancas.front();
                    return *c1;
                }
            }
            else{
                ++counter;
                ++it;
            }
        }
    }

}

list<Crianca>& Jogo::inverte()
{
    criancas.reverse();
    return criancas;
}

list<Crianca> Jogo::divide(unsigned id)
{
    list<Crianca> res;
    list<Crianca>::iterator it=criancas.begin();
    while(it!=criancas.end()){
        if(it->getIdade()>id) {
            res.push_back(*it);
            criancas.erase(it++);
        }
        else{
            ++it;
        }
    }
    return res;
}

void Jogo::setCriancasJogo(const list<Crianca>& l1)
{
    criancas=l1;
}

bool Jogo::operator==(Jogo& j2)
{
    return criancas == j2.getCriancasJogo();
}

list<Crianca> Jogo::baralha() const
{
    list<Crianca> res;
    res=criancas;

// copy it into a vector and shuffle it
    vector<Crianca> temp(res.begin(), res.end());
    random_shuffle(temp.begin(), temp.end());

// copy the (shuffled) vector back into the list
    std::copy(temp.begin(), temp.end(), res.begin());
    return res;
}
