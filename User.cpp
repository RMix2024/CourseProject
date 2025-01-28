#include "User.h"
#include <iostream>

User::User() : username(""), password("") {}

User::User(const std::string& username, const std::string& password)
    : username(username), password(password) {
}

bool User::login(const std::string& inputUsername, const std::string& inputPassword) {
    return (username == inputUsername && password == inputPassword);
}

void User::createAccount(const std::string& newUsername, const std::string& newPassword) {
    username = newUsername;
    password = newPassword;
    std::cout << "Account created successfully!" << std::endl;
}

std::string User::getUsername() const {
    return username;
}

void User::setPassword(const std::string& newPassword) {
    password = newPassword;
}
