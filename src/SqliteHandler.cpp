#include "SqliteHandler.hpp"
#include <iostream>

bool SqliteHandler::executarOperacao(Operacao operacao, const std::string& tabela, const std::string& parametro){
    /* if (!rc){
        std::cerr << "Não foi possível abrir a base de dados" << std::endl;
        return false;
    } */

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

bool SqliteHandler::criarTabela(const std::string& nomeTabela){
    char *errorMsg = NULL;
    
    this->rc = sqlite3_open(NOME_ARQUIVO_BD, &this->db);

    if (this->rc != SQLITE_OK){
        std::cerr << "DEU RUIM AO ABRIR " << nomeTabela << " PATRAO" << std::endl;
        return false;
    }

    this->rc = sqlite3_exec(db, "PRAGMA foreign_keys = ON;", NULL, NULL, NULL);

    if (this->rc != SQLITE_OK){
        std::cerr << "DEU RUIM NA HORA DE EXECUTAR ARGUMENTO" << std::endl;
        std::cerr << "ERRO COD: " << this->rc << std::endl;
        std::cerr << "ERRO MSG: " << errorMsg << std::endl;
        return false;
    }

    this->rc = sqlite3_exec(db, nomeTabela.c_str(), NULL, NULL, &errorMsg);

    if (this->rc != SQLITE_OK){
        std::cerr << "DEU RUIM NA HORA DE EXECUTAR" << std::endl;
        std::cerr << "ERRO COD: " << this->rc << std::endl;
        std::cerr << "ERRO MSG: " << errorMsg << std::endl;
        sqlite3_free(errorMsg);
        return false;
    }

    sqlite3_close_v2(db);
    
    return true;
}

bool SqliteHandler::alterarLinha(const std::string& nomeTabela, const std::string& parametro){
    std::string query;
    
    std::cout << "a" << std::endl;
    return true;
}

bool SqliteHandler::editarLinha(const std::string& nomeTabela, const std::string& parametro){
    std::cout << "b" << std::endl;
    return true;
}

bool SqliteHandler::excluirLinha(const std::string& nomeTabela, const std::string& parametro){
    std::cout << "c" << std::endl;
    return true;
}