CREATE TABLE IF NOT EXISTS CLIENTES(
    id_cliente INTEGER PRIMARY KEY AUTOINCREMENT,
    nome TEXT NOT NULL
);

CREATE TABLE IF NOT EXISTS CLIENTES_CIVIL(
    id_cliente_civil INTEGER PRIMARY KEY AUTOINCREMENT,
    id_cliente INTEGER,
    FOREIGN KEY (id_cliente) REFERENCES CLIENTES(id_cliente)
);

CREATE TABLE IF NOT EXISTS CLIENTES(
    id_cliente INTEGER PRIMARY KEY AUTOINCREMENT,
    nome VARCHAR(50) NOT NULL
);

CREATE TABLE IF NOT EXISTS CLIENTES_CIVIL(
    id_cliente_civil INTEGER PRIMARY KEY AUTOINCREMENT, 
    id_cliente INTEGER, 
    FOREIGN KEY (id_cliente) REFERENCES CLIENTES(id_cliente)
);

CREATE TABLE IF NOT EXISTS CLIENTES_EMPRESA(
    id_cliente_empresa INTEGER PRIMARY KEY AUTOINCREMENT, 
    id_cliente INTEGER, 
    FOREIGN KEY (id_cliente) REFERENCES CLIENTES(id_cliente)
);

CREATE TABLE IF NOT EXISTS SUPERMERCADOS(
    id_estacionamento INTEGER PRIMARY KEY AUTOINCREMENT, 
    cnpj VARCHAR(15) NOT NULL UNIQUE, 
    faturamento_bruto FLOAT, 
    total_impostos FLOAT, 
    faturamento_liquido FLOAT, 
    lucro FLOAT
);