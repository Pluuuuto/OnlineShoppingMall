// CartWidget.cpp
#include "CartWidget.h"
#include <QWidget>
#include <QLabel>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QPushButton>
#include <QCheckBox>
#include <QMessageBox>
#include <QSpinBox>


CartWidget::CartWidget(ShoppingCart* cart, ProductListWidget* productListWidget, QWidget* parent)
    : QWidget(parent), shoppingCart(cart), productListWidget(productListWidget) {

    // 初始化购物车表格
    cartTable = new QTableWidget(this);
    cartTable->setColumnCount(8);  // 增加一列用于“单独结算”按钮
    cartTable->setHorizontalHeaderLabels({ QStringLiteral("选择"), QStringLiteral("商品名称"), QStringLiteral("类别"), QStringLiteral("价格"), QStringLiteral("数量"), QStringLiteral("总价"), QStringLiteral("操作"), QStringLiteral("单独结算") });
    cartTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    cartTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    cartTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // 全选复选框
    selectAllCheckBox = new QCheckBox(QStringLiteral("全选"), this);
    connect(selectAllCheckBox, &QCheckBox::stateChanged, this, &CartWidget::toggleSelectAll);

    // 总价标签
    totalPriceLabel = new QLabel(QStringLiteral("合计：0.00 RMB"), this);

    // 结算按钮
    checkoutButton = new QPushButton(QStringLiteral("结算"), this);
    checkoutButton->setIcon(QIcon(".\\icons\\checkout.png"));
    connect(checkoutButton, &QPushButton::clicked, this, &CartWidget::confirmCheckout);

    // 布局管理
    QVBoxLayout* mainLayout = new QVBoxLayout;
    QHBoxLayout* footerLayout = new QHBoxLayout;
    footerLayout->addWidget(selectAllCheckBox);
    footerLayout->addStretch();
    footerLayout->addWidget(totalPriceLabel);
    footerLayout->addWidget(checkoutButton);

    mainLayout->addWidget(cartTable);
    mainLayout->addLayout(footerLayout);
    setLayout(mainLayout);

    updateCartTable();
}

void CartWidget::addProductToCart(Product* product) {
    int quantityToAdd = 1; 
    if (shoppingCart->addProduct(product, quantityToAdd)) {
        updateCartTable(); 
        updateTotalPrice(); 
    }
}

void CartWidget::updateCartTable() {
    cartTable->setRowCount(0);
    const auto& items = shoppingCart->getItems();

    for (auto it = items.begin(); it != items.end(); ++it) {
        Product* product = it.key();
        int quantity = it.value();
        double price = product->getPrice();
        double total = price * quantity;

        int row = cartTable->rowCount();
        cartTable->insertRow(row);

        // 设置复选框
        QCheckBox* checkBox = new QCheckBox(this);
        QWidget* checkBoxWidget = new QWidget(this);
        QHBoxLayout* checkBoxLayout = new QHBoxLayout(checkBoxWidget);
        checkBoxLayout->addWidget(checkBox);
        checkBoxLayout->setAlignment(Qt::AlignCenter);
        checkBoxLayout->setContentsMargins(0, 0, 0, 0);
        cartTable->setCellWidget(row, 0, checkBoxWidget);
        connect(checkBox, &QCheckBox::stateChanged, this, &CartWidget::updateTotalPrice);

        // 商品信息列设置
        cartTable->setItem(row, 1, new QTableWidgetItem(product->getName()));
        cartTable->setItem(row, 2, new QTableWidgetItem(product->getCategory()));
        cartTable->setItem(row, 3, new QTableWidgetItem(QString::number(price, 'f', 2)));

        // 数量 `QSpinBox` 控件
        QSpinBox* quantitySpinBox = new QSpinBox(this);
        quantitySpinBox->setRange(1, product->getStock());
        quantitySpinBox->setValue(quantity);
        cartTable->setCellWidget(row, 4, quantitySpinBox);

        // 设置总价列
        QTableWidgetItem* totalItem = new QTableWidgetItem(QString::number(total, 'f', 2));
        cartTable->setItem(row, 5, totalItem);

        // 当数量发生变化时，更新总价和合计价格
        connect(quantitySpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int newQuantity) {
            int diff = newQuantity - shoppingCart->getQuantity(product);

            // 更新购物车中的数量
            if (shoppingCart->addProduct(product, diff)) {
                double newTotal = product->getPrice() * newQuantity;
                totalItem->setText(QString::number(newTotal, 'f', 2)); // 更新该行的总价显示
                updateTotalPrice(); // 更新合计价格
            }
            else {
                quantitySpinBox->setValue(shoppingCart->getQuantity(product)); // 恢复原来的数量
            }
            });

        // 删除按钮
        QPushButton* deleteButton = new QPushButton(QStringLiteral("删除"), this);
        connect(deleteButton, &QPushButton::clicked, this, [=]() { removeProductFromCart(product); });
        cartTable->setCellWidget(row, 6, deleteButton);

        // 单独结算按钮
        QPushButton* singleCheckoutButton = new QPushButton(QStringLiteral("单独结算"), this);
        connect(singleCheckoutButton, &QPushButton::clicked, this, [=]() { confirmCheckoutForSingleItem(product); });
        cartTable->setCellWidget(row, 7, singleCheckoutButton);
    }

    updateTotalPrice(); // 更新合计价格
}


