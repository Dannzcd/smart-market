#include <iostream>
#include "Funcionario.hpp"
#include <sqlite3.h>
#include "SqliteHandler.hpp"
#include "MessageHandler.hpp"

int main(int argc, char *argv[]){
    std::vector <Funcionario*> funcionarios;
    SqliteHandler sqlh;

    for (auto tabela: TABELAS){
        std::cout << "Criando tabela " << (*tabela) << std::endl;
        sqlh.executarOperacao(Operacao::CRIAR_TABELA, *tabela, "");    
    }
}
