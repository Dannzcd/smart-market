#include "Dir.hpp"
#include <iostream>

std::string Dir::combinarCaminhos(const char *primeiraCamada, const char *segundaCamada){
    return std::string(CAMINHO_ARQUIVOS_SQL)+primeiraCamada+segundaCamada;
}

std::string Dir::combinarCaminhos(const char *primeiraCamada, const char *segundaCamada, const char *terceiraCamada){
    return std::string(CAMINHO_ARQUIVOS_SQL)+primeiraCamada+segundaCamada+terceiraCamada;
}