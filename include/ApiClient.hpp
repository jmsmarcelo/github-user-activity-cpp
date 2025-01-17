#ifndef API_CLIENT_HPP
#define API_CLIENT_HPP

#include <string>
#include <vector>
#include "../include/HttpClient.hpp"

class ApiClient {
    private:
        const std::string host_name = "api.github.com";
        const char *service_name = "https";
        HttpClient httpClient;
        std::string get_request(const std::string &);
    public:
        ApiClient();
        void init_https();
        std::vector<std::string> get_user_events(const std::string &);
};

#endif