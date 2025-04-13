#ifndef POSTGRESSTORAGE_HPP
#define POSTGRESSTORAGE_HPP

#include "IMessageStorage.hpp"
#include <string>

class PostgresStorage : public IMessageStorage {
public:
    PostgresStorage(const std::string& connStr);
    void save(const std::string& content, const std::string& timestamp) override;

private:
    std::string connStr_;
};

#endif