void CartWidget::removeProductFromCart(Product* product) {
    shoppingCart->removeProduct(product);  // 从购物车中移除商品
    updateCartTable();                     // 更新表格
    updateTotalPrice();                    // 更新总价
}

void CartWidget::confirmCheckoutForSingleItem(Product* product) {
    int quantity = shoppingCart->getItems().value(product, 0);
    if (quantity > 0) {
        double total = product->getPrice() * quantity;
        QString confirmationText = QStringLiteral("您选择结算的商品是：\n") +
            product->getName() +
            QStringLiteral("\n数量：") + QString::number(quantity) +
            QStringLiteral("\n总金额：") + QString::number(total, 'f', 2) +
            QStringLiteral(" RMB\n\n确认结算吗？");

        // 弹出确认对话框
        int result = QMessageBox::question(this, QStringLiteral("确认单独结算"), confirmationText, QMessageBox::Yes | QMessageBox::No);
        if (result == QMessageBox::Yes) {
            // 用户确认后，显示付款二维码并等待用户点击“已扫码”
            showPaymentQRCode([=]() {
                // 回调函数：用户点击“已扫码”后执行的逻辑
                shoppingCart->removeProduct(product);
                updateCartTable();
                updateTotalPrice();
                QMessageBox::information(this, QStringLiteral("结算成功"),
                    QStringLiteral("已结算商品：") + product->getName() +
                    QStringLiteral("\n总金额：") + QString::number(total, 'f', 2) + QStringLiteral(" RMB"));
                });
        }
    }
}

void CartWidget::showPaymentQRCode(std::function<void()> onPaymentConfirmed) {
    QDialog* paymentDialog = new QDialog(this);
    paymentDialog->setWindowTitle(QStringLiteral("请扫码付款"));
    paymentDialog->setFixedSize(300, 350);

    // 显示二维码图片
    QLabel* qrLabel = new QLabel(paymentDialog);
    qrLabel->setPixmap(QPixmap(".\\icons\\payment_qr.jpg").scaled(300, 300, Qt::KeepAspectRatio));
    qrLabel->setAlignment(Qt::AlignCenter);

    // “已扫码”按钮
    QPushButton* confirmButton = new QPushButton(QStringLiteral("已扫码"), paymentDialog);
    confirmButton->setFixedSize(100, 30);
    connect(confirmButton, &QPushButton::clicked, paymentDialog, [=]() {
        paymentDialog->accept();  // 关闭二维码对话框
        if (onPaymentConfirmed) {
            onPaymentConfirmed();  // 执行回调函数，完成结算逻辑
        }
        });

    // 布局
    QVBoxLayout* layout = new QVBoxLayout(paymentDialog);
    layout->addWidget(qrLabel);
    layout->addWidget(confirmButton, 0, Qt::AlignCenter);

    paymentDialog->exec();  // 显示对话框并等待用户交互
}

// 新增的辅助函数，用于从购物车中删除已结算的商品行
void CartWidget::removeCheckedItemsFromCart() {
    QList<int> rowsToDelete;  // 用于保存需要删除的行
    for (int row = cartTable->rowCount() - 1; row >= 0; --row) {
        QCheckBox* checkBox = qobject_cast<QCheckBox*>(cartTable->cellWidget(row, 0)->findChild<QCheckBox*>());
        if (checkBox && checkBox->isChecked()) {
            QString productName = cartTable->item(row, 1)->text();
            Product* product = productListWidget->getProductByName(productName);
            if (product) {
                shoppingCart->removeProduct(product);  // 从购物车逻辑中删除
                rowsToDelete.append(row);  // 将该行标记为待删除
            }
        }
    }

    // 从表格中删除已标记的行
    for (int row : rowsToDelete) {
        cartTable->removeRow(row);
    }

    updateTotalPrice();  // 更新总价显示
}

// KKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK
void CartWidget::confirmCheckout() {
    double total = 0.0;
    QStringList checkedProducts;

    // 遍历选中的商品，计算总价并显示商品列表
    for (int row = 0; row < cartTable->rowCount(); ++row) {
        QCheckBox* checkBox = qobject_cast<QCheckBox*>(cartTable->cellWidget(row, 0)->findChild<QCheckBox*>());
        if (checkBox && checkBox->isChecked()) {
            QString productName = cartTable->item(row, 1)->text();
            double productPrice = cartTable->item(row, 5)->text().toDouble();
            checkedProducts.append(productName + " - " + QString::number(productPrice, 'f', 2) + " RMB");
            total += productPrice;
        }
    }

    if (checkedProducts.isEmpty()) {
        QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("请选择要结算的商品！"));
        return;
    }

    QString confirmationText = QStringLiteral("已选商品：\n") + checkedProducts.join("\n") +
        QStringLiteral("\n总金额：") + QString::number(total, 'f', 2) + QStringLiteral(" RMB\n\n确认结算吗？");

    // 弹出确认对话框
    int result = QMessageBox::question(this, QStringLiteral("确认结算"), confirmationText, QMessageBox::Yes | QMessageBox::No);
    if (result == QMessageBox::Yes) {
        // 用户确认后，显示付款二维码并等待用户点击“已扫码”
        showPaymentQRCode([this, checkedProducts, total]() {
            // 回调函数：用户点击“已扫码”后执行的逻辑
            removeCheckedItemsFromCart();  // 清除购物车中已结算的商品行
            QMessageBox::information(this, QStringLiteral("结算成功"),
                QStringLiteral("已结算商品：\n") + checkedProducts.join("\n") +
                QStringLiteral("\n总金额：") + QString::number(total, 'f', 2) + QStringLiteral(" RMB"));
            });
    }
}

void CartWidget::toggleSelectAll(bool checked) {
    for (int i = 0; i < cartTable->rowCount(); ++i) {
        QCheckBox* selectBox = qobject_cast<QCheckBox*>(cartTable->cellWidget(i, 0)->findChild<QCheckBox*>());
        if (selectBox) {
            selectBox->setChecked(checked);
        }
    }
    updateTotalPrice();
}

void CartWidget::updateTotalPrice() {
    double totalPrice = 0.0;

    for (int i = 0; i < cartTable->rowCount(); ++i) {
        QCheckBox* selectBox = qobject_cast<QCheckBox*>(cartTable->cellWidget(i, 0)->findChild<QCheckBox*>());
        if (selectBox && selectBox->isChecked()) {
            double itemTotalPrice = cartTable->item(i, 5)->text().toDouble();
            totalPrice += itemTotalPrice;
        }
    }
    totalPriceLabel->setText(QStringLiteral("合计：%1 RMB").arg(totalPrice, 0, 'f', 2));
}

void CartWidget::checkoutSelectedItems() {
    double total = 0.0;
    QStringList checkedProducts;

    QList<Product*> productsToRemove; // 需要结算的商品列表

    // 遍历购物车表格，记录选中的商品
    for (int row = cartTable->rowCount() - 1; row >= 0; --row) {
        QCheckBox* checkBox = qobject_cast<QCheckBox*>(cartTable->cellWidget(row, 0)->findChild<QCheckBox*>());
        if (checkBox && checkBox->isChecked()) {
            QString productName = cartTable->item(row, 1)->text();
            Product* product = productListWidget->getProductByName(productName);

            if (product) {
                int quantity = cartTable->item(row, 4)->text().toInt();
                double price = product->getPrice() * quantity;
                checkedProducts.append(productName + " - " + QString::number(price, 'f', 2) + " RMB");
                total += price;
                productsToRemove.append(product); // 将该商品添加到待结算列表中
            }
        }
    }

    if (checkedProducts.isEmpty()) {
        QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("请选择要结算的商品！"));
        return;
    }

    // 确认支付对话框
    QString confirmationText = QStringLiteral("已选商品：\n") + checkedProducts.join("\n") +
        QStringLiteral("\n总金额：") + QString::number(total, 'f', 2) + QStringLiteral(" RMB\n\n确认支付吗？");

    int result = QMessageBox::question(this, QStringLiteral("确认支付"), confirmationText, QMessageBox::Yes | QMessageBox::No);
    if (result == QMessageBox::Yes) {
        // 支付成功，删除购物车中的已结算商品
        for (Product* product : productsToRemove) {
            shoppingCart->removeProduct(product); // 从购物车中删除
        }
        updateCartTable(); // 刷新购物车表格
        QMessageBox::information(this, QStringLiteral("支付成功"), QStringLiteral("您已成功支付！"));
    }
    else {
        QMessageBox::information(this, QStringLiteral("支付取消"), QStringLiteral("支付已取消，商品库存已恢复。"));
    }
}