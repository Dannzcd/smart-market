#include "Funcionario.hpp"
#include <iostream>

Funcionario::Funcionario(std::string nome, std::string cpf){
    this->nome = nome;
    this->cpf = cpf;
}

Funcionario::Funcionario(std::string nome, std::string cpf, double salarioBruto){
    this->nome = nome;
    this->cpf = cpf;
    this->salarioBruto = salarioBruto;
}

Funcionario::Funcionario(){
    
}

void Funcionario::setSalarioBruto(double salarioBruto){
    this->salarioBruto = salarioBruto;
}

void Funcionario::setSalarioLiquido(double salarioLiquido){
    this->salarioLiquido = salarioLiquido;
}

void Funcionario::setCpf(std::string cpf){
    this->cpf = cpf;
}

double Funcionario::getSalarioBruto(){
    return this->salarioBruto;
}