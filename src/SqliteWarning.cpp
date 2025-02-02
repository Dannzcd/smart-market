#include "SqliteWarning.hpp"

const char* SqliteWarning::what(){
    return this->msg.c_str();
}

SqliteWarning::SqliteWarning(const std::string msg){
    this->msg = msg;
}