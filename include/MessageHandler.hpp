#pragma once
#include <string>

class MessageHandler{
    inline static const std::string TextoVermelho = "\033[31m";
    inline static const std::string TextoBranco = "\033[0m";
    inline static const std::string TextoVerde = "\033[32m";
    inline static const std::string TextoAmarelo = "\e[0;33m";

    public:
    static void MostrarErro(std::string mensagemErro);
    static void MostrarMensagemSucesso(std::string mensagemSucesso);
    static void MostrarAviso(std::string mensagemAviso);
};