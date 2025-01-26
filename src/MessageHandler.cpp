#include "MessageHandler.hpp"
#include <iostream>

void MessageHandler::MostrarErro(std::string mensagemErro){
    std::cerr << MessageHandler::TextoVermelho << "[erro]: " << mensagemErro << MessageHandler::TextoBranco << std::endl;
}