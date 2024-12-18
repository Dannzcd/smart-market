#include <iostream>
#include "Funcionario.hpp"
#include <sqlite3.h>
#include "SqliteHandler.hpp"
#include "MessageHandler.hpp"

int main(int argc, char *argv[]){
    Funcionario v;
    SqliteHandler sqlh;
    //bool resultado;

    v.setSalarioBruto(45.43);

    for (auto tabela: TABELAS){
        std::cout << "Criando tabela " << (*tabela) << std::endl;
        sqlh.executarOperacao(Operacao::CRIAR_TABELA, *tabela, "");    
    }

    MessageHandler::MostrarErro("Erro ao abrir a base de dados (TESTE)");

    std::cout << v.getSalarioBruto() << std::endl;
}
