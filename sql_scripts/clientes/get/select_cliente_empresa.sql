SELECT CLIENTES.id_cliente, CLIENTES.nome, CLIENTES_EMPRESA.cnpj  FROM CLIENTES
INNER JOIN CLIENTES_EMPRESA
ON CLIENTES.id_cliente = CLIENTES_EMPRESA.id_cliente
WHERE CLIENTES.id_cliente = ?;