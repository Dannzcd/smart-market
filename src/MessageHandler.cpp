#include "MessageHandler.hpp"
#include <iostream>

void MessageHandler::MostrarErro(std::string mensagemErro){
    std::cerr << MessageHandler::TextoVermelho << "[erro]: " << mensagemErro << MessageHandler::TextoBranco << std::endl;
}

void MessageHandler::MostrarAviso(std::string mensagemAviso){
    std::cout << MessageHandler::TextoAmarelo << "[aviso]: " << mensagemAviso << MessageHandler::TextoBranco << std::endl;
}

void MessageHandler::MostrarMensagemSucesso(std::string mensagemSucesso){
    std::cout << MessageHandler::TextoVerde << "[sucesso]: " << mensagemSucesso << MessageHandler::TextoBranco << std::endl;
}