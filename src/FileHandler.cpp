#include "FileHandler.hpp"

std::string FileHandler::getTipoArquivo(){
    return this->tipoArquivo;
}

void FileHandler::setTipoArquivo(std::string& tipoArquivo){
    this->tipoArquivo = tipoArquivo;
}