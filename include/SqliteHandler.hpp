#ifndef SQLITEHANDLER_HPP
#define SQLITEHANDLER_HPP
#include "FileHandler.hpp"
#include <string>
#include <sqlite3.h>
#include <vector>
#include <string>

#define NOME_ARQUIVO_BD "dados.db"

const std::string TABELA_FUNCIONARIO = "CREATE TABLE IF NOT EXISTS FUNCIONARIOS("
    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
    "nome TEXT NOT NULL, "
    "cpf TEXT NOT NULL UNIQUE, "
    "salarioBruto FLOAT, "
    "salarioLiquido FLOAT);";

enum class Operacao{
    CRIAR_BASE_DADOS=1,
    CRIAR_TABELA,
    ALTERAR_LINHA,
    EDITAR_LINHA,
    EXCLUIR_LINHA
};

class SqliteHandler : FileHandler{
    sqlite3 *db;
    int rc;

    bool criarTabela(const std::string& tabela);
    bool alterarLinha(const std::string& tabela, const std::string& parametro);
    bool editarLinha(const std::string& tabela, const std::string& parametro);
    bool excluirLinha(const std::string& tabela, const std::string& parametro);

    public:
    bool criarBaseDados();

    //metodo generico
    bool executarOperacao(Operacao operacao, const std::string& tabela, const std::string& parametro);
};

#endif