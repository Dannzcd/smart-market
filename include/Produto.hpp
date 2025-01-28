#ifndef PRODUTO_HPP
#define PRODUTO_HPP

#include <string>
#include "Marca.hpp" // Inclusão da classe Marca

class Produto {
private:
    std::string nome;
    double pesoLiquido;
    double preco;
    unsigned unidadesDisponiveis;
    Marca* marca; // Relacionamento com a classe Marca

public:
    Produto();  // Construtor padrão
    Produto(std::string nome, Marca* marca, double pesoLiquido, double preco);
    Produto(std::string nome, double pesoLiquido, double preco);

    std::string getNome();
    void setNome(std::string nome);

    double getPesoLiquido();
    void setPesoLiquido(double pesoLiquido);

    double getPreco();
    void setPreco(double preco);

    unsigned getUnidadesDisponiveis();
    void setUnidadesDisponiveis(unsigned unidades);

    Marca* getMarca();
    void setMarca(Marca* marca);

    bool disponivel();  // Verifica se o produto está disponível
    void adicionarUnidades(unsigned quantidade);  // Adiciona unidades ao estoque
};

#endif
