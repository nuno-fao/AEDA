#include <queue>
#include <cstdlib>
#include "balcao.h"
#include "exceptions.h"

using namespace std;

//a alterar
Cliente::Cliente() {
    numPresentes=rand()%5+1;
}

//a alterar
int Cliente::getNumPresentes() const {
    return numPresentes;
}

//a alterar
Balcao::Balcao(int te): tempo_embrulho(te) {
    tempo_atual=0;
    prox_chegada=rand()%20+1;
    prox_saida=0;
    clientes_atendidos=0;
}

//a alterar
void Balcao:: proximoEvento()
{
    if (prox_chegada<prox_saida && prox_saida!=0){
        tempo_atual=prox_chegada;
        chegada();
    }
    else{
        tempo_atual=prox_saida;
        saida();
    }
}

//a alterar
void Balcao::chegada()
{
    Cliente novoCliente;
    prox_chegada=rand()%20+1;
    if(clientes.empty()){
        prox_saida=novoCliente.getNumPresentes()*tempo_embrulho;
    }
    clientes.push(novoCliente);
    cout<<tempo_atual<<" Presentes do cliente: "<<novoCliente.getNumPresentes()<<endl;
}

//a alterar
void Balcao::saida()
{
    try{
        Cliente novoCliente = getProxCliente();
        clientes.pop();
        clientes_atendidos+=1;
        prox_saida=clientes.front().getNumPresentes()*tempo_embrulho;
        cout<<tempo_atual<<" Presentes do cliente que saiu: "<<novoCliente.getNumPresentes()<<endl;
    }
    catch(FilaVazia exc){
        cout<<exc.getMsg()<<endl;
    }
}


int Balcao::getTempoAtual() const { return tempo_atual; }

int Balcao::getProxChegada() const { return prox_chegada; }

//a alterar
ostream & operator << (ostream & out, const Balcao & b1)
{
     return out;
}

//a alterar
int Balcao::getTempoEmbrulho() const {
	return tempo_embrulho;
}

//a alterar
int Balcao::getProxSaida() const {
	return prox_saida;
}

//a alterar
int Balcao::getClientesAtendidos() const {
	return clientes_atendidos;
}

//a alterar
Cliente & Balcao::getProxCliente() {
    if(!clientes.empty()){
        return clientes.front();
    }
    throw FilaVazia();
}

      
