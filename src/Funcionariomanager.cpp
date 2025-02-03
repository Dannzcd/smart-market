#include "FuncionarioManager.hpp"
#include <iostream>

void FuncionarioManager::cadastrarFuncionario() {
    std::cout << "Iniciando o cadastro do funcionário...\n";

    std::string nome, sobrenome, cpf;
    double salarioBruto;

    std::cout << "Digite o nome do funcionário: ";
    std::getline(std::cin, nome);

    std::cout << "Digite o sobrenome do funcionário: ";
    std::getline(std::cin, sobrenome);

    std::cout << "Digite o CPF do funcionário: ";
    std::getline(std::cin, cpf);

    std::cout << "Digite o salário bruto do funcionário: ";
    std::cin >> salarioBruto;
    std::cin.ignore();  // Limpar o buffer

    Funcionario novoFuncionario(nome, sobrenome, cpf, salarioBruto);
    funcionarios[cpf] = novoFuncionario;

    std::cout << "Funcionário cadastrado com sucesso!\n";
}

void FuncionarioManager::editarFuncionario(std::string cpf) {
