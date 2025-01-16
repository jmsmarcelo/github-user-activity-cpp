#ifndef HTTP_EXCEPTION_HPP
#define HTTP_EXCEPTION_HPP

#include <exception>
#include <string>

class HttpException: public std::exception {
    private:
        const char *msg;
    public:
        explicit HttpException(const char *);
        const char* what() const noexcept override;
};

#endif