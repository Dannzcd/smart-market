#ifndef CLIENTE_HPP
#define CLIENTE_HPP
#include <ctime>
#include <string>

class Cliente{
    std::string nome;
    double tarifaTotal;
    time_t dataDeEntrada;
    time_t dataDeSaida;

    public:
    virtual double getTarifaTotal();
    virtual void setTarifaTotal(double tarifaTotal);
    virtual unsigned getHorasGastas();
};

#endif