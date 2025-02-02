#include "Produto.hpp"

std::string Produto::getNome(){
    return this->nome;
}

double Produto::getPesoLiquido(){
    return this->pesoLiquido;
}

double Produto::getPreco(){
    return this->preco;
}

unsigned Produto::getUnidadesDisponiveis(){
    return this->unidadesDisponiveis;
}

bool Produto::disponivel(){
    return this->unidadesDisponiveis > 0;
}

size_t Produto::getId(){
    return this->id;
}

SqliteHandler *Produto::getControladorSQL(){
    if (this->controladorSQL == nullptr){
        throw std::runtime_error("Funcionalidade de salvamento inválida!");
    }

    return this->controladorSQL;
}

Produto::Produto(){
    this->id = SqliteHandler::NAO_ESTA_NO_BANCO;
}

Produto::Produto(std::string nome, Marca *marca, double pesoLiquido, double preco, SqliteHandler *controladorSQL){
    this->id = SqliteHandler::NAO_ESTA_NO_BANCO;
    this->setNome(nome);
    this->setMarca(marca);
    this->setPesoLiquido(pesoLiquido);
    this->setPreco(preco);
    this->setControladorSQL(controladorSQL);
}

void Produto::setNome(std::string nome){
    if (nome.empty()) 
        throw std::runtime_error("Não é possível inserir nome vazio no produto");

    this->nome = nome;
}

void Produto::setMarca(Marca *marca){
    if (marca == nullptr)
        throw std::runtime_error("Marca não existe ou não está referenciada corretamente");

    this->marca = marca;
}

Marca* Produto::getMarca(){
    if (this->marca == nullptr){
        throw std::runtime_error("Produto com marca inválida");
    }

    return this->marca;
}

void Produto::setPesoLiquido(double pesoLiquido){
    if (pesoLiquido <= 0.0)
        throw std::runtime_error("Peso igual ou inferior a 0 não é válido");
    
    this->pesoLiquido = pesoLiquido;
}

void Produto::setId(size_t id){
    if (id <= 0){
        throw std::runtime_error("ID inválido");
    }

    this->id = id;
}

void Produto::atualizarQuantidade(int quantidade){
    if ((int)this->unidadesDisponiveis + quantidade < 0)
        throw std::runtime_error("A quantidade atualizada não pode ser menor que 0");

    this->unidadesDisponiveis += quantidade;
}

void Produto::setControladorSQL(SqliteHandler *controlador){
    if (controlador == nullptr){
        throw std::runtime_error("Tentativa inválida de ativação do controlador SQL");
    }

    this->controladorSQL = controlador;
}

void Produto::setPreco(double preco){
    if (preco <= 0)
        throw std::runtime_error("Preço inválido");

    this->preco = preco;
}

void Produto::setUnidadesDisponiveis(unsigned unidades){
    this->unidadesDisponiveis = unidades;
}

int Produto::preencherListaProdutos(void *data, int argc, char **argv, char **col_name){
    bool *achou = static_cast<bool*>(data);

    if ((*achou) == false){
        (*achou) = true;
    }
    
    Produto::listaProdutos.emplace_back();

    Produto::listaProdutos.back().setId(atol(argv[0]));
    Produto::listaProdutos.back().setNome(argv[1]);
    Produto::listaProdutos.back().setPesoLiquido(atof(argv[3]));
    Produto::listaProdutos.back().setPreco(atof(argv[4]));
    Produto::listaProdutos.back().setUnidadesDisponiveis(atol(argv[5]));

    for (Marca& marca : Marca::listaMarcas){
        if (marca.getId() == atol(argv[1])){
            Produto::listaProdutos.back().setMarca(&marca);
        }
    }

    return 0;
}

void Produto::buscarTodosOsProdutos(SqliteHandler *controladorSQL){
    if (!Produto::listaProdutos.empty()){
        Produto::listaProdutos.erase(
            Produto::listaProdutos.begin(),
            Produto::listaProdutos.end()  
        );
    }
    
    if (Produto::listaProdutos.capacity() != 10){
        Produto::listaProdutos.reserve(10);
    }

    controladorSQL->executarOperacao(
        Operacao::CAPTURAR_LINHAS,
        preencherListaProdutos,
        Produto::TABELA_PRODUTO.c_str(),
        "id_produto, nome, id_marca, peso_liquido, preco_unitario, unidades_disponiveis",
        nullptr
    );

    if (Produto::listaProdutos.size() == 0){
        throw std::string("Não foi possível encontrar produtos salvos");
    }

    std::cout << Produto::listaProdutos.size() << std::endl;
}

void Produto::imprimirListaProdutos(){
    std::cout << std::left
        << std::setw(30) << "Id " << std::left
        << std::setw(30) << "Nome " << std::left
        << std::setw(30) << "Preco " << std::endl;

    for (Produto& produto: Produto::listaProdutos){
        std::cout << std::left
            << std::setw(30) << produto.getId() << std::left
            << std::setw(30) << produto.getNome() << std::left
            << std::setw(30) << produto.getPreco() << std::endl;
    }
}

void Produto::criar(){
    std::string campos;
    std::string argumentos;

    campos = "nome, id_marca, id_tipo, peso_liquido, preco_unitario, unidades_disponiveis";

    argumentos = "('" + this->getNome() + "'" +
        ", " + std::to_string(this->getMarca()->getId()) +
        ", " + std::to_string(1) +
        ", " + std::to_string(this->getPesoLiquido()) +
        ", " + std::to_string(this->getPreco()) +
        ", " + std::to_string(this->getUnidadesDisponiveis()) +
        ")";

    this->getControladorSQL()->executarOperacao(
        Operacao::INSERIR_LINHA,
        nullptr,
        Produto::TABELA_PRODUTO.c_str(),
        campos,
        &argumentos
    );

    this->setId(sqlite3_last_insert_rowid(this->getControladorSQL()->getDb()));
}

void Produto::editar(){
    std::string campos;
    std::string argumentos;

    campos = "nome, id_marca, id_tipo, peso_liquido, preco_unitario, unidades_disponiveis";

    argumentos = "('" + this->getNome() + "'" +
        ", " + std::to_string(this->getMarca()->getId()) +
        ", " + std::to_string(1) +
        ", " + std::to_string(this->getPesoLiquido()) +
        ", " + std::to_string(this->getPreco()) +
        ", " + std::to_string(this->getUnidadesDisponiveis()) +
        ") WHERE id_produto = " + std::to_string(this->getId());
    

}

void Produto::excluir(){
    std::string argumento = "WHERE id_produto = " + std::to_string(this->getId());

    if (this->id == -1){
        throw std::runtime_error("Impossível excluir objeto inexistente");
    }

    std::cout << argumento << std::endl;

    this->getControladorSQL()->executarOperacao(
        Operacao::EXCLUIR_LINHA,
        nullptr,
        Produto::TABELA_PRODUTO.c_str(),
        "",
        &argumento
    );
}