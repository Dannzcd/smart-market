#pragma once

#include <iostream>
#include <string>
#include <stdexcept>
#include <string.h>
#include <cstdlib>
#include "SqliteHandler.hpp"

class Marca{
    size_t id;
    std::string nome;
    SqliteHandler *controladorSQL;

    static int callbackMarca(void *data, int argc, char **argv, char **col_name);

    public:
    inline static std::vector<Marca> *listaMarcas = nullptr;
    inline static std::string TABELA_MARCA = "MARCAS";

    Marca();
    Marca(std::string nome);
    Marca(std::string* nome);
    Marca(size_t id, std::string nome);

    static void imprimirMarcas();
    static void buscarMarcas(Marca *marca, std::string* argumento);
    static void excluirListaMarcas(std::vector<Marca> *marcas);

    std::string getNome();
    SqliteHandler *getControladorSQL();
    void setNome(const char* nome);
    void setNome(std::string &nome);
    void setNome(std::string *nome);
    void setSqliteHandler(SqliteHandler *controladorSQL);
    void setId(size_t id);
    bool existe();
    void salvar();
    void excluir();
    size_t getId();
    
};