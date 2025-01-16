#include "../include/HttpException.hpp"

HttpException::HttpException(const char *message): msg(message) {}
const char *HttpException::what() const noexcept {
    return msg;
}