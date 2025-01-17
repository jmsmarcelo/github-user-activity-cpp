#include <regex>
#include "../include/Service.hpp"

void Service::init_api() {
    ApiClient.init_https();
}
std::vector<Activity> Service::get_user_activity(const std::string &username) {
    std::vector<Activity> activities;
    std::smatch match;
    for(const auto &event: ApiClient.get_user_events(username)) {
        Activity activity{};
        if(std::regex_search(event, match, std::regex(R"::("type":"(.*?)",".*?"repo":.*?"name":"(.*?)",")::"))) {
            activity.type = match.str(1);
            activity.repo = match.str(2);
        }
        if(std::regex_search(event, match, std::regex(R"::("payload":\{(.*)\},"public")::"))) {
            std::string payload = match.str(1);
            if(std::regex_search(payload, match, std::regex(R"::("action":"(.*?)",")::"))) {
                activity.action = match.str(1);
            }
            if(std::regex_search(payload, match, std::regex(R"::("ref_type":"(.*?)",")::"))) {
                activity.ref_type = match.str(1);
            }
            if(std::regex_search(payload, match, std::regex(R"::("commits":\[(.*?)\}\])::"))) {
                std::string commits = match.str(1);
                while(std::regex_search(commits, match, std::regex(R"::("sha":".*?",")::"))) {
                    commits = match.suffix().str();
                    activity.commits++;
                }
            }
        }
        activities.push_back(activity);
    }
    return activities;
}