// LoginDialog.h
#pragma once
#include <QDialog>
#include <QLineEdit>

class LoginDialog : public QDialog {
    Q_OBJECT
public:
    explicit LoginDialog(QWidget* parent = nullptr);
    void setUsername(const QString& username);
    void setPassword(const QString& password);

signals:
    void loginSuccess(const QString& username);
    void showRegisterDialog();

private slots:
    void handleLogin();
    void handleRegister();

private:
    QLineEdit* usernameInput;
    QLineEdit* passwordInput;
    QPushButton* loginButton;
    QPushButton* registerButton;
};
