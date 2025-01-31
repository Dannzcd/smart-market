#ifndef ERRORHANDLER_HPP
#define ERRORHANDLER_HPP
#include <string>

class MessageHandler{
    inline static const std::string TextoVermelho = "\033[31m";
    inline static const std::string TextoBranco = "\033[0m";
    inline static const std::string TextoVerde = "\033[32m";

    public:
    static void MostrarErro(std::string mensagemErro);
    static void MostrarMensagemSucesso(std::string mensagemSucesso);
};

#endif