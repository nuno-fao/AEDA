#include "parque.h"
#include "insertionSort.h"
#include "sequentialSearch.h"
#include <algorithm>
#include <vector>

using namespace std;

bool InfoCartao::operator == (const InfoCartao &ic1) const
{
    return nome == ic1.nome;
}
bool InfoCartao::operator < (const InfoCartao &ic1) const
{
    if (frequencia > ic1.frequencia)
        return true;
    else if (frequencia < ic1.frequencia)
        return false;
    else
        return (nome<ic1.nome);
}

ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli):
	lotacao(lot), numMaximoClientes(nMaxCli) {
    numClientes = 0;
    vagas=lot; 
}

ParqueEstacionamento::~ParqueEstacionamento() {}

vector<InfoCartao> ParqueEstacionamento::getClientes() const { return clientes; }

unsigned int ParqueEstacionamento::getNumLugares() const { return lotacao; }

unsigned int ParqueEstacionamento::getNumLugaresOcupados() const { return lotacao-vagas; }


int ParqueEstacionamento::posicaoCliente(const string &nome) const
{
    InfoCartao name;
    name.nome = nome;
    return sequentialSearch(clientes, name);
}

int ParqueEstacionamento::getFrequencia(const string &nome) const
{
    int pos = posicaoCliente(nome);

    if (pos == -1) throw ClienteNaoExistente(nome);
    cout<<nome<<" "<<clientes[pos].frequencia<<endl;
    return clientes[pos].frequencia;
}

bool ParqueEstacionamento::adicionaCliente(const string & nome)
{
 	if ( numClientes == numMaximoClientes ) return false;
	if ( posicaoCliente(nome) != -1 ) return false;
	InfoCartao info;
	info.nome = nome;
    info.presente = false;
    info.frequencia = 0;
	clientes.push_back(info);
	numClientes++;
	return true;
}

// a alterar/atualizar ?
bool ParqueEstacionamento::retiraCliente(const string & nome)
{
	for (vector<InfoCartao>::iterator it = clientes.begin(); it != clientes.end(); it++)
		if ( it->nome == nome ) {
			if ( it->presente == false ) {
				clientes.erase(it);
				numClientes--;
				return true;
			}
			else return false;
		}
	return false;
}

// a alterar/atualizar ?
bool ParqueEstacionamento::entrar(const string & nome)
{
	if ( vagas == 0 ) return false;
	int pos = posicaoCliente(nome);
	if ( pos == -1 ) return false;
	if ( clientes[pos].presente == true ) return false;
	clientes[pos].presente = true;
    clientes[pos].frequencia++;
	vagas--;
	return true;
}

// a alterar/atualizar ?
bool ParqueEstacionamento::sair(const string & nome)
{
	int pos = posicaoCliente(nome);
	if ( pos == -1 ) return false;
	if ( clientes[pos].presente == false ) return false;
	clientes[pos].presente = false;
	vagas++;
	return true;
}

		
// a implementar
void ParqueEstacionamento::ordenaClientesPorFrequencia()
{
    insertionSort(clientes);
}


// a implementar
void ParqueEstacionamento::ordenaClientesPorNome()
{
}


// a implementar
vector<string> ParqueEstacionamento::clientesGamaUso(int n1, int n2)
{
    ordenaClientesPorFrequencia();
    vector<string> nomes;
    for (unsigned int i=0; i<clientes.size(); i++)
    {
        if (clientes[i].frequencia < n1)
            break;
        if (clientes[i].frequencia <= n2)
            nomes.push_back(clientes[i].nome);
    }
    return nomes;
}

// a implementar
ostream & operator<<(ostream & os, const ParqueEstacionamento & pe)
{
    return os;
}


// a implmentar
InfoCartao ParqueEstacionamento::getClienteAtPos(vector<InfoCartao>::size_type p) const
{
    InfoCartao info;
    return info;
}
