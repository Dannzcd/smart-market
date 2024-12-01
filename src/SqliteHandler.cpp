#include "SqliteHandler.hpp"
#include <iostream>

bool SqliteHandler::executarOperacao(Operacao operacao, const std::string& tabela, const std::string& parametro){
    switch (operacao) {
        case Operacao::ALTERAR:
            return alterarTabela(tabela, parametro);
        case Operacao::EDITAR:
            return editarTabela(tabela, parametro);
        case Operacao::EXCLUIR:
            return excluirTabela(tabela, parametro);
        default:
            return false; // Operação inválida
    }
}

bool SqliteHandler::alterarTabela(const std::string& tabela, const std::string& parametro){
    std::cout << "a" << std::endl;
    return true;
}

bool SqliteHandler::editarTabela(const std::string& tabela, const std::string& parametro){
    std::cout << "b" << std::endl;
    return true;
}

bool SqliteHandler::excluirTabela(const std::string& tabela, const std::string& parametro){
    std::cout << "c" << std::endl;
    return true;
}