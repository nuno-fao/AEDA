#include "frota.h"
#include <string>

using namespace std;

void Frota::adicionaVeiculo(Veiculo *v1) {
    veiculos.push_back(v1);
}

int Frota::numVeiculos() const{
    return veiculos.size();
}

int Frota:: menorAno() const{
    int ano = 99999;
    if(!veiculos.empty()){
        for(vector<Veiculo*>::const_iterator it=veiculos.begin(); it!=veiculos.end(); ++it){
            if((*it)->getAno()<ano){
                ano=(*it)->getAno();
            }
        }
        return ano;
    }
    return 0;
}

vector<Veiculo *> Frota::operator()(int anoM) const {
    vector<Veiculo *> out;
    if(!veiculos.empty()){
        for(vector<Veiculo*>::const_iterator it=veiculos.begin(); it!=veiculos.end(); ++it){
            if((*it)->getAno() == anoM){
                out.push_back(*it);
            }
        }
    }
    return out;

}

float Frota::totalImposto() const{
    float total=0;
    if(!veiculos.empty()){
        for(vector<Veiculo*>::const_iterator it=veiculos.begin(); it!=veiculos.end(); ++it){
            total+=(*it)->calcImposto();
        }
    }
    return total;
}

ostream & operator<<(ostream & o, const Frota & f){
    if(!f.veiculos.empty()){
        for(vector<Veiculo*>::const_iterator it=f.veiculos.begin(); it!=f.veiculos.end(); ++it){
            (*it)->info();
        }
    }
    return o;
}