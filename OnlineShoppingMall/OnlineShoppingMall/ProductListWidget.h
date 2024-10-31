// ProductListWidget.h
#pragma once
#include "Product.h"
#include <QWidget>
#include <QTableWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QList>

class ProductListWidget : public QWidget {
    Q_OBJECT

public:
    explicit ProductListWidget(QWidget* parent = nullptr);
    Product* getProductByName(const QString& name) const;
    void searchProduct();
    void initializeProductList();
    void loadProductsToTable();

signals:
    void productSelected(Product* product);

private:
    QTableWidget* productTable;
    QLineEdit* searchInput;
    QPushButton* searchButton;
    QList<Product*> products;
};

