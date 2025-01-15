#ifndef HTTP_CLIENT_HPP
#define HTTP_CLIENT_HPP

class HttpClient {
    private:
        const char *host_name;
        const char *service_name;
    public:
        HttpClient(const char *, const char *);
};

#endif