#pragma once
#ifndef USER_H
#define USER_H

#include <string>

class User {
private:
    std::string username;
    std::string password;

public:
    User(); // Default constructor
    User(const std::string& username, const std::string& password); // Parameterized constructor

    bool login(const std::string& inputUsername, const std::string& inputPassword);
    void createAccount(const std::string& newUsername, const std::string& newPassword);
    std::string getUsername() const;
    void setPassword(const std::string& newPassword);
};

#endif // USER_H

