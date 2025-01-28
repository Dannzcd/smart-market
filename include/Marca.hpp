#ifndef MARCA_HPP
#define MARCA_HPP

#include <string>

class Marca {
private:
    std::string nome;

public:
    Marca();  // Construtor padrão
    Marca(std::string nome);  // Construtor com nome da marca

    std::string getNome();
    void setNome(std::string nome);
};

#endif
