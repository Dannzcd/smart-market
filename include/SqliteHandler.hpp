#ifndef SQLITEHANDLER_HPP
#define SQLITEHANDLER_HPP
#include "FileHandler.hpp"
#include <string>
#include <sqlite3.h>

enum class Operacao{
    CRIAR=1,
    ALTERAR,
    EDITAR,
    EXCLUIR
};

class SqliteHandler : FileHandler{
    sqlite3 *db;
    
    bool alterarTabela(const std::string& tabela, const std::string& parametro);
    bool editarTabela(const std::string& tabela, const std::string& parametro);
    bool excluirTabela(const std::string& tabela, const std::string& parametro);

    public: 
    //metodo generico
    bool executarOperacao(Operacao operacao, const std::string& tabela, const std::string& parametro);
};

#endif