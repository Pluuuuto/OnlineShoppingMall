// User.h
#pragma once
#include <QString>
#include <QVector>

class User {
public:
    User(const QString& username, const QString& password);
    bool login(const QString& password);
    QString getUsername() const;

private:
    QString username;
    QString password;
};
