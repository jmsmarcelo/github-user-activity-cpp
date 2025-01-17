#ifndef HTTP_EXCEPTION_HPP
#define HTTP_EXCEPTION_HPP

#include <exception>
#include <string>

class HttpException: public std::exception {
    private:
        std::string message;
    public:
        explicit HttpException(const std::string&);
        const char* what() const noexcept override;
};

#endif