#include "QueryHandler.hpp"
#include "MessageHandler.hpp"
#include "SqliteHandler.hpp"

/* std::string* QueryHandler::carregarQueryUnica(std::string* caminhoArquivoSQL){

} */

std::vector<std::string> *QueryHandler::carregarConjuntoQueries(std::string *caminhoArquivoSQL){
    std::ifstream arquivoSql;
    std::string linha;
    std::string query;
    std::vector<std::string> *queries = new std::vector<std::string>;
    std::runtime_error *erro = nullptr;
    unsigned queriesEncontradas = 0;

    arquivoSql.open(caminhoArquivoSQL->c_str());

    //std::cout << caminhoArquivoSQL->c_str() << std::endl;

    if (arquivoSql.fail()){
        //jogar excecao
        arquivoSql.close();
        erro = new std::runtime_error("Erro ao abrir o arquivo SQL\nArquivo não existe ou está corrompido");
        throw erro;
    }

    queries->reserve(QUANTIDADE_MINIMA_QUERIES);

    while (std::getline(arquivoSql, linha)){
        if (!linha.empty() && (linha.find_first_not_of(" \t") != std::string::npos)){
            query += linha;

            if (query.find(';') != std::string::npos){
                //std::cout << "Empilhando query " << query << "\n" << std::endl;
                ++queriesEncontradas;
                queries->push_back(query);
                query = "";
                //std::cout << "QUERY NOVA:" << "\n" << std::endl;
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
    std::runtime_error *erro = nullptr;

    //o caminho vem pela main
    arquivoSQL.open(caminhoArquivoSQL->c_str());

    if (arquivoSQL.fail()){
        arquivoSQL.close();
        erro = new std::runtime_error("Erro ao abrir o arquivo SQL\nArquivo não existe ou está corrompido");
        throw erro;
    }

    while (std::getline(arquivoSQL, linha)){
        (*query) += linha;
    }

    //std::cout << query->c_str() << std::endl;
    return query;
}