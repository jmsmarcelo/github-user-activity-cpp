#ifndef HTTP_CLIENT_HPP
#define HTTP_CLIENT_HPP

#include <string>
#include <openssl/ssl3.h>
#include <openssl/err.h>
#ifdef _WIN32
    #include <WinSock2.h>
    #include <WS2tcpip.h>
#else
    #include <sys/socket.h>
    #include <netdb.h>
    #include <unistd.h>
#endif
class HttpClient {
    private:
        const char *host_name;
        const char *service_name;
        struct addrinfo *result {nullptr};
#ifdef _WIN32
        SOCKET tcp_socket = INVALID_SOCKET;
        SOCKET invalid_socket = INVALID_SOCKET;
#else
        int tcp_socket = -1;
        int invalid_socket = -1;
#endif
        SSL_CTX *ssl_context {nullptr};
        SSL *ssl_connection {nullptr};
    public:
        HttpClient(const char *, const char *);
        ~HttpClient();
        void setup_socket();
        void setup_ssl();
        void ssl_write(const std::string &);
        int ssl_read(char *buffer, const int buffer_size);
};

#endif