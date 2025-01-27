#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include "SqliteHandler.hpp"
#include "MessageHandler.hpp"
#include "Dir.hpp"
#include "Funcionario.hpp"
#include "ClienteCivil.hpp"

// Variável global para controlar o encerramento do programa
volatile bool encerrarPrograma = false;

void *routine(void *variavel) {
    std::cout << "Vou dormir por 5 segundos" << std::endl;
    sleep(5);
    std::cout << "Acordei!" << std::endl;
    return nullptr;
}

void *monitorarEntrada(void *variavel) {
    std::string comando;
    while (!encerrarPrograma) {
        std::cout << "Digite 'sair' para encerrar o programa: ";
        std::cin >> comando;
        if (comando == "sair") {
            encerrarPrograma = true; // Sinaliza o encerramento
        }
    }
    return nullptr;
}

int main(int argc, char *argv[]) {
    pthread_t threadEntrada;

    // Cria a thread para monitorar a entrada do usuário
    pthread_create(&threadEntrada, nullptr, monitorarEntrada, nullptr);
    std::string caminho = Dir::combinarCaminhos(CAMINHO_FUNCIONARIOS, CAMINHO_SET_COMUM, INSERIR_FUNCIONARIO);
    std::string nome("teste");

    try {
        SqliteHandler controladorSqlite;
        ClienteCivil c(&controladorSqlite);
        c.setNome(nome);
        c.buscar();
    }
    catch(std::runtime_error& erro){
        MessageHandler::MostrarErro(erro.what());
    }

    sleep(300);

    // Cria a thread para monitorar a entrada do usuário
    pthread_create(&threadEntrada, nullptr, monitorarEntrada, nullptr);

    std::string caminho = Dir::combinarCaminhos(CAMINHO_FUNCIONARIOS, CAMINHO_SET_COMUM, INSERIR_FUNCIONARIO);

    try {
        SqliteHandler controladorSqlite;
        std::cout << caminho << std::endl;
        controladorSqlite.executarOperacao(Operacao::INSERIR_LINHA, caminho);
    } catch (std::runtime_error *erro) {
        MessageHandler::MostrarErro(erro->what());
        delete erro;
    }

    // Substitui sleep(300) por um loop que verifica a condição de encerramento
    int contador = 0;
    while (!encerrarPrograma && contador < 300) {
        sleep(1);
        contador++;
    }

    if (encerrarPrograma) {
        std::cout << "Programa encerrado pelo usuário." << std::endl;
    } else {
        std::cout << "Finalizando após o tempo limite." << std::endl;
    }

    // Aguarda a finalização da thread de entrada
    pthread_join(threadEntrada, nullptr);

    return 0;
}