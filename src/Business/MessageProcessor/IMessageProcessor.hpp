#ifndef IMESSAGEPROCESSOR_HPP
#define IMESSAGEPROCESSOR_HPP

#include <string>

class IMessageProcessor {
public:
    virtual ~IMessageProcessor() = default;
    virtual std::string process(const std::string& message) = 0;
};

#endif
