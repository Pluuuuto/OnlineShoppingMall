#include "Product.h"

Product::Product(const QString& name, double price, int stock, const QString& category, const QString& unit, const QString& iconPath)
    : name(name), price(price), stock(stock), category(category), unit(unit), icon(QIcon(iconPath)) {}

QString Product::getName() const { return name; }
QString Product::getCategory() const { return category; }
QString Product::getUnit() const { return unit; }
QIcon Product::getIcon() const { return icon; }
double Product::getPrice() const { return price; }
int Product::getStock() const { return stock; }

// ���¿�棺�ɹ����ٿ�淵�� true����治�㷵�� false
bool Product::updateStock(int quantity) {
    if (stock >= quantity) {
        stock -= quantity;
        return true;
    }
    return false;
}

bool Product::decreaseStock(int quantity) {
    if (quantity > stock) {
        return false; // ��治��
    }
    stock -= quantity;
    return true;
}

void Product::increaseStock(int quantity) {
    stock += quantity;
}
