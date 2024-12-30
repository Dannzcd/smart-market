#ifndef SQLITEHANDLER_HPP
#define SQLITEHANDLER_HPP
#include "FileHandler.hpp"
#include <string>
#include <sqlite3.h>
#include <vector>
#include <array>
#include <string>

#define NOME_ARQUIVO_BD_PADRAO "dados.sqlite3"
#define CAMINHO_BD_PADRAO "../db/"
#define CAMINHO_SCRIPT_PADRAO "../sql_scripts/"

enum class Operacao{
    CRIAR_BASE_DADOS=1,
    CRIAR_TABELAS,
    ALTERAR_LINHA,
    EDITAR_LINHA,
    EXCLUIR_LINHA
};

class SqliteHandler : FileHandler{
    sqlite3 *db;
    int codigoRetorno;
    std::string nomeBD;
    std::vector<std::string> *queries;

    bool dbExiste();
    bool criarTabelas(const std::string& nomeArquivoSQL);

    public:
    SqliteHandler();
    void setNomeBD(std::string& novoNome);
    bool criarBaseDados();
    std::vector<std::string> *getQueries();
    void setQueries(std::string nomeArquivo);

    //metodo generico
    bool executarOperacao(Operacao operacao, const std::string nomeArquivoSQL);
};

#endif