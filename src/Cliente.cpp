#include "Cliente.hpp"

Cliente::Cliente(SqliteHandler *controladorSQL){
    this->controladorSQL = controladorSQL;
}

Cliente::Cliente(SqliteHandler *controladorSQL, std::string& nome){
    this->controladorSQL = controladorSQL;
    this->nome = nome;
}

void Cliente::criar(){

}

void Cliente::salvar(){
    
}

std::string Cliente::getNome(){
    return this->nome;
}

void Cliente::setNome(std::string& nome){
    this->nome = nome;
}

bool Cliente::SqliteHandlerIsNull(){
    return controladorSQL == nullptr || controladorSQL == NULL;
}

void Cliente::setSqliteHandler(SqliteHandler *controladorSQL){
    this->controladorSQL = controladorSQL;
}