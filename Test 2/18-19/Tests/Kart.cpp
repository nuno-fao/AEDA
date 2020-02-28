#include <cstdlib>
#include <iostream>
#include <queue>
#include <sstream>
#include <vector>
#include <algorithm>
#include <time.h>
#include <string>
#include "Kart.h"

using namespace std;

//To help build better array
string itos(int i){
    stringstream s;
    s << i;
    return s.str();
}

void CGrupo::criaGrupo()
{
    float cilindradas[4]  = {134,250,450,600};
    bool avariados[3]  = {true,false,false};

    srand (1);   //Criar Pistas e Karts de Teste
    for(int i=1;i<=50;i++){
        vector<CKart> frota;
        for(int j=1;j<=50;j++){
            frota.push_back(CKart(avariados[rand()% 3],
                                  ("KART - "+itos(i))+itos(j),(i-1)*50+j,cilindradas[(rand() % 4)]));
        }
        adicionaPista(CPista("Pista - "+itos(i),frota));
    }
}


vector <CKart> CPista::getKartsAvariados()
{
    vector<CKart> aux;
    for (vector<CKart>::iterator it = frotaKartsPista.begin() ; it != frotaKartsPista.end(); ++it) {
        if ((it)->getAvariado()) aux.push_back((*it));
    }
    return aux;
}
 
//Exercicio 1 a)
bool cmp(CKart & k1, CKart & k2){
    return k1.getNumero()<k2.getNumero();
}
vector<CKart> CGrupo::ordenaKarts()
{
	vector<CKart> out;
	for(vector<CPista>::iterator it=pistasG.begin();it!=pistasG.end();it++){
	    out.insert(out.end(),it->getFrotaActual().begin(),it->getFrotaActual().end());
	}
    sort(out.begin(),out.end(),cmp);
	return out;
}

//Exercicio 1 b)  
int CGrupo::numAvariados(int cilind)
{
    unsigned out=0;
    vector<CKart> aux;
    for(vector<CPista>::iterator it=pistasG.begin();it!=pistasG.end();it++){
        aux=it->getFrotaActual();
        for(vector<CKart>::iterator it2=aux.begin();it2!=aux.end();it2++){
            if(it2->getCilindrada()==(float)cilind && it2->getAvariado()){
                out++;
            }
        }
    }
    return out;
}

//Exercicio 1 c)   
bool CPista::prepararCorrida(int numeroKarts, int cilind)
{
    unsigned counter = 0;

    for(vector<CKart>::iterator it2=frotaKartsPista.begin();it2!=frotaKartsPista.end();it2++){
        if(it2->getCilindrada()==(float)cilind && !(it2->getAvariado())){
            counter+=1;
            kartsLinhaPartida.push(*it2);
            if(counter==numeroKarts){
                return true;
            }
        }
    }

    return false;

}

//Exercicio 1 d) 
int CPista::inicioCorrida()
{
    while(!kartsLinhaPartida.empty()){
        kartsEmProva.push_back(kartsLinhaPartida.front());
        kartsLinhaPartida.pop();
    }
    return kartsEmProva.size();
}

