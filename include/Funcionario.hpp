#ifndef FUNCIONARIO_HPP
#define FUNCIONARIO_HPP
#include <string>

class Funcionario{
    std::string nome;
    std::string cpf;
    double salarioBruto;
    double salarioLiquido;

    public:
    void setSalarioBruto(double salario);
    double getSalarioBruto();
};

#endif