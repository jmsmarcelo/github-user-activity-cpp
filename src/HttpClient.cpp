#include "../include/HttpClient.hpp"

HttpClient::HttpClient(const char *hostName, const char *serviceName):
    host_name(hostName), service_name(serviceName) {}