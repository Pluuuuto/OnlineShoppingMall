// MainWindow.cpp
#include "MainWindow.h"
#include <QTabWidget>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent) {

    setWindowTitle(QStringLiteral("在线购物商城"));
    setWindowIcon(QIcon(".\\icons\\logo.png"));
    resize(1000, 600);

    productListWidget = new ProductListWidget(this);
    shoppingCart = new ShoppingCart(productListWidget);
    cartWidget = new CartWidget(shoppingCart, productListWidget, this);

    connect(productListWidget, &ProductListWidget::productSelected, cartWidget, &CartWidget::addProductToCart);

    QTabWidget* tabWidget = new QTabWidget(this);
    tabWidget->addTab(productListWidget, QStringLiteral("商品列表"));
    tabWidget->addTab(cartWidget, QStringLiteral("购物车"));

    setCentralWidget(tabWidget);
}
