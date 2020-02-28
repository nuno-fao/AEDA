
#include "animal.h"
#include <sstream>
using namespace std;

/*
 * Classe Animal
 */

string Animal::getNome() const {
	return nome;
}

Animal::Animal(string nome, int idade) {
    this->nome=nome;
    this->idade=idade;
    *vet=malloc(sizeof(*vet));
}

