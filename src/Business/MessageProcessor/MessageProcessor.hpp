#ifndef MESSAGEPROCESSOR_HPP
#define MESSAGEPROCESSOR_HPP

#include "IMessageProcessor.hpp"

class MessageProcessor : public IMessageProcessor {
public:
    std::string process(const std::string& message) override;
};

#endif
