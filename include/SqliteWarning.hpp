#pragma once

#include <stdexcept>
#include <string>

class SqliteWarning : public std::exception{
    std::string msg;

    public:
        SqliteWarning(const std::string msg);
        const char *what();

};