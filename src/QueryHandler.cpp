#include "QueryHandler.hpp"
#include "MessageHandler.hpp"
#include "SqliteHandler.hpp"

std::vector<std::string> *QueryHandler::carregarQueriesDeSetup(std::string *nomeArquivo){
    std::ifstream arquivoSql;
    std::string linha;
    std::string query;
    std::vector<std::string> *queries = new std::vector<std::string>;
    size_t queriesEncontradas = 0;

    arquivoSql.open(nomeArquivo->c_str());

    if (arquivoSql.fail()){
        //jogar excecao
        MessageHandler::MostrarErro("Erro ao abrir o arquivo SQL");
        arquivoSql.close();
        return NULL;
    }

    queries->reserve(20);

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