#include "Produto.hpp"

Produto::Produto() : nome(""), pesoLiquido(0.0), preco(0.0), unidadesDisponiveis(0), marca(nullptr) {}

Produto::Produto(std::string nome, Marca* marca, double pesoLiquido, double preco)
    : nome(nome), pesoLiquido(pesoLiquido), preco(preco), unidadesDisponiveis(0), marca(marca) {}

Produto::Produto(std::string nome, double pesoLiquido, double preco)
    : nome(nome), pesoLiquido(pesoLiquido), preco(preco), unidadesDisponiveis(0), marca(nullptr) {}

std::string Produto::getNome() const {
    return nome;
}

void Produto::setNome(std::string nome) {
    this->nome = nome;
}

double Produto::getPesoLiquido() const {
    return pesoLiquido;
}

void Produto::setPesoLiquido(double pesoLiquido) {
    this->pesoLiquido = pesoLiquido;
}

double Produto::getPreco() const {
    return preco;
}

void Produto::setPreco(double preco) {
    this->preco = preco;
}

unsigned Produto::getUnidadesDisponiveis() const {
    return unidadesDisponiveis;
}

void Produto::setUnidadesDisponiveis(unsigned unidades) {
    unidadesDisponiveis = unidades;
}

Marca* Produto::getMarca() const {
    return marca;
}

void Produto::setMarca(Marca* marca) {
    this->marca = marca;
}

bool Produto::disponivel() const {
    return unidadesDisponiveis > 0;
}

void Produto::adicionarUnidades(unsigned quantidade) {
    unidadesDisponiveis += quantidade;
}
