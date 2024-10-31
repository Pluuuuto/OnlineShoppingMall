// User.cpp
#include "User.h"

User::User(const QString& username, const QString& password)
    : username(username), password(password) {}

bool User::login(const QString& password) {
    return this->password == password;
}

QString User::getUsername() const {
    return username;
}
