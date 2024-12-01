#ifndef FUNCIONARIO_HPP
#define FUNCIONARIO_HPP
#include <string>

class Funcionario{
    std::string nome;
    std::string cpf;
    double salarioBruto;
    double salarioLiquido;

    public:
    void setSalarioBruto(double salarioBruto);
    void setSalarioLiquido(double salarioLiquido);
    void setCpf(std::string cpf);
    void setNome(std::string nome);
    
    Funcionario();
    Funcionario(std::string nome, std::string cpf);
    Funcionario(std::string nome, std::string cpf, double salarioBruto);

    double getSalarioBruto();
};

#endif