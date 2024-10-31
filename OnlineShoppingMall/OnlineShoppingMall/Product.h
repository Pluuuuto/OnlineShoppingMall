// Product.h
#pragma once
#include <QString>
#include <QIcon>

class Product {
public:
    Product(const QString& name, double price, int stock, const QString& category, const QString& unit, const QString& iconPath);

    QString getName() const;
    QString getCategory() const;
    QString getUnit() const;
    QIcon getIcon() const;
    double getPrice() const;
    int getStock() const;
    bool updateStock(int quantity); 
    bool decreaseStock(int quantity);
    void increaseStock(int quantity);

private:
    QString name;
    double price;
    int stock;
    QString category;
    QString unit;
    QIcon icon;
};

