#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <map>
#include <functional>
#include <limits>
#include "SqliteHandler.hpp"
#include "MessageHandler.hpp"
#include "Dir.hpp"
#include "Funcionario.hpp"
#include "ClienteCivil.hpp"
#include "Produto.hpp"
#include "Marca.hpp"

volatile bool encerrarPrograma = false;
std::map<int, Produto> produtos;

void cadastrarProduto() {
    std::cout << "Iniciando o cadastro doss produtos...\n";

    std::string nome, marcaNome;
    double pesoLiquido, preco;
    unsigned unidadesDisponiveis;
    int idTipo;
    Marca* marca = nullptr;

    std::cout << "Digite o nome do produto: ";
    std::getline(std::cin >> std::ws, nome);

    std::cout << "Digite o peso líquido do produto: ";
    std::cin >> pesoLiquido;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Digite o preço do produto: ";
    std::cin >> preco;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Digite a quantidade disponível do produto: ";
    std::cin >> unidadesDisponiveis;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Digite o nome da marca do produto: ";
    std::getline(std::cin, marcaNome);

    std::cout << "Digite o ID do tipo de produto: ";
    std::cin >> idTipo;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    marca = new Marca(marcaNome);
    Produto novoProduto(nome, marca, pesoLiquido, preco, idTipo);
    novoProduto.setUnidadesDisponiveis(unidadesDisponiveis);
    novoProduto.criar();

    int idProduto = produtos.size() + 1;
    produtos[idProduto] = novoProduto;

    std::cout << "Produto cadastrado com sucesso!\n";
}

void lerProdutos() {
    if (produtos.empty()) {
        std::cout << "Nenhum produto cadastrado.\n";
        return;
    }

    std::cout << "Lista de produtos cadastrados:\n";
    for (const auto& par : produtos) {
        const Produto& produto = par.second;
        std::cout << "ID: " << par.first
                  << " | Nome: " << produto.getNome()
                  << " | Marca: " << (produto.getMarca() ? produto.getMarca()->getNome() : "Sem Marca")
                  << " | Preço: R$ " << produto.getPrecoUnitario()
                  << " | Peso: " << produto.getPesoLiquido() << " kg"
                  << " | Estoque: " << produto.getUnidadesDisponiveis()
                  << " | Tipo ID: " << produto.getIdTipo() << "\n";
    }
}

void excluirProduto() {
    int id;
    std::cout << "Digite o ID do produto que deseja excluir: ";
    std::cin >> id;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    auto it = produtos.find(id);
    if (it == produtos.end()) {
        std::cout << "Produto com ID " << id << " não encontrado.\n";
        return;
    }

    it->second.excluir();
    produtos.erase(it);
    std::cout << "Produto removido com sucesso!\n";
}

void editarProduto() {
    int id;
    std::cout << "Digite o ID do produto que deseja editar: ";
    std::cin >> id;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    auto it = produtos.find(id);
    if (it == produtos.end()) {
        std::cout << "Produto com ID " << id << " não encontrado.\n";
        return;
    }

    Produto& produto = it->second;
    std::string novoNome;
    double novoPreco, novoPeso;
    unsigned novaQuantidade;
    int novoIdTipo;

    std::cout << "Novo nome do produto: ";
    std::getline(std::cin, novoNome);
    if (!novoNome.empty()) produto.setNome(novoNome);

    std::cout << "Novo preço: ";
    std::cin >> novoPreco;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    produto.setPrecoUnitario(novoPreco);

    std::cout << "Novo peso líquido: ";
    std::cin >> novoPeso;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    produto.setPesoLiquido(novoPeso);

    std::cout << "Nova quantidade disponível: ";
    std::cin >> novaQuantidade;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    produto.setUnidadesDisponiveis(novaQuantidade);

    std::cout << "Novo ID do tipo de produto: ";
    std::cin >> novoIdTipo;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    produto.setIdTipo(novoIdTipo);

    produto.editar();
    std::cout << "Produto atualizado com sucesso!\n";
}

void *monitorarEntrada(void *variavel) {
    std::string comando;
    while (!encerrarPrograma) {
        std::cout << "Digite um comando (cadastrar/ler/editar/excluir/sair): ";
        std::cin >> comando;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (comando == "sair") {
            encerrarPrograma = true;
        } else if (comando == "cadastrar") {
            cadastrarProduto();
        } else if (comando == "ler") {
            lerProdutos();
        } else if (comando == "editar") {
            editarProduto();
        } else if (comando == "excluir") {
            excluirProduto();
        } else {
            std::cout << "Comando não reconhecido!\n";
        }
    }
    return nullptr;
}

int main(int argc, char *argv[]) {
    pthread_t threadEntrada;
    pthread_create(&threadEntrada, nullptr, monitorarEntrada, nullptr);
    pthread_join(threadEntrada, nullptr);
    return 0;
}