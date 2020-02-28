#include <iostream>
#include <vector>

using namespace std;

/**
 * Versao da classe generica Grafo usando a classe vector
 */

template <class N, class A> class Aresta;

template <class N, class A>
class No {
public:
	N info;
	vector< Aresta<N,A> > arestas;
	No(N inf) {
		info = inf;
	}
};

template <class N, class A>
class Aresta {
public:
	A valor;
	No<N,A> *destino;
	Aresta(No<N,A> *dest, A val) {
		valor = val;
		destino = dest;
	}
};

template <class N, class A> 
class Grafo { 
	vector< No<N,A> *> nos;
  public: 
    Grafo()= default;
    ~Grafo(){
        for(typename vector< No<N,A>*>::iterator it = nos.begin();it!=nos.end();++it){
            it->~No();
        }
    }
    Grafo & inserirNo(const N &dados){
        for(auto it:nos){
            if(it->info==dados.info){
                throw NoRepetido(dados.info);
            }
        }
        nos.push_back(dados);
        return this;
    }
    Grafo & inserirAresta(const N &inicio, const N &fim, const A &val){
        for(auto it:nos){
            if(it->info==inicio.info){
                Aresta<N,A> *cona=new Aresta<N,A>(fim,val);
                it->arestas.push_back(cona);
                return this;
            }
        }
        throw NoInexistente(inicio);
    }
    Grafo & eliminarAresta(const N &inicio, const N &fim);
    A & valorAresta(const N &inicio, const N &fim);
    int numArestas(void) const{
        int counter=0;
        for(auto it:nos){
            counter+=it->arestas.size();
        }
        return counter;
    }
    int numNos(void) const{
        return nos.size();
    }
    void imprimir(std::ostream &os) const; 
};

template <class N, class A> 
std::ostream & operator<<(std::ostream &out, const Grafo<N,A> &g);


// excecao NoRepetido
template <class N>
class NoRepetido
{
public:
   N info;
   NoRepetido(N inf) { info=inf; }
};
template <class N> 
std::ostream & operator<<(std::ostream &out, const NoRepetido<N> &no)
{ out << "No repetido: " << no.info; return out; }


// excecao NoInexistente
template <class N>
class NoInexistente {
public:
	N info;
	NoInexistente(N inf) {
		info = inf;
	}
};

template <class N>
std::ostream & operator<<(std::ostream &out, const NoInexistente<N> &ni)
{ out << "No inexistente: " << ni.info; return out; }


