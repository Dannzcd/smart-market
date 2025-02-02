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

void Marca::setControladorSQL(SqliteHandler *controladorSQL){
    this->controladorSQL = controladorSQL;
}

void Marca::imprimirMarcas(){
    /* if (Marca::listaMarcas == nullptr)
        throw std::runtime_error("A lista de marcas está nula!"); */

    if (Marca::listaMarcas.empty())
        throw std::runtime_error("A lista de marcas está vazia!");

    for (int i = 0; i < (int)listaMarcas.size(); i++){
        std::cout << Marca::listaMarcas.at(i).getNome() << std::endl;
    }
}

void Marca::registrarMarcasPadrao(SqliteHandler* controladorSql){
    std::ostringstream argumentoss;
    std::string argumento = "a";
    Marca::listaMarcas.reserve(10);
    std::vector<std::string> argumentos;
    argumentos.reserve(10);
    argumento.reserve(128);

    std::string marcasArray[10] = {"Nestlé",
            "Coca-cola",
            "Unilever",
            "P&G",
            "PepsiCo",
            "Danone",
            "Kelloggs",
            "Perdigão",
            "Saida",
            "Ypê"
    };

    for (int i = 0; i < 10; i++){
        Marca::listaMarcas.emplace_back(i+1, marcasArray[i]);
        //std::cout << marcasArray[i] << std::endl;
    }

    for (Marca& marca: Marca::listaMarcas){
        argumentoss << "(" << std::to_string(marca.getId()) << ", '" << marca.getNome() << "')";
        argumento = argumentoss.str();
        argumentos.emplace_back(argumento);

        if (argumento.empty()) {
            throw std::runtime_error("Argumento vazio ao inserir linha");
        }

        argumentoss.str("");
        argumento.clear();
    }

    for (std::string& arg: argumentos){
        try{
                controladorSql->executarOperacao(
                Operacao::INSERIR_LINHA,
                nullptr,
                Marca::TABELA_MARCA.c_str(),
                "id_marca, nome",
                &arg
            );
        }
        catch(std::string& e){
            
        }
        //std::cout << arg << std::endl;
    }
}

int Marca::empilharMarcas(void *data, int argc, char **argv, char **col_name){
    int *achou = static_cast<int*>(data);

    (*achou) = 1;
    
    if (argv != nullptr){
        Marca::listaMarcas.push_back(Marca(atol(argv[0]), argv[1]));
    }

    return 0;
}

void Marca::criar(){
    std::string argumento;

    argumento += "('" + this->getNome() + "')";

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

    if (this->id == -1){
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
    /* if (Marca::listaMarcas == nullptr){
        Marca::listaMarcas = new std::vector<Marca>;
    } else{
        delete Marca::listaMarcas;
        Marca::listaMarcas = new std::vector<Marca>;
    } */

    Marca::listaMarcas.reserve(20);

    if (marca->getControladorSQL() == nullptr) throw std::runtime_error("Controlador SQL não acessível!");

    if (argumento == nullptr){
        marca->getControladorSQL()->executarOperacao(
            Operacao::CAPTURAR_LINHAS,
            marca->empilharMarcas,
            Marca::TABELA_MARCA.c_str(),
            "*",
            nullptr    
        );
    }

    else{
        marca->getControladorSQL()->executarOperacao(
            Operacao::CAPTURAR_LINHAS,
            marca->empilharMarcas,
            Marca::TABELA_MARCA.c_str(),
            "nome",
            argumento    
        );
    }
}

bool Marca::existe(){
    std::string query;

    return true;
}