// RegisterDialog.cpp
#include "RegisterDialog.h"

RegisterDialog::RegisterDialog(QWidget* parent) : QDialog(parent) {
    setWindowTitle(QStringLiteral("�û�ע��"));
    resize(350, 250);

    QLabel* titleLabel = new QLabel(QStringLiteral("ע�����û�"), this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold; margin-bottom: 20px;");

    usernameInput = new QLineEdit(this);
    usernameInput->setPlaceholderText(QStringLiteral("�û���"));
    usernameInput->setMinimumHeight(30);

    passwordInput = new QLineEdit(this);
    passwordInput->setPlaceholderText(QStringLiteral("����"));
    passwordInput->setEchoMode(QLineEdit::Password);
    passwordInput->setMinimumHeight(30);

    confirmPasswordInput = new QLineEdit(this);
    confirmPasswordInput->setPlaceholderText(QStringLiteral("ȷ������"));
    confirmPasswordInput->setEchoMode(QLineEdit::Password);
    confirmPasswordInput->setMinimumHeight(30);

    registerButton = new QPushButton(QStringLiteral("ע��"), this);
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
        QMessageBox::warning(this, QStringLiteral("ע��ʧ��"), QStringLiteral("����д�����ֶ�"));
        return;
    }

    if (password != confirmPassword) {
        QMessageBox::warning(this, QStringLiteral("ע��ʧ��"), QStringLiteral("���벻һ��"));
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
        QMessageBox::warning(this, QStringLiteral("ע��ʧ��"), QStringLiteral("�û����Ѵ��ڣ���ѡ�������û���"));
        return;
    }

    users[username] = password;

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QJsonDocument doc(users);
        file.write(doc.toJson());
        file.close();
    }

    QMessageBox::information(this, QStringLiteral("ע��ɹ�"), QStringLiteral("�û�ע��ɹ���"));
    accept();  // �رնԻ���
}
