#include "Produto.hpp"
#include <iostream>

// Construtor padrão
Produto::Produto() : nome(""), pesoLiquido(0.0), preco(0.0), unidadesDisponiveis(0), marca(nullptr) {}

// Construtor com todos os parâmetros
Produto::Produto(std::string nome, Marca* marca, double pesoLiquido, double preco)
    : nome(nome), pesoLiquido(pesoLiquido), preco(preco), unidadesDisponiveis(0), marca(marca) {}

// Construtor sem a marca (caso o produto não tenha marca associada)
Produto::Produto(std::string nome, double pesoLiquido, double preco)
    : nome(nome), pesoLiquido(pesoLiquido), preco(preco), unidadesDisponiveis(0), marca(nullptr) {}

// Métodos para acessar os atributos
std::string Produto::getNome() {
    return nome;
}

void Produto::setNome(std::string nome) {
    this->nome = nome;
}

double Produto::getPesoLiquido() {
    return pesoLiquido;
}

void Produto::setPesoLiquido(double pesoLiquido) {
    this->pesoLiquido = pesoLiquido;
}

double Produto::getPreco() {
    return preco;
}

void Produto::setPreco(double preco) {
    this->preco = preco;
}

unsigned Produto::getUnidadesDisponiveis() {
    return unidadesDisponiveis;
}

void Produto::setUnidadesDisponiveis(unsigned unidades) {
    unidadesDisponiveis = unidades;
}

Marca* Produto::getMarca() {
    return marca;
}

void Produto::setMarca(Marca* marca) {
    this->marca = marca;
}

// Verifica se o produto está disponível (quantidade maior que 0)
bool Produto::disponivel() {
    return unidadesDisponiveis > 0;
}

// Adiciona unidades ao estoque
void Produto::adicionarUnidades(unsigned quantidade) {
    unidadesDisponiveis += quantidade;
}
