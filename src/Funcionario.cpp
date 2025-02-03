#include "Funcionario.hpp"

Funcionario::Funcionario() : nome(""), sobrenome(""), cpf(""), salarioBruto(0.0), salarioLiquido(0.0) {}

Funcionario::Funcionario(std::string nome, std::string sobrenome, std::string cpf, double salarioBruto)
    : nome(nome), sobrenome(sobrenome), cpf(cpf), salarioBruto(salarioBruto) {
    this->salarioLiquido = salarioBruto * 0.9; // Exemplo de cálculo de salário líquido
}

void Funcionario::setNome(std::string nome) {
    this->nome = nome;
}

void Funcionario::setSobrenome(std::string sobrenome) {
    this->sobrenome = sobrenome;
}

void Funcionario::setCpf(std::string cpf) {
    this->cpf = cpf;
}

void Funcionario::setSalarioBruto(double salarioBruto) {
    this->salarioBruto = salarioBruto;
    this->salarioLiquido = salarioBruto * 0.9; // Atualiza salário líquido
}

void Funcionario::setSalarioLiquido(double salarioLiquido) {
    this->salarioLiquido = salarioLiquido;
}

std::string Funcionario::getNome() const {
    return nome;
}

std::string Funcionario::getSobrenome() const {
    return sobrenome;
}

std::string Funcionario::getCpf() const {
    return cpf;
}

double Funcionario::getSalarioBruto() const {
    return salarioBruto;
}

double Funcionario::getSalarioLiquido() const {
    return salarioLiquido;
}
