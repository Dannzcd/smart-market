#ifndef PRODUTO_HPP
#define PRODUTO_HPP

#include <string>
#include "Marca.hpp"
#include "SqliteHandler.hpp"

class Produto {
private:
    size_t id;
    std::string nome;
    double pesoLiquido;
    double precoUnitario;
    unsigned unidadesDisponiveis;
    Marca* marca;
    int idTipo;
    SqliteHandler* controladorSQL;

public:
    Produto();
    Produto(std::string nome, Marca* marca, double pesoLiquido, double precoUnitario, int idTipo);
    Produto(size_t id, std::string nome, Marca* marca, double pesoLiquido, double precoUnitario, unsigned unidadesDisponiveis, int idTipo);

    size_t getId();
    std::string getNome() const;
    void setNome(std::string nome);

    double getPesoLiquido() const;
    void setPesoLiquido(double pesoLiquido);

    double getPrecoUnitario() const;
    void setPrecoUnitario(double precoUnitario);

    unsigned getUnidadesDisponiveis() const;
    void setUnidadesDisponiveis(unsigned unidades);

    Marca* getMarca() const;
    void setMarca(Marca* marca);

    int getIdTipo() const;
    void setIdTipo(int idTipo);

    bool disponivel() const;
    void adicionarUnidades(unsigned quantidade);

    void setSqliteHandler(SqliteHandler *controladorSQL);

    void criar();
    void editar();
    void excluir();
};

#endif // PRODUTO_HPP
