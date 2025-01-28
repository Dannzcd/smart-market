#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <map>
#include <functional>
#include "SqliteHandler.hpp"
#include "MessageHandler.hpp"
#include "Dir.hpp"
#include "Funcionario.hpp"
#include "ClienteCivil.hpp"
#include "Produto.hpp"  
#include "Marca.hpp"    

// Variável global para controlar o encerramento do programa
volatile bool encerrarPrograma = false;

// Mapeamento de ID para Produto
std::map<int, Produto> produtos;

// Funções para manipulação de produtos
void cadastrarProduto() {
    std::cout << "Iniciando o cadastro do produto..." << std::endl;  // Mensagem de debug

    std::string nome;
    double pesoLiquido, preco;
    unsigned unidadesDisponiveis;
    std::string marcaNome;
    Marca* marca = nullptr;

    // Leitura dos dados do produto
    std::cout << "Digite o nome do produto: ";
    std::cin.ignore();  // Limpa o buffer de entrada após o comando anterior
    std::getline(std::cin, nome);  // Lê o nome do produto

    std::cout << "Digite o peso líquido do produto: ";
    std::cin >> pesoLiquido;
    std::cin.ignore();  // Limpa o buffer após o número

    std::cout << "Digite o preço do produto: ";
    std::cin >> preco;
    std::cin.ignore();  // Limpa o buffer após o número

    std::cout << "Digite a quantidade disponível do produto: ";
    std::cin >> unidadesDisponiveis;
    std::cin.ignore();  // Limpa o buffer após o número

    std::cout << "Digite o nome da marca do produto: ";
    std::getline(std::cin, marcaNome);  // Lê o nome da marca

    // Criação da marca
    marca = new Marca(marcaNome);  // Cria a marca com o nome fornecido

    // Criação do produto
    Produto novoProduto(nome, marca, pesoLiquido, preco);
    novoProduto.setUnidadesDisponiveis(unidadesDisponiveis);

    // Gerar um ID para o novo produto
    int idProduto = produtos.size() + 1;  // Um ID simples baseado no tamanho atual do mapa

    // Armazenar o produto no mapa
    produtos[idProduto] = novoProduto;

    std::cout << "Produto cadastrado com sucesso!" << std::endl;
    std::cout << "ID do Produto: " << idProduto << std::endl;
    std::cout << "Nome do Produto: " << novoProduto.getNome() << std::endl;
    std::cout << "Marca: " << novoProduto.getMarca()->getNome() << std::endl;
    std::cout << "Preço: R$ " << novoProduto.getPreco() << std::endl;
    std::cout << "Peso: " << novoProduto.getPesoLiquido() << " kg" << std::endl;
    std::cout << "Quantidade disponível: " << novoProduto.getUnidadesDisponiveis() << std::endl;
}

void *monitorarEntrada(void *variavel) {
    std::string comando;
    while (!encerrarPrograma) {
        std::cout << "Digite um comando (cadastrar/ler/editar/excluir/sair): ";
        std::cin >> comando;
        std::cin.ignore();  // Limpa o buffer de entrada após o comando

        std::cout << "Comando recebido: " << comando << std::endl;  // Mensagem de depuração

        if (comando == "sair") {
            encerrarPrograma = true;
        }
        else if (comando == "cadastrar") {
            std::cout << "Iniciando o processo de cadastro..." << std::endl;  // Mensagem de depuração
            cadastrarProduto();  // Chama a função de cadastro
        }
        else {
            std::cout << "Comando não reconhecido!" << std::endl;
        }
    }
    return nullptr;
}

int main(int argc, char *argv[]) {
    pthread_t threadEntrada;

    // Cria a thread para monitorar a entrada do usuário
    pthread_create(&threadEntrada, nullptr, monitorarEntrada, nullptr);

    // Aguarda a finalização da thread de entrada
    pthread_join(threadEntrada, nullptr);

    return 0;
}
