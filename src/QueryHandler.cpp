#include "QueryHandler.hpp"
#include "MessageHandler.hpp"
#include "SqliteHandler.hpp"

/* std::string* QueryHandler::carregarQueryUnica(std::string* caminhoArquivoSQL){

} */

std::vector<std::string>* QueryHandler::carregarConjuntoQueries(std::string *caminhoArquivoSQL){
    std::ifstream arquivoSql;
    std::string linha;
    std::string query;
    std::vector<std::string> *queries = new std::vector<std::string>;
    unsigned queriesEncontradas = 0;

    arquivoSql.open(caminhoArquivoSQL->c_str());

    if (arquivoSql.fail()){
        //jogar excecao
        arquivoSql.close();
        throw std::runtime_error("Erro ao abrir o arquivo SQL\nArquivo não existe ou está corrompido");
    }

    queries->reserve(QUANTIDADE_MINIMA_QUERIES);

    while (std::getline(arquivoSql, linha)){
        if (!linha.empty() && (linha.find_first_not_of(" \t") != std::string::npos)){
            query += linha;
            if (query.find(';') != std::string::npos){
                ++queriesEncontradas;
                queries->push_back(query);
                query = "";
            }
        }
    }

    std::cout << "Queries encontradas: " << queriesEncontradas << std::endl;

    arquivoSql.close();
    return queries;
}

std::string* QueryHandler::carregarQueryUnica(std::string *caminhoArquivoSQL){
    std::ifstream arquivoSQL;
    std::string linha;
    std::string *query = new std::string;

    //o caminho vem pela main
    arquivoSQL.open(caminhoArquivoSQL->c_str());

    if (arquivoSQL.fail()){
        arquivoSQL.close();
        throw std::runtime_error("Erro ao abrir o arquivo SQL\nArquivo não existe ou está corrompido");
    }

    while (std::getline(arquivoSQL, linha)){
        (*query) += linha;
    }

    return query;
}