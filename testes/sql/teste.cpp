#include <iostream>
#include <sqlite3.h>

int main(){
    sqlite3 *db;
    int retorno;

    retorno = sqlite3_open("teste.sqlite3", &db);

    retorno = sqlite3_exec(db, "DELETE FROM MARCAS WHERE id_marca = 3;", nullptr, nullptr, nullptr);
    if (retorno != SQLITE_OK){
        std::cout << "aaa" << std::endl;
    }

    return 0;
}