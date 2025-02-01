#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include "SqliteHandler.hpp"
#include "MessageHandler.hpp"
#include "Dir.hpp"
#include "Funcionario.hpp"
#include "ClienteCivil.hpp"
#include "Marca.hpp"

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
    std::string caminho = Dir::combinarCaminhos(CAMINHO_FUNCIONARIOS, CAMINHO_SET_COMUM, INSERIR_FUNCIONARIO);
    std::string nome("veja");
    SqliteHandler controladorSqlite;
    Marca m1;
    std::string argumentos("WHERE id_marca = 10");

    m1.setNome(nome);
    m1.setId(10);
    //
    m1.setSqliteHandler(&controladorSqlite);

    //IMPORTANTE: ELE DIFERENCIA AVISOS DE ERROS
    //EXEMPLOS: 

    try {
        Marca::buscarMarcas(&m1, nullptr);
        m1.excluir();
    }
    catch(std::string& aviso){
        MessageHandler::MostrarAviso(aviso);
    }
    catch(std::runtime_error& erro){
        MessageHandler::MostrarErro(erro.what());
    }

    // Cria a thread para monitorar a entrada do usuário
    pthread_create(&threadEntrada, nullptr, monitorarEntrada, nullptr);

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