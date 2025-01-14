import random

# Função para formatar o CPF
def gerar_cpf():
    cpf = ''.join([str(random.randint(0, 9)) for _ in range(11)])
    return f"{cpf[:3]}.{cpf[3:6]}.{cpf[6:9]}-{cpf[9:]}"

# Função para formatar o CNPJ
def gerar_cnpj():
    cnpj = ''.join([str(random.randint(0, 9)) for _ in range(14)])
    return f"{cnpj[:2]}.{cnpj[2:5]}.{cnpj[5:8]}/{cnpj[8:12]}-{cnpj[12:]}"

# Gerando o arquivo SQL com as 160 novas instâncias para cada entidade
sql_lines = []

# CLIENTES
for i in range(4, 164):
    sql_lines.append(f"INSERT INTO CLIENTES (nome) VALUES ('Cliente_{i:06}');")

# CLIENTES_CIVIL (com CPF formatado)
for i in range(1, 164):
    cpf = gerar_cpf()
    sql_lines.append(f"INSERT INTO CLIENTES_CIVIL (id_cliente, cpf) VALUES ({i}, '{cpf}');")

# CLIENTES_EMPRESA (com CNPJ formatado)
for i in range(1, 164):
    cnpj = gerar_cnpj()
    sql_lines.append(f"INSERT INTO CLIENTES_EMPRESA (id_cliente, cnpj) VALUES ({i}, '{cnpj}');")

# SUPERMERCADOS
for i in range(1, 164):
    sql_lines.append(f"INSERT INTO SUPERMERCADOS (cnpj, faturamento_bruto, total_impostos, faturamento_liquido, lucro) VALUES ('11.111.111/0001-0{i:02}', {100000 * i:.2f}, {15000 * i:.2f}, {85000 * i:.2f}, {10000 * i:.2f});")

# FUNCIONARIOS
for i in range(1, 164):
    cpf = gerar_cpf()
    sql_lines.append(f"INSERT INTO FUNCIONARIOS (nome, sobrenome, cpf, salario_bruto, salario_liquido) VALUES ('Funcionario_{i:03}', 'Sobrenome_{i:03}', '{cpf}', {3000 + (i % 10) * 500:.2f}, {2500 + (i % 10) * 500:.2f});")

# MARCAS
for i in range(1, 164):
    sql_lines.append(f"INSERT INTO MARCAS (nome) VALUES ('Marca_{i:03}');")

# TIPOS_PRODUTO
for i in range(1, 164):
    sql_lines.append(f"INSERT INTO TIPOS_PRODUTO (nome) VALUES ('Tipo_{i:03}');")

# PRODUTOS
for i in range(1, 164):
    sql_lines.append(f"INSERT INTO PRODUTOS (nome, id_marca, id_tipo, peso_liquido, preco_unitario, unidades_disponiveis) VALUES ('Produto_{i:03}', {i % 50 + 1}, {i % 50 + 1}, {1.0 + (i % 5) * 0.5:.2f}, {10 + (i % 10) * 5:.2f}, {100 + (i % 5) * 20});")

# VENDAS
for i in range(1, 164):
    sql_lines.append(f"INSERT INTO VENDAS (id_cliente, descricao, data_venda) VALUES ({i}, 'Venda de teste {i}', '2023-01-{i % 31 + 1:02}');")

# ITENS_VENDA
for i in range(1, 164):
    sql_lines.append(f"INSERT INTO ITENS_VENDA (id_venda, id_produto, quantidade, preco_unitario, valor_total) VALUES ({i}, {i % 50 + 1}, {i % 5 + 1}, {10 + (i % 10) * 5:.2f}, {(i % 5 + 1) * (10 + (i % 10) * 5):.2f});")

# Salvar o SQL em um arquivo
with open("insert_data_formatted.sql", "w") as file:
    file.write("\n".join(sql_lines))
