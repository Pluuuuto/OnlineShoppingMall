// CartWidget.h
#pragma once
#include "ProductListWidget.h"
#include "ShoppingCart.h"


class CartWidget : public QWidget {
    Q_OBJECT

public:
    explicit CartWidget(ShoppingCart* cart, ProductListWidget* productListWidget, QWidget* parent = nullptr);
    void addProductToCart(Product* product);
    void confirmCheckoutForSingleItem(Product* product);
    void checkoutSelectedItems();
    void toggleSelectAll(bool checked);
    void updateTotalPrice();
    void updateCartTable();
    void removeProductFromCart(Product* product);
    void confirmCheckout();
    void showPaymentQRCode(std::function<void()> onPaymentConfirmed);
    void removeCheckedItemsFromCart();

private:
    QTableWidget* cartTable;
    QCheckBox* selectAllCheckBox;
    QLabel* totalPriceLabel;
    QPushButton* checkoutButton;
    ShoppingCart* shoppingCart;
    ProductListWidget* productListWidget;
};