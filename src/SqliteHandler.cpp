#include "SqliteHandler.hpp"
#include <iostream>

bool SqliteHandler::executarOperacao(Operacao operacao, const std::string& tabela, const std::string& parametro){
    if (!rc){
        std::cerr << "Não foi possível abrir a base de dados" << std::endl;
        return false;
    }

    switch (operacao) {
        case Operacao::CRIAR_TABELA:
            return criarTabela(tabela);
        case Operacao::ALTERAR_LINHA:
            return alterarLinha(tabela, parametro);
        case Operacao::EDITAR_LINHA:
            return editarLinha(tabela, parametro);
        case Operacao::EXCLUIR_LINHA:
            return excluirLinha(tabela, parametro);
        default:
            return false; // Operação inválida
    }
}

bool SqliteHandler::criarBaseDados(){
    //Nao vai dar erro, eu confio
    //char **mensagemErro = NULL;

    this->rc = sqlite3_open(NOME_ARQUIVO_BD, &this->db);   
    
    std::cout << "Retorno: " << this->rc << std::endl;

    if (rc != SQLITE_OK){
        return false;
    }
    
    sqlite3_close_v2(db);
    return true;
}

bool SqliteHandler::criarTabela(const std::string& tabela){
    this->rc = sqlite3_open(NOME_ARQUIVO_BD, &this->db);

    if (this->rc != SQLITE_OK){
        return false;
    }

    this->rc = sqlite3_exec(db, TABELA_FUNCIONARIO.c_str(), NULL, NULL, NULL);

    if (this->rc != SQLITE_OK){
        return false;
    }

    sqlite3_close_v2(db);
    
    return true;
}

bool SqliteHandler::alterarLinha(const std::string& tabela, const std::string& parametro){
    std::string query;
    
    std::cout << "a" << std::endl;
    return true;
}

bool SqliteHandler::editarLinha(const std::string& tabela, const std::string& parametro){
    std::cout << "b" << std::endl;
    return true;
}

bool SqliteHandler::excluirLinha(const std::string& tabela, const std::string& parametro){
    std::cout << "c" << std::endl;
    return true;
}