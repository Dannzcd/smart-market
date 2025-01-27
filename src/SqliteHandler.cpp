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

void SqliteHandler::executarOperacao(Operacao operacao, int (*callback)(void *, int, char **, char **), std::string* argumentos){
    switch (operacao) {
        case Operacao::INSERIR_LINHA:
            inserirLinha(argumentos);
            break;

        case Operacao::EDITAR_LINHA:

            break;

        case Operacao::EXCLUIR_LINHA:

            break;

        case Operacao::CAPTURAR_LINHAS:
            capturarLinhas(callback, nullptr);
            break;

        default:
            throw std::runtime_error("COMANDO INVÁLIDO"); // Operação inválida
    }
}

void SqliteHandler::criarBaseDados(){
    if (this->dbExiste()) return;

    this->codigoRetorno = sqlite3_open(this->caminhoCompletoBaseDeDados.c_str(), &this->db);   

    if (this->codigoRetorno != SQLITE_OK){
        throw std::runtime_error("Erro ao criar a base de dados!\nCodigo de erro: " + this->codigoRetorno);
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

void SqliteHandler::inserirLinha(std::string* argumentos){
    this->codigoRetorno = sqlite3_open(this->caminhoCompletoBaseDeDados.c_str(), &this->db);
    if (this->codigoRetorno != SQLITE_OK){
        throw std::runtime_error("Erro ao executar a query");
    }

    sqlite3_prepare_v2(this->db, argumentos->c_str(), -1, &this->queryFormatada, nullptr);
}

void SqliteHandler::capturarLinhas(int (*callback)(void *, int, char **, char **), std::string* argumentos){
    bool argumentoEhNulo = (argumentos == nullptr || argumentos == NULL);
    this->codigoRetorno = sqlite3_open(this->caminhoCompletoBaseDeDados.c_str(), &this->db);
    char **mensagemErro = nullptr;

    //SELECT nome FROM Clientes;
    if (this->codigoRetorno != SQLITE_OK){
        throw std::runtime_error("Erro ao abrir a base de dados");
    }
    
    if (argumentoEhNulo){
        this->codigoRetorno = sqlite3_exec(this->db, "SELECT nome FROM Clientes;", callback, nullptr, mensagemErro);
        
    }

    sqlite3_close(this->db);
}

void SqliteHandler::excluirLinha(std::string* query){
    std::cout << "a" << std::endl;
}