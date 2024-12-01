#include <iostream>
#include "Funcionario.hpp"
#include <sqlite3.h>
#include "SqliteHandler.hpp"

int main(int argc, char *argv[]){
    Funcionario v;
    SqliteHandler sqlh;
    bool resultado;

    v.setSalarioBruto(45.43);

    /* if (!sqlh.criarBaseDados()){
        std::cerr << "Erro ao criar a base de dados!" << std::endl;
        return -1;
    } */

    resultado = sqlh.executarOperacao(Operacao::CRIAR_TABELA, "", "");
    std::cout << resultado << std::endl;

    std::cout << v.getSalarioBruto() << std::endl;
}
