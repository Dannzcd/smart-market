#ifndef SQLITEHANDLER_HPP
#define SQLITEHANDLER_HPP
#include "FileHandler.hpp"
#include "MessageHandler.hpp"
#include "QueryHandler.hpp"
#include "Dir.hpp"
#include <string>
#include <sqlite3.h>
#include <vector>
#include <array>
#include <string>
#include <exception>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <iomanip>

#define NOME_ARQUIVO_BD_PADRAO "dados.sqlite3"
#define CAMINHO_BD_PADRAO "../db/"
#define QUANTIDADE_MINIMA_QUERIES 10

enum class Operacao{
    CRIAR_BASE_DADOS=1,
    CRIAR_TABELAS,
    INSERIR_LINHA,
    EDITAR_LINHA,
    EXCLUIR_LINHA,
    CAPTURAR_LINHAS
};

class SqliteHandler : FileHandler{
    sqlite3 *db;
    sqlite3_stmt *queryFormatada; //query pré compilada formatada, substituindo os '?' no script
    int codigoRetorno;
    std::string nomeBD;
    std::vector<std::string> *queries;

    bool dbExiste();
    void criarTabelas(std::runtime_error *erro);
    void criarBaseDados(std::runtime_error *erro);

    void inserirLinha(std::runtime_error *erro, std::string caminhoQuery);

    void excluirLinha(std::runtime_error *erro, std::string caminhoQuery);
    void editarLinha(std::runtime_error *erro);

    public:
    SqliteHandler();
    void setNomeBD(std::string& novoNome);
    std::vector<std::string> *getQueries();
    void setQueries(std::string nomeArquivo);
    void setQueries(std::string *nomeArquivoSQL);

    //metodo generico
    void executarOperacao(Operacao operacao);

    void executarOperacao(Operacao operacao, std::string &caminhoQuery);
};

#endif