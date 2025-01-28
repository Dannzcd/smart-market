#include "Marca.hpp"

// Construtor padrão
Marca::Marca() : nome("") {}

// Construtor com nome
Marca::Marca(std::string nome) : nome(nome) {}

// Método para obter o nome da marca
std::string Marca::getNome() {
    return nome;
}

// Método para definir o nome da marca
void Marca::setNome(std::string nome) {
    this->nome = nome;
}
