#ifndef QUERYHANDLER_HPP
#define QUERYHANDLER_HPP

#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <exception>
#include "Dir.hpp"

//

//caminhos

class QueryHandler{
public:
    static std::vector<std::string>* carregarConjuntoQueries(std::string *caminhoArquivoSQL);
    static std::string* carregarQueryUnica(std::string *caminhoArquivoSQL);
    //static unsigned contarQueries(std::string *nomeArquivo);
};

#endif