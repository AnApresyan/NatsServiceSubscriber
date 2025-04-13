#include "MessageProcessor.hpp"
#include <algorithm>
#include <cctype>
#include <sstream>

std::string MessageProcessor::process(const std::string& message) {
    std::string result = message;

    result.erase(result.begin(), std::find_if(result.begin(), result.end(),
        [](unsigned char ch) { return !std::isspace(ch); }));

    result.erase(std::find_if(result.rbegin(), result.rend(),
        [](unsigned char ch) { return !std::isspace(ch); }).base(), result.end());

    return result;
}
