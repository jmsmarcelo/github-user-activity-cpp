#include <regex>
#include "../include/ApiClient.hpp"
#include "../include/HttpException.hpp"

ApiClient::ApiClient(): httpClient(host_name.c_str(), service_name) {}
void ApiClient::init_https() {
    httpClient.setup_socket();
    httpClient.setup_ssl();
}
std::string ApiClient::get_request(const std::string &username) {
    return
        "GET /users/" + username + "/events HTTP/1.1\r\n"
        "Host: " + host_name + "\r\n"
        "User-Agent: JMSClient/1.0\r\n"
        "Accept: application/vnd.github+json\r\n"
        "X-GitHub-Api-Version: 2022-11-28\r\n"
        "Connection: close\r\n\r\n";
}
std::vector<std::string> ApiClient::get_user_events(const std::string &username) {
    httpClient.ssl_write(get_request(username));
    const int buffer_size = 4096;
    char buffer[buffer_size];
    int bytes_received;
    std::string response;
    std::string http_version;
    unsigned int status_code;
    std::string status_message;
    std::smatch match;
    while((bytes_received = httpClient.ssl_read(buffer, buffer_size - 1)) > 0) {
        buffer[bytes_received] = '\0';
        response += buffer;
        if(std::regex_search(response, match, std::regex("(HTTP/.*) (\\d{3}) (.*)\r\n"))) {
            http_version = match.str(1);
            status_code = std::stoi(match.str(2));
            status_message = match.str(3);
            response = match.suffix().str();
            break;
        } else {
            throw HttpException("Invalid response.");
        }
    }
    if(bytes_received < 0) {
        throw HttpException("Error reading from SSL connection.");
    }
    switch(status_code) {
        case 200:
            break;
        case 404:
            throw HttpException(username + " " + status_message);
        default:
            throw HttpException(status_message);
    }
    std::vector<std::string> events {};
    while((bytes_received = httpClient.ssl_read(buffer, buffer_size - 1)) > 0) {
        buffer[bytes_received] = '\0';
        response += buffer;
        while(std::regex_search(response, match, std::regex(R"::((\{"id":".*?\})(?:(?:,(\{"id":"))|\]$))::"))) {
            events.push_back(match.str(1));
            response = match.str(2) + match.suffix().str();
        }
    }
    return events;
}