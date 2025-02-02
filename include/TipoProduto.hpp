#pragma once

#include <string>
#include "SqliteHandler.hpp"


class TipoProduto{
    size_t id;
    std::string nome;
    SqliteHandler *controladorSQL;
public:
    size_t getId();
    std::string getNome();
    SqliteHandler *getControladorSQL();
    

    void setId(size_t id);
    void setNome(std::string nome);
    void setControladorSQL(SqliteHandler *controladorSQL);
};
