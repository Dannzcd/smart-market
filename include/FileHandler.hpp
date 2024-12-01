#ifndef CALLFILES_HPP
#define CALLFILES_HPP
#include <string>

class FileHandler{
    std::string tipoArquivo;
    
    public:
    
    virtual std::string getTipoArquivo();
    virtual void setTipoArquivo(std::string& tipoArquivo);
};

#endif