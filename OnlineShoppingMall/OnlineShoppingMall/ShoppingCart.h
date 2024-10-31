// ShoppingCart.h
#pragma once
#include <QMap>
#include <QMessageBox>
#include "Product.h"
#include "ProductListWidget.h"

class ShoppingCart {
public:
    ShoppingCart(ProductListWidget* productListWidget);
    QMap<Product*, int> getItems() const;
    bool addProduct(Product* product, int quantity);
    double getTotalPrice() const;
    int getQuantity(Product* product) const;
    void removeProduct(Product* product);
    void clear();

private:
    QMap<Product*, int> cartContents;
    ProductListWidget* productListWidget;
};
