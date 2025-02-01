#include "SqliteHandler.hpp"

SqliteHandler::SqliteHandler(){  
    this->nomeBD = NOME_ARQUIVO_BD_PADRAO;
    try{
        this->caminhoCompletoBaseDeDados = CAMINHO_BD_PADRAO+this->nomeBD;
        this->executarOperacao(Operacao::CRIAR_BASE_DADOS);
        this->executarOperacao(Operacao::CRIAR_TABELAS);
    } catch(std::runtime_error& erro){
        MessageHandler::MostrarErro(erro.what());
    }
    
}

void SqliteHandler::setQueries(std::string *nomeArquivoSQL){
    this->queries = QueryHandler::carregarConjuntoQueries(nomeArquivoSQL);
}

void SqliteHandler::setQueries(std::string nomeArquivoSQL){
    this->queries = QueryHandler::carregarConjuntoQueries(&nomeArquivoSQL);
}

std::vector<std::string>* SqliteHandler::getQueries(){
    return this->queries;
}

void SqliteHandler::setNomeBD(std::string& novoNome){
    this->nomeBD = novoNome;
}

//Só pode ser chamado depois do construtor
bool SqliteHandler::dbExiste(){
    return std::filesystem::exists((CAMINHO_BD_PADRAO+this->nomeBD).c_str());
}

void SqliteHandler::executarOperacao(Operacao operacao){
    switch (operacao) {
        case Operacao::CRIAR_BASE_DADOS:
            criarBaseDados();
            break;

        case Operacao::CRIAR_TABELAS:
            criarTabelas();
            break;

        default:
            throw std::runtime_error("COMANDO INVÁLIDO"); // Operação inválida
    }
}

void SqliteHandler::executarOperacao(Operacao operacao, int (*callback)(void *, int, char **, char **), const char* tabela, std::string campos, std::string* argumentos){
    if (tabela == nullptr) throw std::runtime_error("TABELA INEXISTENTE");
    
    switch (operacao) {
        case Operacao::INSERIR_LINHA:
            inserirLinha(tabela, campos, argumentos);
            break;

        case Operacao::EXCLUIR_LINHA:
            excluirLinha(tabela, argumentos);
            break;

        case Operacao::CAPTURAR_LINHAS:
            capturarLinhas(callback, tabela, campos, nullptr);
            break;

        default:
            throw std::runtime_error("COMANDO INVÁLIDO"); // Operação inválida
    }
}

void SqliteHandler::criarBaseDados(){
    if (this->dbExiste()) return;

    this->codigoRetorno = sqlite3_open(this->caminhoCompletoBaseDeDados.c_str(), &this->db);   

    if (this->codigoRetorno != SQLITE_OK){
        throw std::runtime_error("Erro ao criar a base de dados! Codigo de erro: " + this->codigoRetorno);
    }
    
    sqlite3_close_v2(db);
}

void SqliteHandler::criarTabelas(){
    char *errorMsg = nullptr;
    std::string caminhoCompletoArquivoSQLdeSetup = Dir::combinarCaminhos(CAMINHO_SETUP, ARQUIVO_CRIAR_TABELAS);

    this->codigoRetorno = sqlite3_open(this->caminhoCompletoBaseDeDados.c_str(), &this->db);

    if (this->codigoRetorno != SQLITE_OK){
        throw std::runtime_error("Erro ao abrir a base de dados");
    }

    this->codigoRetorno = sqlite3_exec(db, "PRAGMA foreign_keys = ON;", NULL, NULL, NULL);

    if (this->codigoRetorno != SQLITE_OK){
        throw std::runtime_error("Erro ao abrir a base de dados");
    }

    this->setQueries(&caminhoCompletoArquivoSQLdeSetup);

    for (auto iterador = queries->begin(); iterador != queries->end(); ++iterador){
        this->codigoRetorno = sqlite3_exec(db, (*iterador).c_str(), NULL, NULL, &errorMsg);
        if (this->codigoRetorno != SQLITE_OK){
            std::cout << errorMsg << std::endl;
            sqlite3_free(errorMsg);
            throw std::runtime_error("Erro ao executar a query");;
        }
    }

    std::cout << caminhoCompletoArquivoSQLdeSetup << std::endl;
    delete this->queries;
    sqlite3_close_v2(db);
}

// insere argumentos (dado1, dado2, ..., dadon) dentro da tabela
void SqliteHandler::inserirLinha(const char* tabela, std::string campos, std::string* argumentos){
    if (argumentos == nullptr) throw std::runtime_error("Não é possível inserir sem argumentos");
    
    this->codigoRetorno = sqlite3_open(this->caminhoCompletoBaseDeDados.c_str(), &this->db);

    if (this->codigoRetorno != SQLITE_OK){
        throw std::runtime_error("Erro ao abrir a base de dados");
    }
    
    std::string query = std::string("INSERT OR REPLACE INTO ") +
        tabela + " (" + campos + ") VALUES " +
        (*argumentos) + ';';

    std::cout << query << std::endl;
    
    if (this->codigoRetorno != SQLITE_OK){
        throw std::runtime_error("Erro ao executar a query");
    }

    this->codigoRetorno = sqlite3_exec(this->db, query.c_str(), nullptr, nullptr, nullptr);

    sqlite3_close_v2(this->db);
}

void SqliteHandler::capturarLinhas(int (*callback)(void *, int, char **, char **), const char *tabela, std::string& campos, std::string* argumentos){
    bool argumentoEhNulo = (argumentos == nullptr || argumentos == NULL);
    bool achou = false;
    this->codigoRetorno = sqlite3_open(this->caminhoCompletoBaseDeDados.c_str(), &this->db);
    char **mensagemErro = nullptr;
    std::string query;
    std::string aviso = std::string("Objeto do tipo \"") + tabela + "\" não foi encontrado";

    std::cout << query << std::endl;

    //SELECT nome FROM Clientes;
    if (this->codigoRetorno != SQLITE_OK){
        throw std::runtime_error("Erro ao abrir a base de dados");
    }

    if (argumentoEhNulo){
        query = "SELECT " + campos + " FROM " + tabela + ';';
        std::cout << query << std::endl;
    }

    else{
        query = "SELECT " + campos + " FROM " + tabela +
        (*argumentos) + ';';
    }

    this->codigoRetorno = sqlite3_exec(this->db, query.c_str(), callback, &achou, mensagemErro);

    if (this->codigoRetorno != SQLITE_OK) throw std::runtime_error("Não foi possível executar a query");

    sqlite3_close_v2(this->db);

    if (!achou){
        throw aviso;
    }
}

void SqliteHandler::excluirLinha(const char* tabela, std::string* argumentos){
    std::string query = "DELETE FROM " + std::string(tabela) + ' ' + (*argumentos) + ";";
    std::cout << query << std::endl;

    this->codigoRetorno = sqlite3_open(this->caminhoCompletoBaseDeDados.c_str(), &this->db);

    if (this->codigoRetorno != SQLITE_OK){
        throw std::runtime_error("Erro ao abrir a base de dados");
    }

    this->codigoRetorno = sqlite3_exec(
        this->db,
        query.c_str(),
        nullptr,
        nullptr,
        nullptr
    );

    if (this->codigoRetorno != SQLITE_OK){
        throw std::runtime_error("NÃO FOI POSSÍVEL EXECUTAR A EXCLUSÃO DE OBJETO");
    }

    if (sqlite3_changes(this->db) == 0){
        throw std::string("Não é possível excluir um objeto inexistente!");
    }

    sqlite3_close_v2(this->db);
}