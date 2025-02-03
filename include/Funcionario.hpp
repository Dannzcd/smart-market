#ifndef FUNCIONARIO_HPP
#define FUNCIONARIO_HPP

#include <string>

class Funcionario {
private:
    std::string nome;
    std::string sobrenome;
    std::string cpf;
    double salarioBruto;
    double salarioLiquido;

public:
    // Construtor padrão
    Funcionario();

    // Construtor com parâmetros
    Funcionario(std::string nome, std::string sobrenome, std::string cpf, double salarioBruto);

    // Métodos setters
    void setNome(std::string nome);
    void setSobrenome(std::string sobrenome);
    void setCpf(std::string cpf);
    void setSalarioBruto(double salarioBruto);
    void setSalarioLiquido(double salarioLiquido);

    // Métodos getters
    std::string getNome() const;
    std::string getSobrenome() const;
    std::string getCpf() const;
    double getSalarioBruto() const;
    double getSalarioLiquido() const;
};

#endif
