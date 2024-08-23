#pragma once
#include <string>

class Server {
public:
    void start();
private:
    void processClientRequest(int client_socket);
    std::string fetchVerse(const std::string& verse, const std::string& translation);
};
