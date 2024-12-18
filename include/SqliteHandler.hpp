#ifndef SQLITEHANDLER_HPP
#define SQLITEHANDLER_HPP
#include "FileHandler.hpp"
#include <string>
#include <sqlite3.h>
#include <vector>
#include <array>
#include <string>

#define NOME_ARQUIVO_BD "dados.sqlite3"
#define NUMERO_TABELAS 5

const std::string TABELA_FUNCIONARIO = "CREATE TABLE IF NOT EXISTS FUNCIONARIOS("
    "id_funcionario INTEGER PRIMARY KEY AUTOINCREMENT, "
    "nome VARCHAR(50) NOT NULL, "
    "cpf VARCHAR(13) NOT NULL UNIQUE, "
    "salario_bruto FLOAT, "
    "salario_liquido FLOAT);";

const std::string TABELA_CLIENTE = "CREATE TABLE IF NOT EXISTS CLIENTES("
    "id_cliente INTEGER PRIMARY KEY AUTOINCREMENT,"
    "nome VARCHAR(50) NOT NULL);";

const std::string TABELA_CLIENTE_CIVIL = "CREATE TABLE IF NOT EXISTS CLIENTES_CIVIL("
    "id_cliente_civil INTEGER PRIMARY KEY AUTOINCREMENT, "
    "id_cliente INTEGER, "
    "FOREIGN KEY (id_cliente) REFERENCES CLIENTES(id_cliente));";

const std::string TABELA_CLIENTE_EMPRESA = "CREATE TABLE IF NOT EXISTS CLIENTES_EMPRESA("
    "id_cliente_empresa INTEGER PRIMARY KEY AUTOINCREMENT, "
    "id_cliente INTEGER, "
    "FOREIGN KEY (id_cliente) REFERENCES CLIENTES(id_cliente));";

const std::string TABELA_ESTACIONAMENTOS = "CREATE TABLE IF NOT EXISTS ESTACIONAMENTOS("
    "id_estacionamento INTEGER PRIMARY KEY AUTOINCREMENT, "
    "cnpj VARCHAR(15) NOT NULL UNIQUE, "
    "faturamento_bruto FLOAT, "
    "total_impostos FLOAT, "
    "faturamento_liquido FLOAT, "
    "lucro FLOAT);";

const std::array<const std::string*, NUMERO_TABELAS> TABELAS {
    &TABELA_FUNCIONARIO, 
    &TABELA_CLIENTE,
    &TABELA_CLIENTE_CIVIL,
    &TABELA_CLIENTE_EMPRESA,
    &TABELA_ESTACIONAMENTOS
};

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

    bool criarTabela(const std::string& nomeTabela);
    bool alterarLinha(const std::string& nomeTabela, const std::string& parametro);
    bool editarLinha(const std::string& nomeTabela, const std::string& parametro);
    bool excluirLinha(const std::string& nomeTabela, const std::string& parametro);

    public:
    bool criarBaseDados();

    //metodo generico
    bool executarOperacao(Operacao operacao, const std::string& nomeTabela, const std::string& parametro);
};

#endif