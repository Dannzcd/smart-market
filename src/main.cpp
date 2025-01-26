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
#include "ClienteCivil.hpp"

void *routine(void *variavel){
    std::cout << "Vou dormir por 5 segundos" << std::endl;
    sleep(5);
    std::cout << "Acordei!" << std::endl;

    return nullptr;
}

int main(int argc, char *argv[]){
    //sem dinamicidade, não tem tempo de implementar
    //std::string caminho = Dir::combinarCaminhos(CAMINHO_FUNCIONARIOS, CAMINHO_SET_COMUM, INSERIR_FUNCIONARIO);

    std::string nome("pinto");

    try{
        SqliteHandler controladorSqlite;
        ClienteCivil c(&controladorSqlite);
        c.setNome(nome);
        c.buscar();
    }

    catch(std::runtime_error& erro){
        MessageHandler::MostrarErro(erro.what());
    }

    sleep(300);

    return 0;
}
