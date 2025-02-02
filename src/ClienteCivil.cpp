#include "ClienteCivil.hpp"

ClienteCivil::ClienteCivil(SqliteHandler *controladorSQL):Cliente(controladorSQL){

}

ClienteCivil::ClienteCivil(SqliteHandler *controladorSQL, std::string& nome):Cliente(controladorSQL, nome){
    
}

void ClienteCivil::criar() {
    std::string queryCliente = "INSERT INTO CLIENTES (nome) VALUES ?;";
    std::string queryClienteCivil = "INSERT INTO CLIENTES_CIVIL (id_cliente, cpf) VALUES (?, ?);";

    

    //this->controladorSQL->
}

void ClienteCivil::salvar(){
    
}

int ClienteCivil::callbackClienteCivil(void *data, int argc, char **argv, char **col_name){
    std::vector<std::string> nomes(argc);

    for (int i = 0; i < argc; i++){
        nomes[i] = argv[i];
    }

    for (auto& nome: nomes){
        std::cout << nome << std::endl;
    }

    return 0;
}

void ClienteCivil::buscar(){
    this->controladorSQL->executarOperacao(Operacao::CAPTURAR_LINHAS, this->callbackClienteCivil, "CLIENTES", "nome", nullptr);

}