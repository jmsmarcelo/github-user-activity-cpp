#include <iostream>
#include <regex>
#include "../include/api_cli.hpp"

void handle_get_user_activity(const char *username) {
    if(std::regex_search(username, std::regex("^-|-$|[-]{2,}")) ||
        !std::regex_match(username, std::regex("[A-Za-z0-9\\-]{1,39}"))) {
            std::cout << "Invalid username.\n";
            return;
    }
}
void handle_args_command(const int argc, const char *argv[]) {
    if(argc == 1 || argc > 2) {
        std::cout   << "Invalid command.\n"
                    << "    Usage:      <username>\n"
                    << "    Example:    kamranahmedse\n";
        return;
    }
    handle_get_user_activity(argv[1]);
}