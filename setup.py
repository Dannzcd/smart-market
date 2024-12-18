import os
import sys

SUBDIRS = ["programa","db"]
MAKE_DIRS = ["obj"]

def criar_todos_subdiretorios(dir:str) -> int:
    qtd_inexistentes = 0
    
    for subdir in SUBDIRS:
        if not(os.path.exists(dir+"/"+subdir)):
            qtd_inexistentes += 1
            print("CRIANDO [%s]" % (dir+"/"+subdir))
            os.mkdir(dir+"/"+subdir)

    return qtd_inexistentes

def main(nomePastaSaida:str):
    num = 0

    if (not os.path.exists(nomePastaSaida)):
        print("A pasta de saida não existe\n")
        os.mkdir(nomePastaSaida)

    else:
        print("A pasta de saída %s já existe\n" % (nomePastaSaida))

    num = criar_todos_subdiretorios(nomePastaSaida)

    for makedir in MAKE_DIRS:
        if (not os.path.exists(makedir)):
            print("CRIANDO DIRETORIO PARA O MAKE [%s]" % (makedir))
            os.mkdir(makedir)
            num += 1

    print(str(num) + " pastas criadas!") if num != 0 else print("Todas as pastas de saída existentes criadas!")

if __name__ == "__main__":
    if (len(sys.argv) == 2):
        main(sys.argv[1])
    else:
        main("output")