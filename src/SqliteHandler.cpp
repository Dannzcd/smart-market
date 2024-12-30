#include "SqliteHandler.hpp"
#include "QueryHandler.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>

SqliteHandler::SqliteHandler(){
    this->nomeBD = NOME_ARQUIVO_BD_PADRAO;
}

void SqliteHandler::setQueries(std::string nomeArquivoSQL){
    this->queries = QueryHandler::carregarQueriesDeSetup(&nomeArquivoSQL);
}

std::vector<std::string>* SqliteHandler::getQueries(){
    return this->queries;
}

void SqliteHandler::setNomeBD(std::string& novoNome){
    this->nomeBD = novoNome;
}

bool SqliteHandler::dbExiste(){
    return std::filesystem::exists((CAMINHO_BD_PADRAO+this->nomeBD).c_str());
}

bool SqliteHandler::executarOperacao(Operacao operacao, const std::string nomeArquivoSQL){
    switch (operacao) {
        case Operacao::CRIAR_TABELAS:
            return criarTabelas(nomeArquivoSQL);
        /* case Operacao::ALTERAR_LINHA:
            return alterarLinha(tabela, parametro);
        case Operacao::EDITAR_LINHA:
            return editarLinha(tabela, parametro);
        case Operacao::EXCLUIR_LINHA:
            return excluirLinha(tabela, parametro); */
        default:
            return false; // Operação inválida
    }
}

bool SqliteHandler::criarBaseDados(){
    if (this->dbExiste()) return true;

    std::cout << "a" << std::endl;
    std::string caminhoCompleto(CAMINHO_BD_PADRAO+this->nomeBD);

    this->codigoRetorno = sqlite3_open(caminhoCompleto.c_str(), &this->db);   
    
    std::cout << "Retorno: " << this->codigoRetorno << std::endl;

    if (codigoRetorno != SQLITE_OK){
        return false;
    }
    
    sqlite3_close_v2(db);
    return true;
}

bool SqliteHandler::criarTabelas(const std::string& nomeArquivoSQL){
    char *errorMsg = NULL;
    std::string caminhoCompleto(CAMINHO_BD_PADRAO+this->nomeBD);

    this->codigoRetorno = sqlite3_open(caminhoCompleto.c_str(), &this->db);

    if (this->codigoRetorno != SQLITE_OK){
        std::cerr << "DEU RUIM AO ABRIR " << this->nomeBD << " PATRAO" << std::endl;
        return false;
    }

    this->codigoRetorno = sqlite3_exec(db, "PRAGMA foreign_keys = ON;", NULL, NULL, NULL);

    if (this->codigoRetorno != SQLITE_OK){
        std::cerr << "DEU RUIM NA HORA DE EXECUTAR ARGUMENTO" << std::endl;
        std::cerr << "ERRO COD: " << this->codigoRetorno << std::endl;
        std::cerr << "ERRO MSG: " << errorMsg << std::endl;
        return false;
    }

    this->setQueries(nomeArquivoSQL);

    for (auto iterador = queries->begin(); iterador != queries->end(); ++iterador){
        this->codigoRetorno = sqlite3_exec(db, (*iterador).c_str(), NULL, NULL, &errorMsg);
        if (this->codigoRetorno != SQLITE_OK){
            std::cerr << "DEU RUIM NA HORA DE EXECUTAR" << std::endl;
            std::cerr << "ERRO COD: " << this->codigoRetorno << std::endl;
            std::cerr << "ERRO MSG: " << errorMsg << std::endl;
            sqlite3_free(errorMsg);
            return false;
        }
    }

    sqlite3_close_v2(db);
    
    return true;
}