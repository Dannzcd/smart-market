#include <iostream>
#include <sqlite3.h>
#include <fstream>
#include <pthread.h>
#include <unistd.h>
#include <iomanip>
#include "Funcionario.hpp"
#include "SqliteHandler.hpp"
#include "MessageHandler.hpp"
#include "QueryHandler.hpp"

void *routine(void *variavel){
    std::cout << "Vou dormir por 5 segundos" << std::endl;
    sleep(5);
    std::cout << "Acordei!" << std::endl;

    return NULL;
}

int main(int argc, char *argv[]){
    //std::vector <Funcionario> *funcionarios;
    //std::vector<std::string> *queries;
    SqliteHandler controladorSqlite;
    std::string arquivoSetupSQL = "../../sql_scripts/setup/criarTabelas.sql";
    
    std::string linha;
    std::ifstream arquivoSQL;
    //pthread_t threadQuery;

    controladorSqlite.criarBaseDados();
    controladorSqlite.executarOperacao(Operacao::CRIAR_TABELAS, arquivoSetupSQL);

    /* queries = QueryHandler::carregarQueriesDeSetup(&arquivoSetupSQL);

    std::cout << "Tamanho do vetor de queries: " << queries->size() << std::endl; */

    /* for (auto iterador = queries->begin(); iterador != queries->end(); ++iterador){
        std::cout << (*iterador) << std::endl;
    } */

    /* arquivoSQL.open(arquivoSetupSQL);
    while (std::getline(arquivoSQL, linha)) std::cout << linha << std::endl; */

    return 0;
}
