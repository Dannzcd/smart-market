#ifndef PRODUTO_HPP
#define PRODUTO_HPP

#include <string>
#include "Marca.hpp"

class Produto {
private:
    std::string nome;
    double pesoLiquido;
    double preco;
    unsigned unidadesDisponiveis;
    Marca* marca;

public:
    Produto();
    Produto(std::string nome, Marca* marca, double pesoLiquido, double preco);
    Produto(std::string nome, double pesoLiquido, double preco);

    std::string getNome() const;
    void setNome(std::string nome);

    double getPesoLiquido() const;
    void setPesoLiquido(double pesoLiquido);

    double getPreco() const;
    void setPreco(double preco);

    unsigned getUnidadesDisponiveis() const;
    void setUnidadesDisponiveis(unsigned unidades);

    Marca* getMarca() const;
    void setMarca(Marca* marca);

    bool disponivel() const;
    void adicionarUnidades(unsigned quantidade);
};

#endif
