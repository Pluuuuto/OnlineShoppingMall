// ShoppingCart.cpp
#include "ShoppingCart.h"
#include <QDebug>

ShoppingCart::ShoppingCart(ProductListWidget* productListWidget)
    : productListWidget(productListWidget) {}

QMap<Product*, int> ShoppingCart::getItems() const {
    return cartContents;
}

bool ShoppingCart::addProduct(Product* product, int quantity) {
    int currentQuantity = cartContents.value(product, 0);

    if (quantity < 0) {
        if (currentQuantity + quantity < 0) {
            return false;
        }
        cartContents[product] += quantity;
        product->increaseStock(-quantity);
        return true;
    }

    if (currentQuantity + quantity > product->getStock()) {
        QMessageBox msgBox;
        msgBox.setWindowTitle(QStringLiteral("库存不足"));
        msgBox.setText(QStringLiteral("无法添加商品“%1”，库存不足！").arg(product->getName()));
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowIcon(QIcon(".\\icons\\logo.png"));
        msgBox.exec();
        return false;
    }

    cartContents[product] += quantity;
    product->decreaseStock(quantity);
    return true;
}


double ShoppingCart::getTotalPrice() const {
    double total = 0.0;
    for (auto it = cartContents.begin(); it != cartContents.end(); ++it) {
        total += it.key()->getPrice() * it.value();
    }
    return total;
}

int ShoppingCart::getQuantity(Product* product) const {
    return cartContents.value(product, 0);
}

void ShoppingCart::removeProduct(Product* product) {
    if (cartContents.contains(product)) {
        int quantity = cartContents[product];
        product->updateStock(quantity);
        cartContents.remove(product);
    }
}

void ShoppingCart::clear() {
    for (auto it = cartContents.begin(); it != cartContents.end(); ++it) {
        Product* product = it.key();
        int quantity = it.value();
        product->updateStock(quantity);
    }
    cartContents.clear();
}
