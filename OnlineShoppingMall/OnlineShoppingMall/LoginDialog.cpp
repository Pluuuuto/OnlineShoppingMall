// LoginDialog.cpp
#include "LoginDialog.h"
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

LoginDialog::LoginDialog(QWidget* parent)
    : QDialog(parent) {

    setWindowTitle(QStringLiteral("用户登录"));
    setWindowIcon(QIcon(".\\icons\\logo.png"));
    resize(350, 300);

    QLabel* titleLabel = new QLabel(QStringLiteral("在线购物商城"), this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold; margin-bottom: 20px;");

    usernameInput = new QLineEdit(this);
    usernameInput->setPlaceholderText(QStringLiteral("用户名"));
    usernameInput->setMinimumHeight(30);

    passwordInput = new QLineEdit(this);
    passwordInput->setPlaceholderText(QStringLiteral("密码"));
    passwordInput->setEchoMode(QLineEdit::Password);
    passwordInput->setMinimumHeight(30);

    loginButton = new QPushButton(QStringLiteral("登录"), this);
    loginButton->setMinimumHeight(35);
    loginButton->setStyleSheet("background-color: #4CAF50; color: white; font-size: 16px;");

    registerButton = new QPushButton(QStringLiteral("注册"), this);
    registerButton->setMinimumHeight(35);
    registerButton->setStyleSheet("font-size: 16px;");

    connect(loginButton, &QPushButton::clicked, this, &LoginDialog::handleLogin);
    connect(registerButton, &QPushButton::clicked, this, &LoginDialog::handleRegister);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(titleLabel);
    layout->addWidget(usernameInput);
    layout->addWidget(passwordInput);
    layout->addSpacing(10);
    layout->addWidget(loginButton);
    layout->addWidget(registerButton);

    setLayout(layout);
}

void LoginDialog::setUsername(const QString& username) {
    usernameInput->setText(username);
}

void LoginDialog::setPassword(const QString& password) {
    passwordInput->setText(password);
}

void LoginDialog::handleLogin() {
    QString username = usernameInput->text();
    QString password = passwordInput->text();

    QFile file("users.json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, QStringLiteral("错误"), QStringLiteral("无法打开用户数据文件"));
        return;
    }

    QJsonParseError jsonError;
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &jsonError);
    file.close();

    if (jsonError.error != QJsonParseError::NoError || !doc.isObject()) {
        QMessageBox::critical(this, QStringLiteral("错误"), QStringLiteral("用户数据文件格式错误"));
        return;
    }

    QJsonObject users = doc.object();
    if (users.contains(username) && users[username].toString() == password) {
        emit loginSuccess(username);    // 发出登录成功信号
        accept();                       // 关闭对话框
    }
    else {
        QMessageBox::warning(this, QStringLiteral("登录失败"), QStringLiteral("用户名或密码错误"));
    }
}

void LoginDialog::handleRegister() {
    emit showRegisterDialog();  // 发出显示注册对话框的信号
}
