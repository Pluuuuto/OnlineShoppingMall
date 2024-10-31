#pragma once

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QTextStream>
#include <QLabel> 

class RegisterDialog : public QDialog {
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget* parent = nullptr);

    QString getUsername() const { return usernameInput->text(); }
    QString getPassword() const { return passwordInput->text(); }

signals:
    void registerSuccess(const QString& username, const QString& password);

private slots:
    void handleRegister();

private:
    QLineEdit* usernameInput;
    QLineEdit* passwordInput;
    QLineEdit* confirmPasswordInput;
    QPushButton* registerButton;
};
