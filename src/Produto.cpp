#include "Produto.hpp"

Produto::Produto() : id(SqliteHandler::NAO_ESTA_NO_BANCO), nome(""), pesoLiquido(0.0), precoUnitario(0.0), unidadesDisponiveis(0), marca(nullptr), idTipo(0) {}

Produto::Produto(std::string nome, Marca* marca, double pesoLiquido, double precoUnitario, int idTipo)
    : id(SqliteHandler::NAO_ESTA_NO_BANCO), nome(nome), pesoLiquido(pesoLiquido), precoUnitario(precoUnitario), unidadesDisponiveis(0), marca(marca), idTipo(idTipo) {}

Produto::Produto(size_t id, std::string nome, Marca* marca, double pesoLiquido, double precoUnitario, unsigned unidadesDisponiveis, int idTipo)
    : id(id), nome(nome), marca(marca), pesoLiquido(pesoLiquido), precoUnitario(precoUnitario), unidadesDisponiveis(unidadesDisponiveis), idTipo(idTipo) {}

size_t Produto::getId() {
    if (this->id == SqliteHandler::NAO_ESTA_NO_BANCO) throw std::runtime_error("Objeto não salvo na base de dados.");
    return this->id;
}

std::string Produto::getNome() const { return nome; }
void Produto::setNome(std::string nome) { this->nome = nome; }

double Produto::getPesoLiquido() const { return pesoLiquido; }
void Produto::setPesoLiquido(double pesoLiquido) { this->pesoLiquido = pesoLiquido; }

double Produto::getPrecoUnitario() const { return precoUnitario; }
void Produto::setPrecoUnitario(double precoUnitario) { this->precoUnitario = precoUnitario; }

unsigned Produto::getUnidadesDisponiveis() const { return unidadesDisponiveis; }
void Produto::setUnidadesDisponiveis(unsigned unidades) { unidadesDisponiveis = unidades; }

Marca* Produto::getMarca() const { return marca; }
void Produto::setMarca(Marca* marca) { this->marca = marca; }

int Produto::getIdTipo() const { return idTipo; }
void Produto::setIdTipo(int idTipo) { this->idTipo = idTipo; }

bool Produto::disponivel() const { return unidadesDisponiveis > 0; }

void Produto::adicionarUnidades(unsigned quantidade) { unidadesDisponiveis += quantidade; }

void Produto::setSqliteHandler(SqliteHandler *controladorSQL) {
    this->controladorSQL = controladorSQL;
}

void Produto::criar() {
    std::string argumento = "('" + this->getNome() + "', " + std::to_string(this->marca->getId()) + ", " + std::to_string(this->getIdTipo()) + ", "
                            + std::to_string(this->getPesoLiquido()) + ", " + std::to_string(this->getPrecoUnitario()) + ", "
                            + std::to_string(this->getUnidadesDisponiveis()) + ")";

    this->controladorSQL->executarOperacao(
        Operacao::INSERIR_LINHA, 
        nullptr, 
        "PRODUTOS", 
        "nome, id_marca, id_tipo, peso_liquido, preco_unitario, unidades_disponiveis", 
        &argumento
    );
}

void Produto::editar() {
    if (this->id == SqliteHandler::NAO_ESTA_NO_BANCO)
        throw std::runtime_error("Não é possível editar um objeto que não foi salvo");

    std::string argumento = " SET nome='" + this->getNome() + "', id_marca=" + std::to_string(this->marca->getId()) +
                            ", id_tipo=" + std::to_string(this->getIdTipo()) +
                            ", peso_liquido=" + std::to_string(this->getPesoLiquido()) +
                            ", preco_unitario=" + std::to_string(this->getPrecoUnitario()) +
                            ", unidades_disponiveis=" + std::to_string(this->getUnidadesDisponiveis()) +
                            " WHERE id_produto = " + std::to_string(this->getId());

    this->controladorSQL->executarOperacao(
        Operacao::EDITAR_LINHA, 
        nullptr, 
        "PRODUTOS", 
        "nome", 
        &argumento
    );
}

void Produto::excluir() {
    std::string argumento = "WHERE id_produto = " + std::to_string(this->id);

    if (this->id == static_cast<size_t>(-1))
        throw std::runtime_error("Impossível excluir objeto inexistente");

    this->controladorSQL->executarOperacao(
        Operacao::EXCLUIR_LINHA,
        nullptr,
        "PRODUTOS",
        "",
        &argumento
    );
}
