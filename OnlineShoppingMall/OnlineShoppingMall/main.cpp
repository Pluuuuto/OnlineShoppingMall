#include <QApplication>
#include "MainWindow.h"
#include "LoginDialog.h"
#include "RegisterDialog.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    LoginDialog loginDialog;
    RegisterDialog registerDialog;

    QObject::connect(&loginDialog, &LoginDialog::showRegisterDialog, [&]() {
        if (registerDialog.exec() == QDialog::Accepted) {
            loginDialog.setUsername(registerDialog.getUsername());
            loginDialog.setPassword(registerDialog.getPassword());
        }
        });

    if (loginDialog.exec() == QDialog::Accepted) {
        MainWindow mainWindow;
        mainWindow.show();
        return app.exec();
    }

    return 0;
}
