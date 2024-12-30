#ifndef QUERYHANDLER_HPP
#define QUERYHANDLER_HPP

#include <fstream>
#include <string>
#include <iostream>
#include <vector>

class QueryHandler{
public:
    static std::vector<std::string>* carregarQueriesDeSetup(std::string *nomeArquivo);
    static unsigned contarQueries(std::string *nomeArquivo);
};

#endif