#ifndef PATHMAPPER_HPP
#define PATHMAPPER_HPP

#include <fstream>
#include <filesystem>
#include <unordered_map>
#include <string>
#include <vector>
#include <initializer_list>

#define CAMINHO_ARQUIVOS_SQL "../../sql_scripts"

// Primeira camada da pastas
#define CAMINHO_CLIENTES "/clientes"
#define CAMINHO_SETUP "/setup"
#define CAMINHO_FUNCIONARIOS "/funcionarios"
#define CAMINHO_PRODUTOS "/produtos"
#define CAMINHO_VENDAS "/vendas"

// Segunda camada
#define CAMINHO_GET_COMUM "/get"
#define CAMINHO_SET_COMUM "/set"

// Terceira camada
#define SELECIONAR_CLIENTE_CIVIL "/select_cliente_civil.sql"
#define SELECIONAR_CLIENTE_EMPRESA "/select_cliente_empresa.sql"
#define INSERIR_CLIENTE_CIVIL "/inserir_cliente_civil.sql"
#define INSERIR_CLIENTE_EMPRESA "/inserir_cliente_empresa.sql"
#define INSERIR_CLIENTE "/inserir_cliente.sql"

#define ARQUIVO_CRIAR_TABELAS "/criarTabelas.sql"

#define SELECIONAR_POR_CPF "/select_por_cpf.sql"
#define INSERIR_FUNCIONARIO "/inserir_funcionario.sql"

#define SELECIONAR_PRODUTOS_DISPONIVEIS "/select_disponiveis.sql"
#define SELECIONAR_PRODUTOS_ESGOTADOS "/select_esgotados.sql"
#define SELECIONAR_PRODUTOS_POR_ID "/select_por_id.sql"
#define SELECIONAR_PRODUTOS_POR_MARCA "/select_por_marca.sql"
#define SELECIONAR_PRODUTOS_POR_TIPO "/select_por_tipo.sql"

#define SELECIONAR_VENDAS_POR_DATA "/select_por_data.sql"
#define SELECIONAR_VENDAS_POR_ID "/select_por_data.sql"
#define SELECIONAR_VENDAS_POR_TIPO "/select_por_tipo.sql"
#define INSERIR_VENDA "/inserir_venda.sql"
#define INSERIR_ITENS_VENDA "/inserir_itens_venda.sql"

//NAO CONSEGUI PENSAR EM ALGO MELHOR (E TAMBEM NAO DA TEMPO) 
class Dir{
    public:
    static std::string combinarCaminhos(const char *primeiraCamada, const char *segundaCamada);
    static std::string combinarCaminhos(const char *primeiraCamada, const char *segundaCamada, const char *terceiraCamada);

};

#endif