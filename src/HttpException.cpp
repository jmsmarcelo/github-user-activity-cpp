#include "../include/HttpException.hpp"

HttpException::HttpException(const std::string& msg) : message(msg) {}
const char* HttpException::what() const noexcept {
    return message.c_str();
}