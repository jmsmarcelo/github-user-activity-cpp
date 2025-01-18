#include <iostream>
#include <regex>
#include "../include/api_cli.hpp"
#include "../include/ApiService.hpp"
#include "../include/HttpException.hpp"

ApiService service;
std::string capitalize(const std::string &str) {
    if(str.empty()) return str;
    std::string result = str;
    result[0] = std::toupper(result[0]);
    return result;
}
void print_activity(const Activity &activity) {
    std::string msg = "- ";
    if(activity.type == "CommitCommentEvent") {
        msg +=  "Commented on a commit in " + activity.repo;
    } else if(activity.type == "CreateEvent") {
        msg +=  "Created a " + activity.ref_type +
                " in " + activity.repo;
    } else if(activity.type == "ForkEvent") {
        msg +=  "Forked " + activity.repo;
    } else if(activity.type == "IssuesEvent") {
        msg +=  capitalize(activity.action) + " a issue in " +
                activity.repo;
    } else if(activity.type == "IssueCommentEvent") {
        msg +=  capitalize(activity.action) + " a comment on an issue in "
                + activity.repo;
    } else if(activity.type == "PullRequestEvent") {
        msg +=  capitalize(activity.action) + " a pull request in " +
                activity.repo;
    } else if(activity.type == "PullRequestReviewEvent") {
        msg +=  capitalize(activity.action) + " a pull request review in "
                + activity.repo;
    } else if(activity.type == "PullRequestReviewCommentEvent") {
        msg +=  capitalize(activity.action) + " a pull request review comment in "
                + activity.repo;
    } else if(activity.type == "PushEvent") {
        std::string commit = " commit";
        if(activity.commits > 1) commit += "s";
        msg +=  "Pushed " + std::to_string(activity.commits) + commit +
                " to " + activity.repo;
    } else if(activity.type == "WatchEvent") {
        msg +=  "Starred " + activity.repo;
    } else {
        msg +=  "Performed an unknown activity in " + activity.repo;
    }
    std::cout << msg << '\n';
}
void handle_get_user_activity(const char *username) {
    if(std::regex_search(username, std::regex("^-|-$|[-]{2,}")) ||
        !std::regex_match(username, std::regex("[A-Za-z0-9\\-]{1,39}"))) {
            std::cout << "Invalid username.\n";
            return;
    }
    try {
        service.init_api();
        for(const auto &activity: service.get_user_activity(username)) {
            print_activity(activity);
        }
    } catch(HttpException &e) {
        std::cout << e.what() << '\n';
    }
}
void handle_args_command(const int argc, const char *argv[]) {
    if(argc == 1 || argc > 2) {
        std::cout   << "Usage:      " << argv[0] << " <username>\n"
                    << "Example:    " << argv[0] << " kamranahmedse\n";
        return;
    }
    handle_get_user_activity(argv[1]);
}