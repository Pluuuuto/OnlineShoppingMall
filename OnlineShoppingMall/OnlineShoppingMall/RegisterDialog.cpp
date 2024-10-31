// RegisterDialog.cpp
#include "RegisterDialog.h"

RegisterDialog::RegisterDialog(QWidget* parent) : QDialog(parent) {
    setWindowTitle(QStringLiteral("用户注册"));
    resize(350, 250);

    QLabel* titleLabel = new QLabel(QStringLiteral("注册新用户"), this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold; margin-bottom: 20px;");

    usernameInput = new QLineEdit(this);
    usernameInput->setPlaceholderText(QStringLiteral("用户名"));
    usernameInput->setMinimumHeight(30);

    passwordInput = new QLineEdit(this);
    passwordInput->setPlaceholderText(QStringLiteral("密码"));
    passwordInput->setEchoMode(QLineEdit::Password);
    passwordInput->setMinimumHeight(30);

    confirmPasswordInput = new QLineEdit(this);
    confirmPasswordInput->setPlaceholderText(QStringLiteral("确认密码"));
    confirmPasswordInput->setEchoMode(QLineEdit::Password);
    confirmPasswordInput->setMinimumHeight(30);

    registerButton = new QPushButton(QStringLiteral("注册"), this);
    registerButton->setMinimumHeight(35);
    registerButton->setStyleSheet("background-color: #4CAF50; color: white; font-size: 16px;");

    connect(registerButton, &QPushButton::clicked, this, &RegisterDialog::handleRegister);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(titleLabel);
    layout->addWidget(usernameInput);
    layout->addWidget(passwordInput);
    layout->addWidget(confirmPasswordInput);
    layout->addSpacing(10);
    layout->addWidget(registerButton);

    setLayout(layout);
}

void RegisterDialog::handleRegister() {
    QString username = usernameInput->text();
    QString password = passwordInput->text();
    QString confirmPassword = confirmPasswordInput->text();

    if (username.isEmpty() || password.isEmpty() || confirmPassword.isEmpty()) {
        QMessageBox::warning(this, QStringLiteral("注册失败"), QStringLiteral("请填写所有字段"));
        return;
    }

    if (password != confirmPassword) {
        QMessageBox::warning(this, QStringLiteral("注册失败"), QStringLiteral("密码不一致"));
        return;
    }

    QFile file("users.json");
    QJsonObject users;

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QJsonParseError jsonError;
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &jsonError);
        if (jsonError.error == QJsonParseError::NoError && doc.isObject()) {
            users = doc.object();
        }
        file.close();
    }

    if (users.contains(username)) {
        QMessageBox::warning(this, QStringLiteral("注册失败"), QStringLiteral("用户名已存在，请选择其他用户名"));
        return;
    }

    users[username] = password;

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QJsonDocument doc(users);
        file.write(doc.toJson());
        file.close();
    }

    QMessageBox::information(this, QStringLiteral("注册成功"), QStringLiteral("用户注册成功！"));
    accept();  // 关闭对话框
}
