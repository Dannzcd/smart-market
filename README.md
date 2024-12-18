# Estacionamento
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

## Tarifas por veículo
- Carro comum: R$ 5,60 a hora e R$ 50 para regime de 12 horas. Diária a partir de R$ 90.
- Carro esportivo: R$ 8,60 a hora e R$ 80 para regime de 12 horas. Diária a partir de R$ 130.
- Moto: R$ 3,60 a hora e R$ 36 para regime de 12 horas. Diária a partir de R$ 60.

## Desconto para empresas
Para cada 5 veículos estacionados sob um regime previamente determinado, a tarifa por veículo diminui 1.5%

## Vagas disponíveis:
Para cada andar, com 500m² e 70% do terreno de área útil para vagas, temos:

- 21 vagas para carros por andar
- 7 vagas para motos por andar