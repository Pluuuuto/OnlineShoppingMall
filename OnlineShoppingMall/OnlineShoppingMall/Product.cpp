#include "Product.h"

Product::Product(const QString& name, double price, int stock, const QString& category, const QString& unit, const QString& iconPath)
    : name(name), price(price), stock(stock), category(category), unit(unit), icon(QIcon(iconPath)) {}

QString Product::getName() const { return name; }
QString Product::getCategory() const { return category; }
QString Product::getUnit() const { return unit; }
QIcon Product::getIcon() const { return icon; }
double Product::getPrice() const { return price; }
int Product::getStock() const { return stock; }

// 更新库存：成功减少库存返回 true，库存不足返回 false
bool Product::updateStock(int quantity) {
    if (stock >= quantity) {
        stock -= quantity;
        return true;
    }
    return false;
}

bool Product::decreaseStock(int quantity) {
    if (quantity > stock) {
        return false; // 库存不足
    }
    stock -= quantity;
    return true;
}

void Product::increaseStock(int quantity) {
    stock += quantity;
}
