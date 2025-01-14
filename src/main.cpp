#include <iostream>
#include <sqlite3.h>
#include <fstream>
#include <pthread.h>
#include <unistd.h>
#include <filesystem>
#include "SqliteHandler.hpp"
#include "MessageHandler.hpp"
#include "Dir.hpp"
#include "Funcionario.hpp"

void *routine(void *variavel){
    std::cout << "Vou dormir por 5 segundos" << std::endl;
    sleep(5);
    std::cout << "Acordei!" << std::endl;

    return nullptr;
}

int main(int argc, char *argv[]){
    std::string caminho = Dir::combinarCaminhos(CAMINHO_FUNCIONARIOS, CAMINHO_SET_COMUM, INSERIR_FUNCIONARIO);
    //Funcionario f1("daniel", "123.231.212-32");
    //f1.setSalarioBruto(7021.29);

    try{
        SqliteHandler controladorSqlite;
        //smart-market/sql_scripts/funcionarios/set/inserir_funcionario.sql
        std::cout << caminho << std::endl;
        controladorSqlite.executarOperacao(Operacao::INSERIR_LINHA, caminho);
    }

    catch(std::runtime_error *erro){
        MessageHandler::MostrarErro(erro->what());
        delete erro;
    }

    sleep(300);

    return 0;
}
