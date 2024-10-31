// MainWindow.cpp
#include "MainWindow.h"
#include <QTabWidget>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent) {

    setWindowTitle(QStringLiteral("���߹����̳�"));
    setWindowIcon(QIcon(".\\icons\\logo.png"));
    resize(1000, 600);

    productListWidget = new ProductListWidget(this);
    shoppingCart = new ShoppingCart(productListWidget);
    cartWidget = new CartWidget(shoppingCart, productListWidget, this);

    connect(productListWidget, &ProductListWidget::productSelected, cartWidget, &CartWidget::addProductToCart);

    QTabWidget* tabWidget = new QTabWidget(this);
    tabWidget->addTab(productListWidget, QStringLiteral("��Ʒ�б�"));
    tabWidget->addTab(cartWidget, QStringLiteral("���ﳵ"));

    setCentralWidget(tabWidget);
}
