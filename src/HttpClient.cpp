#include "../include/HttpClient.hpp"
#include "../include/HttpException.hpp"

HttpClient::HttpClient(const char *hostName, const char *serviceName):
    host_name(hostName), service_name(serviceName) {
#ifdef _WIN32
        WSADATA wsaData;
        if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            throw HttpException("Error initializing Winsock.");
        }
#endif
}
HttpClient::~HttpClient() {
    if(result != nullptr) freeaddrinfo(result);
    if(ssl_connection != nullptr) SSL_free(ssl_connection);
    if(ssl_context != nullptr) SSL_CTX_free(ssl_context);
    if(tcp_socket != invalid_socket) {
#ifdef _WIN32
        closesocket(tcp_socket);
    }
    WSACleanup();
#else
        close(tcp_socket);
    }
#endif
}
void HttpClient::setup_socket() {
    struct addrinfo hints {};
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    if(getaddrinfo(host_name, service_name, &hints, &result) != 0) {
        throw HttpException("Error resolving host.");
    }
    tcp_socket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if(tcp_socket == invalid_socket) {
        throw HttpException("Error creating socket.");
    }
    if(connect(tcp_socket, result->ai_addr, result->ai_addrlen) != 0) {
        throw HttpException("Error connecting to server.");
    }
    freeaddrinfo(result);
    result = nullptr;
}
void HttpClient::setup_ssl() {
    if(tcp_socket == invalid_socket) {
        throw HttpException("Socket not configured.");
    }
    SSL_library_init();
    SSL_load_error_strings();
    const SSL_METHOD *ssl_method = TLS_client_method();
    ssl_context = SSL_CTX_new(ssl_method);
    if(!ssl_context) {
        throw HttpException("Error creating SSL context.");
    }
    ssl_connection = SSL_new(ssl_context);
    SSL_set_fd(ssl_connection, tcp_socket);
    if(SSL_connect(ssl_connection) <= 0) {
        ERR_print_errors_fp(stderr);
        throw HttpException("Error estabilishing SSL connection.");
    }
}
void HttpClient::ssl_write(const std::string &request) {
    if(tcp_socket == invalid_socket) {
        throw HttpException("Socket not configured.");
    }
    if(!ssl_context || !ssl_connection) {
        throw HttpException("SSL connection not configured.");
    }
    if(int bytes_sent = SSL_write(ssl_connection, request.c_str(), request.size()); bytes_sent <= 0) {
        switch(SSL_get_error(ssl_connection, bytes_sent)) {
            case SSL_ERROR_ZERO_RETURN:
                throw HttpException("SSL connection closed gracefully by the peer.");
            case SSL_ERROR_WANT_WRITE:
            case SSL_ERROR_WANT_READ:
                throw HttpException("SSL_write needs to be retried.");
            case SSL_ERROR_SYSCALL:
                throw HttpException("I/O error occurred during SSL_write.");
            case SSL_ERROR_SSL:
                throw HttpException("A failure in the SSL library occurred.");
            default:
                throw HttpException("An unknown error occurred during SSL_write.");
        }
    }
}
int HttpClient::ssl_read(char *buffer, const int buffer_size) {
    return SSL_read(ssl_connection, buffer, buffer_size);
}