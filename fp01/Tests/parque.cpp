#include "parque.h"
#include <vector>

using namespace std;

ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli):numMaximoClientes(nMaxCli), lotacao(lot) {
    clientes.clear();
    vagas=lot;
}

unsigned int ParqueEstacionamento::getNumLugares() const {
    return lotacao;
}

unsigned int ParqueEstacionamento::getNumMaximoClientes() const {
    return numMaximoClientes;
}

int ParqueEstacionamento::posicaoCliente(const string &nome) const {
    for(int i = 0; i < clientes.size(); i++){
        if (clientes.at(i).nome == nome) {
            return i;
        }
    }
    return -1;
}

bool ParqueEstacionamento::adicionaCliente(const string &nome) {
    if(clientes.size()==numMaximoClientes) {
        return false;
    }
    InfoCartao newclient;
    newclient.nome=nome;
    newclient.presente=false;
    clientes.push_back(newclient);
    return true;
}

bool ParqueEstacionamento::entrar(const string &nome) {
    short pos = posicaoCliente(nome);
    if (pos!=-1 && !clientes.at(pos).presente && vagas != 0){
        vagas-=1;
        clientes.at(pos).presente=true;
        return true;
    }
    return false;
}

bool ParqueEstacionamento::retiraCliente(const string &nome) {
    int pos = posicaoCliente(nome);
    if(pos!=-1 && !clientes.at(pos).presente){
        clientes.erase(clientes.begin()+pos);
        return true;
    }
    return false;
}

bool ParqueEstacionamento::sair(const string &nome) {
    int pos = posicaoCliente(nome);
    if(pos!=-1 && clientes.at(pos).presente){
        clientes.at(pos).presente=false;
        return true;
    }
    return false;
}

unsigned int ParqueEstacionamento::getNumLugaresOcupados() const {
    return lotacao-vagas;
}

unsigned int ParqueEstacionamento::getNumClientesAtuais() const {
    return clientes.size();
}