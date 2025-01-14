#include "SqliteHandler.hpp"

SqliteHandler::SqliteHandler(){  
    this->nomeBD = NOME_ARQUIVO_BD_PADRAO;
    try{
        this->executarOperacao(Operacao::CRIAR_BASE_DADOS);
        this->executarOperacao(Operacao::CRIAR_TABELAS);
    } catch(std::runtime_error* erro){
        MessageHandler::MostrarErro(erro->what());
        delete erro;
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
    std::runtime_error *erro = nullptr; 
    
    switch (operacao) {
        case Operacao::CRIAR_BASE_DADOS:
            criarBaseDados(erro);
            break;

        case Operacao::CRIAR_TABELAS:
            criarTabelas(erro);
            break;

        default:
            erro = new std::runtime_error("COMANDO INVÁLIDO");
            throw erro; // Operação inválida
    }
}

void SqliteHandler::executarOperacao(Operacao operacao, std::string &caminhoQuery){
    std::runtime_error *erro = nullptr; 
    
    switch (operacao) {
        case Operacao::INSERIR_LINHA:
            inserirLinha(erro, caminhoQuery);
            break;

        case Operacao::EDITAR_LINHA:

            break;

        case Operacao::EXCLUIR_LINHA:

            break;

        case Operacao::CAPTURAR_LINHAS:
            
            break;

        default:
            erro = new std::runtime_error("COMANDO INVÁLIDO");
            throw erro; // Operação inválida
    }
}

void SqliteHandler::criarBaseDados(std::runtime_error *erro){
    if (this->dbExiste()) return;
    std::string caminhoCompletoBaseDeDados(CAMINHO_BD_PADRAO+this->nomeBD);

    this->codigoRetorno = sqlite3_open(caminhoCompletoBaseDeDados.c_str(), &this->db);   

    if (this->codigoRetorno != SQLITE_OK){
        erro = new std::runtime_error("Erro ao criar a base de dados!\nCodigo de erro: " + this->codigoRetorno);
        throw erro;
    }
    
    delete queries;
    sqlite3_close_v2(db);
}

void SqliteHandler::criarTabelas(std::runtime_error *erro){
    char *errorMsg = nullptr;

    std::string caminhoCompletoBaseDeDados(CAMINHO_BD_PADRAO+this->nomeBD);
    std::string caminhoCompletoArquivoSQLdeSetup = Dir::combinarCaminhos(CAMINHO_SETUP, ARQUIVO_CRIAR_TABELAS);

    this->codigoRetorno = sqlite3_open(caminhoCompletoBaseDeDados.c_str(), &this->db);

    if (this->codigoRetorno != SQLITE_OK){
        erro = new std::runtime_error("Erro ao abrir a base de dados");
        throw erro;
    }

    this->codigoRetorno = sqlite3_exec(db, "PRAGMA foreign_keys = ON;", NULL, NULL, NULL);

    if (this->codigoRetorno != SQLITE_OK){
        //std::cerr << "ERRO COD: " << this->codigoRetorno << std::endl;
        //std::cerr << "ERRO MSG: " << errorMsg << std::endl;
        erro = new std::runtime_error("Erro ao abrir a base de dados");
        throw erro;
    }

    this->setQueries(&caminhoCompletoArquivoSQLdeSetup);

    for (auto iterador = queries->begin(); iterador != queries->end(); ++iterador){
        this->codigoRetorno = sqlite3_exec(db, (*iterador).c_str(), NULL, NULL, &errorMsg);
        if (this->codigoRetorno != SQLITE_OK){
            /* std::cerr << "DEU RUIM NA HORA DE EXECUTAR" << std::endl;
            std::cerr << "ERRO COD: " << this->codigoRetorno << std::endl;
            std::cerr << "ERRO MSG: " << errorMsg << std::endl; */
            
            sqlite3_free(errorMsg);
            erro = new std::runtime_error("Erro ao executar a query");
            
            throw erro;
        }
    }

    std::cout << caminhoCompletoArquivoSQLdeSetup << std::endl;
    delete this->queries;
    sqlite3_close_v2(db);
}

void SqliteHandler::inserirLinha(std::runtime_error *erro, std::string caminhoQuery){
    //char *errorMsg = nullptr;
    std::string *query = nullptr;
    std::string caminhoCompletoBaseDeDados(CAMINHO_BD_PADRAO+this->nomeBD);
    //std::ifstream arquivoQuery = QueryHandler::

    this->codigoRetorno = sqlite3_open(caminhoCompletoBaseDeDados.c_str(), &this->db);

    if (this->codigoRetorno != SQLITE_OK){
        std::cerr << "DEU RUIM AO ABRIR " << this->nomeBD << " PATRAO" << std::endl;
        erro = new std::runtime_error("Erro ao abrir a base de dados");
        throw erro;
    }

    query = QueryHandler::carregarQueryUnica(&caminhoQuery);

    std::cout << (*query) << std::endl;

    sqlite3_prepare_v2(this->db, query->c_str(), -1, &this->queryFormatada, nullptr);

    
    delete query;
}

void SqliteHandler::excluirLinha(std::runtime_error *erro, std::string caminhoQuery){
    std::cout << "a" << std::endl;
}