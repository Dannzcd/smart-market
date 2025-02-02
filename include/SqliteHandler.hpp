#pragma once

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
    std::string caminhoCompletoBaseDeDados;
    std::vector<std::string> *queries;

    bool dbExiste();
    void criarTabelas();
    void criarBaseDados();

    void inserirLinha(const char* tabela, std::string campos, std::string* argumentos);
    void excluirLinha(const char* tabela, std::string* argumentos);
    void editarLinha(const char* tabela, std::string campos, std::string* argumentos);
    void capturarLinhas(int (*callback)(void *, int, char **, char **), const char *tabela, std::string& campos, std::string* argumentos);

    public:
    inline static size_t NAO_ESTA_NO_BANCO = -1;

    sqlite3 *getDb();
    SqliteHandler();
    void setNomeBD(std::string& novoNome);
    std::vector<std::string> *getQueries();
    void setQueries(std::string nomeArquivo);
    void setQueries(std::string *nomeArquivoSQL);

    void liberarMemoriaCallback(void *data, int argc, char **argv, char **col_name);

    //metodo generico
    void executarOperacao(Operacao operacao);
    void executarOperacao(Operacao operacao, int (*callback)(void *, int, char **, char **), const char* tabela, std::string campos, std::string* argumentos);
};