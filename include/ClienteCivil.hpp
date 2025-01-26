#ifndef CLIENTECIVIL_HPP
#define CLIENTECIVIL_HPP
#include "Cliente.hpp"

class ClienteCivil: public Cliente{
    std::string cpf;

    public:
    ClienteCivil(SqliteHandler *controladorSQL);
    ClienteCivil(SqliteHandler *controladorSQL, std::string& nome);

    void criar() override;
    void salvar() override;

    std::string getCpf();

    void buscar();
    static int callbackClienteCivil(void *data, int argc, char **argv, char **col_name);

};

#endif