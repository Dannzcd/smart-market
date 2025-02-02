#pragma once

#include <iostream>
#include <string>
#include <stdexcept>
#include <string.h>
#include <cstdlib>
#include <sstream>
#include "SqliteHandler.hpp"

class Marca{
    size_t id;
    std::string nome;
    SqliteHandler *controladorSQL;

    static int empilharMarcas(void *data, int argc, char **argv, char **col_name);

    public:
    inline static std::vector<Marca> listaMarcas; 
    inline static std::string TABELA_MARCA = "MARCAS";

    Marca();
    Marca(std::string nome);
    Marca(std::string* nome);
    Marca(size_t id, std::string nome);

    static void imprimirMarcas();
    static void registrarMarcasPadrao(SqliteHandler* controladorSql);
    //Métodos não prontos
    static void buscarMarcas(Marca *marca, std::string* argumento);
    static void excluirListaMarcas(std::vector<Marca> *marcas);
    //fim métodos não prontos

    std::string getNome();
    SqliteHandler *getControladorSQL();
    void setNome(const char* nome);
    void setNome(std::string &nome);
    void setNome(std::string *nome);
    void setControladorSQL(SqliteHandler *controladorSQL);
    void setId(size_t id);
    bool existe();
    void criar();
    void editar();
    void excluir();
    size_t getId();
    
};