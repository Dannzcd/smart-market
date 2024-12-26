import os
import sys
import shutil

ENV_DIRS = {
    "programa": [],
    "db": [],
    "constantes": ["comandos_sql", "tabelas_sql"]
}

MAKE_DIRS = ["obj", "output"]

def delete_dirs(outputdirname:str) -> bool:
    if (os.path.exists(outputdirname)):
        shutil.rmtree(outputdirname)
        return True
    
    return False

COMMANDS = {
    "delete": delete_dirs
}

def criar_todos_envdirs(outputdir:str) -> int:
    qtd_criados = 0
    
    for diretorio in ENV_DIRS.keys():
        if (not os.path.exists(outputdir+"/"+diretorio)):
            print("CRIANDO [%s]" % (diretorio))
            os.mkdir(outputdir+"/"+diretorio)
            qtd_criados += 1

            print("Subdiretorios de %s: %s" % (diretorio, ENV_DIRS[diretorio]))

            if (len(ENV_DIRS[diretorio]) > 0):
                for subdiretorio in ENV_DIRS[diretorio]:
                    if (not os.path.exists(outputdir+"/"+diretorio+"/"+subdiretorio)):
                        os.mkdir(outputdir+"/"+diretorio+"/"+subdiretorio)
                        qtd_criados += 1            

    return qtd_criados

def criar_todos_makedirs():
    qtd_criados = 0

    for makedir in MAKE_DIRS:
        if (not os.path.exists(makedir)):
            print("CRIANDO [%s]" % (makedir))
            os.mkdir(makedir)
            qtd_criados += 1

    return qtd_criados

def main(nomePastaSaida:str):
    num = 0

    if (not os.path.exists(nomePastaSaida)):
        print("A pasta de saida não existe\n")
        os.mkdir(nomePastaSaida)

    else:
        print("A pasta de saída %s já existe\n" % (nomePastaSaida))

    num += criar_todos_envdirs(nomePastaSaida)
    num += criar_todos_makedirs()

    print(str(num) + " pastas criadas!") if num != 0 else print("Todas as pastas de saída existentes criadas!")

if __name__ == "__main__":
    if (len(sys.argv) > 1):
        for makedir in MAKE_DIRS:
            if (COMMANDS[sys.argv[1]](makedir)):
                print("Pasta %s excluida com sucesso!" % (sys.argv[1]))

    else:
        main("output")