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
    std::cout << "Iniciando o cadastro do produto...\n";

    std::string nome;
    double pesoLiquido, preco;
    unsigned unidadesDisponiveis;
    std::string marcaNome;
    Marca* marca = nullptr;

    std::cout << "Digite o nome do produto: ";
    std::getline(std::cin >> std::ws, nome);  // Solução correta para capturar o nome corretamente

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

    marca = new Marca(marcaNome);
    Produto novoProduto(nome, marca, pesoLiquido, preco);
    novoProduto.setUnidadesDisponiveis(unidadesDisponiveis);

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
                  << " | Preço: R$ " << produto.getPreco()
                  << " | Peso: " << produto.getPesoLiquido() << " kg"
                  << " | Estoque: " << produto.getUnidadesDisponiveis() << "\n";
    }
}

void editarProduto() {
    if (produtos.empty()) {
        std::cout << "Nenhum produto cadastrado para editar.\n";
        return;
    }

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
    std::string novoNome, novaMarca;
    double novoPreco, novoPeso;
    unsigned novaQuantidade;

    std::cout << "Novo nome do produto (" << produto.getNome() << "): ";
    std::getline(std::cin, novoNome);
    if (!novoNome.empty()) produto.setNome(novoNome);

    std::cout << "Novo preço do produto (R$ " << produto.getPreco() << "): ";
    std::cin >> novoPreco;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    produto.setPreco(novoPreco);

    std::cout << "Novo peso líquido do produto (" << produto.getPesoLiquido() << " kg): ";
    std::cin >> novoPeso;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    produto.setPesoLiquido(novoPeso);

    std::cout << "Nova quantidade disponível (" << produto.getUnidadesDisponiveis() << "): ";
    std::cin >> novaQuantidade;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    produto.setUnidadesDisponiveis(novaQuantidade);

    std::cout << "Novo nome da marca (" << produto.getMarca()->getNome() << "): ";
    std::getline(std::cin, novaMarca);
    if (!novaMarca.empty()) {
        produto.getMarca()->setNome(novaMarca);
    }

    std::cout << "Produto atualizado com sucesso!\n";
}

void excluirProduto() {
    if (produtos.empty()) {
        std::cout << "Nenhum produto cadastrado para excluir.\n";
        return;
    }

    int id;
    std::cout << "Digite o ID do produto que deseja excluir: ";
    std::cin >> id;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    auto it = produtos.find(id);
    if (it == produtos.end()) {
        std::cout << "Produto com ID " << id << " não encontrado.\n";
        return;
    }

    produtos.erase(it);
    std::cout << "Produto removido com sucesso!\n";
}

void *monitorarEntrada(void *variavel) {
    std::string comando;
    while (!encerrarPrograma) {
        std::cout << "Digite um comando (cadastrar/ler/editar/excluir/sair): ";
        std::cin >> comando;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (comando == "sair") {
            encerrarPrograma = true;
        }
        else if (comando == "cadastrar") {
            cadastrarProduto();
        }
        else if (comando == "ler") {
            lerProdutos();
        }
        else if (comando == "editar") {
            editarProduto();
        }
        else if (comando == "excluir") {
            excluirProduto();
        }
        else {
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
