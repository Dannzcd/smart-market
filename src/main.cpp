#include <iostream>
#include "Funcionario.hpp"
#include <sqlite3.h>
#include "SqliteHandler.hpp"

int main(int argc, char *argv[]){
    Funcionario v;
    SqliteHandler sqlh;

    v.setSalarioBruto(45.43);

    sqlite3 *db;
    int rc;

    rc = sqlite3_open("../db/vasco.db", &db);

    if (rc){
        std::cout << "Nao foi possivel abrir o banco de dados!" << std::endl;
        return 0;
    }
    
    else{
        std::cout << "Base de dados aberta com sucesso!" << std::endl;
    }

    sqlh.executarOperacao(Operacao::EDITAR, "TABELA1", "a");

    std::cout << v.getSalarioBruto() << std::endl;
    sqlite3_close_v2(db);
}
