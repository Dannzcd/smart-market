#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include "SqliteHandler.hpp"
#include "MessageHandler.hpp"
#include "Dir.hpp"
#include "Funcionario.hpp"
#include "ClienteCivil.hpp"
#include "Marca.hpp"
#include "Produto.hpp"

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
    SqliteHandler controladorSqlite;
    Marca::registrarMarcasPadrao(&controladorSqlite);

    // Cria a thread para monitorar a entrada do usuário
    std::string nome("veja");
    Marca m1;
    Produto p1("Desengordurante", &m1, 30.5, 7.99, &controladorSqlite);

    m1.setNome(nome);
    m1.setId(1);
    //
    m1.setControladorSQL(&controladorSqlite);

    //IMPORTANTE: ELE DIFERENCIA AVISOS DE ERROS
    //EXEMPLOS: 

    try{
        Produto::buscarTodosOsProdutos(&controladorSqlite);
        Produto::imprimirListaProdutos();
    } 
    catch(std::string& aviso){
        MessageHandler::MostrarAviso(aviso);
    }
    catch(std::runtime_error& erro){
        MessageHandler::MostrarErro(erro.what());
    }

    try {
        //Marca::buscarMarcas(&m1, nullptr);
        

        //m1.criar();
        //MessageHandler::MostrarMensagemSucesso("Objeto criado com sucesso!");
        //m1.excluir();
    }
    catch(std::string& aviso){
        MessageHandler::MostrarAviso(aviso);
    }
    catch(std::runtime_error& erro){
        MessageHandler::MostrarErro(erro.what());
    }

    try{
        m1.setNome("vanish");
        m1.editar();
        MessageHandler::MostrarMensagemSucesso("Objeto editado com sucesso!");

        p1.setId(2);
        //p1.criar();
        p1.excluir();
    }
    catch(std::string& aviso){
        MessageHandler::MostrarAviso(aviso);
    }
    catch(std::runtime_error& erro){
        MessageHandler::MostrarErro(erro.what());
    }

    try{
        p1.editar();
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