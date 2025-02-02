#include "Marca.hpp"

void Marca::setNome(std::string& nome){
    if (nome.empty()) throw std::runtime_error("Nome vazio");
    
    this->nome = nome;
}

void Marca::setNome(std::string* nome){
    if (nome->empty()) throw std::runtime_error("Nome vazio");
    
    this->nome = (*nome);
}

void Marca::setNome(const char* nome){
    if (nome == nullptr || strlen(nome) == 0) throw std::runtime_error("Nome vazio");

    this->nome = nome;
}

std::string Marca::getNome(){
    return this->nome;
}

size_t Marca::getId(){
    if (this->id == SqliteHandler::NAO_ESTA_NO_BANCO) throw std::runtime_error("Objeto não salvo na base de dados.");
    return this->id;
}

void Marca::setId(size_t id){
    this->id = id;
}

SqliteHandler* Marca::getControladorSQL(){
    return this->controladorSQL;
}

Marca::Marca(){
    this->id = SqliteHandler::NAO_ESTA_NO_BANCO;
}

Marca::Marca(std::string nome){
    this->id = SqliteHandler::NAO_ESTA_NO_BANCO;
    this->setNome(nome);
}

Marca::Marca(std::string* nome){
    this->id = SqliteHandler::NAO_ESTA_NO_BANCO;
    this->setNome(nome);
}

Marca::Marca(size_t id, std::string nome){
    this->id = id;
    this->setNome(nome);
}

void Marca::setSqliteHandler(SqliteHandler *controladorSQL){
    this->controladorSQL = controladorSQL;
}

void Marca::imprimirMarcas(){
    if (Marca::listaMarcas == nullptr)
        throw std::runtime_error("A lista de marcas está nula!");

    if (Marca::listaMarcas->empty())
        throw std::runtime_error("A lista de marcas está vazia!");

    for (int i = 0; i < (int)listaMarcas->size(); i++){
        std::cout << Marca::listaMarcas->at(i).getNome() << std::endl;
    }
}

int Marca::callbackMarca(void *data, int argc, char **argv, char **col_name){
    bool *achou = static_cast<bool*>(data);

    (*achou) = true;
    
    if (argv != nullptr){
        Marca::listaMarcas->push_back(Marca(atol(argv[0]), argv[1]));
    }

    return 0;
}

void Marca::criar(){
    std::string argumento;

    argumento += "('" + this->getNome() + "')";

    std::cout << Marca::TABELA_MARCA << std::endl;

    this->getControladorSQL()->executarOperacao(
            Operacao::INSERIR_LINHA, 
            nullptr, 
            Marca::TABELA_MARCA.c_str(), 
            "nome", 
            &argumento
        );
}

void Marca::editar(){
    std::string argumento;

    if (this->id == SqliteHandler::NAO_ESTA_NO_BANCO){
        throw std::runtime_error("Não é possível editar um objeto que não foi salvo");
    }

    argumento = " SET nome='" + this->getNome() + "'"
                + " WHERE id_marca = " + std::to_string(this->getId());

    this->controladorSQL->executarOperacao(
        Operacao::EDITAR_LINHA,
        nullptr,
        Marca::TABELA_MARCA.c_str(),
        "nome",
        &argumento
    );
}

void Marca::excluir(){
    std::string argumento = "WHERE id_marca = " + std::to_string(this->id);

    if (this->id == static_cast<size_t>(-1)){
        throw std::runtime_error("Impossível excluir objeto inexistente");
    }

    std::cout << argumento << std::endl;

    this->getControladorSQL()->executarOperacao(
        Operacao::EXCLUIR_LINHA,
        nullptr,
        Marca::TABELA_MARCA.c_str(),
        "",
        &argumento
    );
}

void Marca::buscarMarcas(Marca *marca, std::string* argumento){
    if (Marca::listaMarcas == nullptr){
        Marca::listaMarcas = new std::vector<Marca>;
    } else{
        delete Marca::listaMarcas;
        Marca::listaMarcas = new std::vector<Marca>;
    }

    Marca::listaMarcas->reserve(50);

    if (marca->getControladorSQL() == nullptr) throw std::runtime_error("Controlador SQL não acessível!");

    if (argumento == nullptr){
        marca->getControladorSQL()->executarOperacao(
            Operacao::CAPTURAR_LINHAS,
            marca->callbackMarca,
            "MARCAS",
            "*",
            nullptr    
        );
    }

    else{
        marca->getControladorSQL()->executarOperacao(
            Operacao::CAPTURAR_LINHAS,
            marca->callbackMarca,
            "MARCAS",
            "nome",
            argumento    
        );
    }
}

bool Marca::existe(){
    std::string query;

    return true;
}