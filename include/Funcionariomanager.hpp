#ifndef FUNCIONARIOMANAGER_HPP
#define FUNCIONARIOMANAGER_HPP

#include <map>
#include "Funcionario.hpp"

class FuncionarioManager {
private:
    std::map<std::string, Funcionario> funcionarios;  // Usando o CPF como chave

public:
    void cadastrarFuncionario();
    void editarFuncionario(std::string cpf);
    void excluirFuncionario(std::string cpf);
    void exibirFuncionario(std::string cpf);
};

#endif
