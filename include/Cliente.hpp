#ifndef CLIENTE_HPP
#define CLIENTE_HPP
#include <string>
#include "SqliteHandler.hpp"
#include "MessageHandler.hpp"

class Cliente{
    std::string nome;

    public:
    virtual std::string getNome();
    virtual void setNome(std::string& nome);

    protected:
    SqliteHandler *controladorSQL = nullptr;

    virtual void setSqliteHandler(SqliteHandler *controladorSQL);
    virtual bool SqliteHandlerIsNull();
    virtual void criar();
    virtual void salvar();

    //buscar por nome por default
    void buscar(std::string&);

    Cliente(SqliteHandler *controladorSQL);
    Cliente(SqliteHandler *controladorSQL, std::string& nome);
};

#endif