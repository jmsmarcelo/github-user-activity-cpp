#ifndef SERVICE_HPP
#define SERVICE_HPP

#include <string>
#include <vector>
#include "../include/ApiClient.hpp"

struct Activity {
    std::string type, repo, action, ref_type;
    int commits {0};
};
class Service {
    private:
        ApiClient apiClient;
    public:
        void init_api();
        std::vector<Activity> get_user_activity(const std::string &);
};

#endif