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

    setWindowTitle(QStringLiteral("�û���¼"));
    setWindowIcon(QIcon(".\\icons\\logo.png"));
    resize(350, 300);

    QLabel* titleLabel = new QLabel(QStringLiteral("���߹����̳�"), this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold; margin-bottom: 20px;");

    usernameInput = new QLineEdit(this);
    usernameInput->setPlaceholderText(QStringLiteral("�û���"));
    usernameInput->setMinimumHeight(30);

    passwordInput = new QLineEdit(this);
    passwordInput->setPlaceholderText(QStringLiteral("����"));
    passwordInput->setEchoMode(QLineEdit::Password);
    passwordInput->setMinimumHeight(30);

    loginButton = new QPushButton(QStringLiteral("��¼"), this);
    loginButton->setMinimumHeight(35);
    loginButton->setStyleSheet("background-color: #4CAF50; color: white; font-size: 16px;");

    registerButton = new QPushButton(QStringLiteral("ע��"), this);
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
        QMessageBox::critical(this, QStringLiteral("����"), QStringLiteral("�޷����û������ļ�"));
        return;
    }

    QJsonParseError jsonError;
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &jsonError);
    file.close();

    if (jsonError.error != QJsonParseError::NoError || !doc.isObject()) {
        QMessageBox::critical(this, QStringLiteral("����"), QStringLiteral("�û������ļ���ʽ����"));
        return;
    }

    QJsonObject users = doc.object();
    if (users.contains(username) && users[username].toString() == password) {
        emit loginSuccess(username);    // ������¼�ɹ��ź�
        accept();                       // �رնԻ���
    }
    else {
        QMessageBox::warning(this, QStringLiteral("��¼ʧ��"), QStringLiteral("�û������������"));
    }
}

void LoginDialog::handleRegister() {
    emit showRegisterDialog();  // ������ʾע��Ի�����ź�
}
