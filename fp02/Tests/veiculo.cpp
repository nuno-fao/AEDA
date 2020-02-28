#include "veiculo.h"
#include <iostream>
#include <vector>

using namespace std;

 Veiculo::Veiculo(string mc, int m, int a) {
     marca=mc;
     mes=m;
     ano=a;
 }

 int Veiculo::info() const {
     cout<<"Marca: "<<marca<<"\tAno: "<<ano<<"\tMes: "<<mes<<endl;
     return 3;
 }

 int Veiculo::getAno() const {
     return ano;
 }

 string Veiculo::getMarca() const {
     return marca;
 }

 bool Veiculo::operator<(const Veiculo &v) const {
     if(ano<v.ano){
         return true;
     }
     else if(ano==v.ano){
         if(mes<v.mes){
             return true;
         }
     }
     return false;
 }

 Motorizado::Motorizado(string mc, int m, int a, string c, int cil) : Veiculo(mc,m,a){
     combustivel=c;
     cilindrada=cil;
 }

 int Motorizado::info() const {
     Veiculo::info();
     cout<<"Combustivel: "<<combustivel<<"\tCilindrada: "<<cilindrada<<endl;
     return 5;
 }

 float Motorizado::calcImposto() const {
     vector <int> cilgas = {1000,1300,1750,2600,3500};
     vector <int> cilout = {1500, 2000, 3000};
     vector <float> imp95 = {8.10, 14.56, 22.65, 54.89, 87.13, 148.37};
     vector <float> imp00 = {14.56, 29.06, 45.15, 113.98, 181.17, 320.89};
     int cil;
     if (combustivel=="gasolina"){
        for(int i=0;i<cilgas.size();++i){
            if(cilindrada<=cilgas.at(i)){
                cil=i;
            }
            else if(i==cilgas.size()-1){
                cil=i;
            }
        }
     }
     else{
         for(int i=0;i<cilout.size();++i){
             if(cilindrada<=cilout.at(i)){
                 cil=i;
             }
             else if(i==cilout.size()-1){
                 cil=i;
             }
         }
    }
    if(ano>1995){
        return imp00.at(cil);
    }
    else{
        return imp95.at(cil);
    }
 }

 string Motorizado::getCombustivel() const{
     return combustivel;
 }

 Automovel::Automovel(string mc, int m, int a, string c, int cil) : Motorizado(mc,m,a,c,cil){}

 int Automovel::info() const {
    Motorizado::info();
    return 5;
 }

 Camiao::Camiao(string mc, int m, int a, string c, int cil, int cm) : Motorizado(mc,m,a,c,cil){
     carga_maxima=cm;
 }

 int Camiao::info() const {
    Motorizado::info();
    cout<<"Carga max: "<<carga_maxima<<endl;
    return 6;
 }

 Bicicleta::Bicicleta(string mc, int m, int a, string t) : Veiculo(mc,m,a) {
     tipo=t;
 }

 int Bicicleta::info() const {
    Veiculo::info();
    cout<<"Tipo: "<<tipo<<endl;
    return 4;
 }

 float Bicicleta::calcImposto() const {
     return 0;
 }