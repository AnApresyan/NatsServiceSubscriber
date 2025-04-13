#ifndef IMESSAGESTORAGE_HPP
#define IMESSAGESTORAGE_HPP

#include <string>

class IMessageStorage {
public:
    virtual ~IMessageStorage() = default;
    virtual void save(const std::string& content, const std::string& timestamp) = 0;
};

#endif
