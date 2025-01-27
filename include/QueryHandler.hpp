#ifndef QUERYHANDLER_HPP
#define QUERYHANDLER_HPP

#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <exception>
#include "Dir.hpp"

class QueryHandler{
public:
    static std::vector<std::string>* carregarConjuntoQueries(std::string *caminhoArquivoSQL);
    static std::string* carregarQueryUnica(std::string *caminhoArquivoSQL);
};

#endif