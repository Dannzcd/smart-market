#include "MessageHandler.hpp"
#include <iostream>

void MessageHandler::MostrarErro(std::string mensagemErro){
    std::cerr << MessageHandler::vermelho << "[erro]: " << mensagemErro << MessageHandler::branco << std::endl;
}