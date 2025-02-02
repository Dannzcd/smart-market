#pragma once

#include <string>
#include <stdexcept>
#include "Marca.hpp"
#include "SqliteHandler.hpp"

class Produto{
    size_t id;
    std::string nome;
    double pesoLiquido;
    double preco;
    unsigned unidadesDisponiveis;
    Marca *marca;
    SqliteHandler *controladorSQL;
    inline static std::vector<Produto> listaProdutos;

    public:
    Produto();
    Produto(std::string nome, Marca *marca, double pesoLiquido, double preco, SqliteHandler *controladorSQL);

    inline static std::string TABELA_PRODUTO = "PRODUTOS";
    static int preencherListaProdutos(void *data, int argc, char **argv, char **col_name);
    static void buscarTodosOsProdutos(SqliteHandler *controladorSQL);
    static void imprimirListaProdutos();

    std::string getNome();
    Marca *getMarca();
    double getPesoLiquido();
    double getPreco();
    bool disponivel();
    unsigned getUnidadesDisponiveis();
    SqliteHandler *getControladorSQL();
    size_t getId();

    void setUnidadesDisponiveis(unsigned unidades);
    void setNome(std::string nome);
    void setMarca(Marca *marca);
    void setPesoLiquido(double pesoLiquido);
    void atualizarQuantidade(int quantidade);
    void setControladorSQL(SqliteHandler *controlador);
    void setPreco(double preco);
    void criar();
    void editar();
    void excluir();
    void setId(size_t id);

};