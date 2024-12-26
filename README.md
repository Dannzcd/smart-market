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
    -unsigned numeroVagasPorAndar
    -unsigned numeroAndares
    -double faturamentoBruto
    -double totalImpostos
    -double faturamentoLiquido
    -double lucro

    +string getNome()
    +string getCnpj()
    +unsigned getNumeroVagasPorAndar()
    +unsigned getNumeroAndares()
    +double getFaturamentoBruto()
    +double getFaturamentoLiquido()
    +double getLucro()
}

Supermercado *.. "1..n" Funcionario: tem

class Produto{
    -string nome
    -string marca
    -
}

class Pagamento{
    -string metodo
    -double valorTotal

    Pagamento(string metodo, double tarifa)
    
    -void fazerRelatorioPagamento()
    -bool ehValido()
    +void fazerPagamento(double &faturamentoBruto)
}

class Cliente{
    <<interface>>
    -time_t dataDeEntrada;
    -time_t dataDeSaida;
    -double tarifaTotal

    +double getTarifaTotal()
    +void setTarifaTotal(double tarifaTotal)
    +unsigned getHorasGastas()
}

class ClienteEmpresa{
    -List~Veiculo*~ veiculos
    -double desconto

    static +double getTarifaReal()
}

class ClienteCivil{
    -Veiculo veiculo
}

Cliente <|-- ClienteEmpresa: é um
Cliente <|-- ClienteCivil: é um

ClienteCivil <.. "1..1" Veiculo: tem

Supermercado o.. Cliente

class Veiculo{
    -string marca
    -string modelo
    -string ano
    -void setAno()

    +string getMarca()
    +string getModelo()
    +string getAno()
}

Supermercado o.. "0..n" Veiculo: aloca

class Contabilidade{
    static -double calcularImpostosTrabalhistas(List~Funcionario*~ *funcionarios)
    static -double calcularImpostosEstataisFaturamento(double &faturamento)
    static +double calcularImpostosSobFaturamento()
    static +double calcularImpostosSobTerreno()
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
    CRIAR=1
    ALTERAR
    EDITAR
    EXCLUIR
}

FileHandler <|.. TXTHandler: é um
FileHandler <|.. SQLiteHandler: é um
SQLiteHandler .. Operacao: usa
Pagamento .. FileHandler: salva

```