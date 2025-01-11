# Supermercado
Projeto simples para faculdade.

## Bibliotecas e dependências para compilar por código fonte
- zlib-devel: https://docs.oracle.com/en/graalvm/enterprise/20/docs/reference-manual/ruby/Installingzlib/
- tcl: https://sqlite.org/src/doc/trunk/doc/compile-for-unix.md
- sqlite3: Para sistemas baseados em RedHat: sudo dnf install sqlite-devel
- sqlite3: Para sistemas baseados em debian/ubuntu: sudo apt-get install libsqlite3-dev

## Impostos calculados

1. Contribuição Social sobre o Lucro Líquido (CSLL) -> 9%
2. PIS (Programa de Integração Social) -> 0.65%
3. COFINS (Contribuição para o Financiamento da Seguridade Social) -> 3%
4. Contribuições previdenciárias (Assumimos como o salário completo do funcionário, contratado em regime CLT)
5. IṔTU estimado: Tarifa de R$ 5000,00 ao ano.

## Desconto para empresas ou compras em atacado
Para empresas ou para compradores no atacado, cada produto terá 7.5% de desconto

## Diagrama de classe

```mermaid

classDiagram

class Funcionario{
    -string nome
    -string cpf
    -double salarioBruto
    -double salarioLiquido

    +void setSalarioBruto(double salarioBruto)
    +void setSalarioLiquido(double salarioLiquido)
    +void setCpf(string cpf)
    +void setNome(string nome)
    +Funcionario(string nome, string cpf)
    +FUncionario(string nome, string cpf, double salarioBruto)
}

class Supermercado{
    -string nome
    -string cnpj
    -double faturamentoBruto
    -double totalImpostos
    -double faturamentoLiquido
    -double lucro

    +string getNome()
    +string getCnpj()
    +double getFaturamentoBruto()
    +double getFaturamentoLiquido()
    +double getLucro()
}

Supermercado *.. "1..n" Funcionario: tem

class Marca{
    -string nome

    +Marca()
    +Marca(std::string nome)

    +std::string getNome()
    +void setNome(std::string nome)
}

class Produto{
    -string nome
    -double pesoLiquido
    -double preco
    -unsigned unidadesDisponiveis

    +Produto()
    +Produto(Marca* marca)
    +Produto(std::string nome, Marca* marca, double pesoLiquido, double preco)

    +std::string getNome()
    +std::string getMarca()
    +double getPesoLiquido()
    +double getPreco()
    +bool disponivel()
    +unsigned getUnidadesDisponiveis()

    +void setNome(std::string nome)
    +void setMarca(Marca *marca)
    +void setPesoLiquido(double pesoLiquido)
    +void adicionarUnidades(unsigned quantidade)
}

Produto *.. "1..1" Marca
Supermercado *.. "1..n" Produto

class Pagamento{
    -string metodo
    -double valorTotal

    +Pagamento(string metodo, double tarifa)
    
    -void fazerRelatorioPagamento()
    -bool ehValido()
    +void fazerPagamento(double &faturamentoBruto)
}

class Cliente{
    <<interface>>
    -double subtotal

    +double getSubtotal()
}

class ClienteEmpresa{
    -std::string cnpj

    +ClienteEmpresa(std::string cnpj)
    +std::string getCnpj()
}

class ClienteCivil{
    -std::string cpf 
    
    +ClienteCivil(std::string cpf)

    +std::string getCpf()
}

Cliente <|-- ClienteEmpresa: é um
Cliente <|-- ClienteCivil: é um

Supermercado o.. Cliente

class Contabilidade{
    static -double calcularImpostosTrabalhistas(List~Funcionario*~ *funcionarios)
    static -double calcularImpostosEstataisFaturamento(double &faturamento)
    static +double calcularImpostosSobFaturamento()
    static +double calcularImpostosTotais()
    static +double definirLucro(double &lucro)
}

Supermercado *.. "1..1" Contabilidade: tem

class FileHandler{
    <<interface>>

    -string tipoArquivo
    -string nomeArquivo

    void setNomeArquivo(string nomeArquivo)
    void setTypeArquivo(string nomeArquivo)
}

class SQLiteHandler{
    -bool aberto

    -bool alterarTabela(const string& tabela, const string& parametro)
    -bool editarTabela(const string& tabela, const string& parametro)
    -bool excluirTabela(const string& tabela, const string& parametro)

    +bool executarOperacao(Operacao operacao, const string& tabela, const string& parametro)
    
}

class TXTHandler{
    
}

class Operacao{
    <<enumeration>>
    CRIAR_BASE_DADOS=1,
    CRIAR_TABELAS,
    ALTERAR_LINHA,
    EDITAR_LINHA,
    EXCLUIR_LINHA
}

FileHandler <|.. TXTHandler: é um
FileHandler <|.. SQLiteHandler: é um
SQLiteHandler .. Operacao: usa
Pagamento .. FileHandler: salva

```
