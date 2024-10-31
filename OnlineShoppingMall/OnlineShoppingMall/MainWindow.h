// MainWindow.h
#pragma once

#include <QMainWindow>
#include "ProductListWidget.h"
#include "CartWidget.h"
#include "ShoppingCart.h"


class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

private:
    ProductListWidget* productListWidget;
    CartWidget* cartWidget;
    ShoppingCart* shoppingCart;
};

