#pragma once
#include <string>

class User
{
public:
    void searchVerse(const std::string &verse, const std::string &translation);

private:
    void connectToServer();
    void sendRequestToServer(const std::string &request);
    std::string receiveResponseFromServer();
};
