#include "ProductListWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QPushButton>
#include <QHeaderView>
#include <QIcon>

ProductListWidget::ProductListWidget(QWidget* parent)
    : QWidget(parent), productTable(new QTableWidget(this)), searchInput(new QLineEdit(this)) {

    searchInput->setPlaceholderText(QStringLiteral("搜索商品"));
    searchButton = new QPushButton(QStringLiteral("搜索"), this);

    // 使用水平布局将搜索框和搜索按钮放在一行
    QHBoxLayout* searchLayout = new QHBoxLayout;
    searchLayout->addWidget(searchInput);
    searchLayout->addWidget(searchButton);

    connect(searchButton, &QPushButton::clicked, this, &ProductListWidget::searchProduct);

    // 主布局
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addLayout(searchLayout);  // 将水平布局添加到主布局
    layout->addWidget(productTable);
    setLayout(layout);

    // 设置表格的列数和标题
    productTable->setColumnCount(5);  // 列数为5，将图标和商品名称放在同一列
    productTable->setHorizontalHeaderLabels({ QStringLiteral("商品名称"), QStringLiteral("类别"), QStringLiteral("价格"), QStringLiteral("单位"), QStringLiteral("操作") });
    productTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    productTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // 设置表格列宽自动填满
    productTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    productTable->horizontalHeader()->setSectionResizeMode(4, QHeaderView::ResizeToContents);

    initializeProductList();
    loadProductsToTable();
}

void ProductListWidget::initializeProductList() {
    products = {
        new Product(QStringLiteral("苹果 iPhone 16 Pro Max"), 12999.0, 10, QStringLiteral("电子产品"), QStringLiteral("部"), ".\\icons\\iphone.jpg"),
        new Product(QStringLiteral("华为 MateBook X Pro"), 8999.0, 5, QStringLiteral("电子产品"), QStringLiteral("台"),".\\icons\\huawei.png"),
        new Product(QStringLiteral("三星 Galaxy Tab S7"), 4999.0, 15, QStringLiteral("电子产品"), QStringLiteral("台"),".\\icons\\Galaxy.jpg"),
        new Product(QStringLiteral("索尼 WH-1000XM4 耳机"), 1999.0, 30, QStringLiteral("电子产品"), QStringLiteral("副"),".\\icons\\Sony.png"),

        new Product(QStringLiteral("飞利浦电动牙刷"), 299.0, 50, QStringLiteral("个人护理"), QStringLiteral("支"),".\\icons\\Philips.jpg"),
        new Product(QStringLiteral("松下电吹风"), 399.0, 40, QStringLiteral("个人护理"), QStringLiteral("台"),".\\icons\\songxia.png"),

        new Product(QStringLiteral("宜家书桌"), 599.0, 20, QStringLiteral("家具"), QStringLiteral("张"),".\\icons\\yijia.jpg"),
        new Product(QStringLiteral("办公椅"), 299.0, 25, QStringLiteral("家具"), QStringLiteral("把"),".\\icons\\bangongyi.jpg"),
        new Product(QStringLiteral("三人沙发"), 1999.0, 8, QStringLiteral("家具"), QStringLiteral("套"),".\\icons\\sanrenshafa.jpg"),
        new Product(QStringLiteral("实木衣柜"), 3999.0, 5, QStringLiteral("家具"), QStringLiteral("个"),".\\icons\\yigui.jpg"),

        new Product(QStringLiteral("小米扫地机器人"), 1599.0, 10, QStringLiteral("家用电器"), QStringLiteral("台"),".\\icons\\xiaomi-robot.jpg"),
        new Product(QStringLiteral("美的空调"), 2999.0, 12, QStringLiteral("家用电器"), QStringLiteral("台"),".\\icons\\Midea.jpg"),
        new Product(QStringLiteral("海尔冰箱"), 3599.0, 6, QStringLiteral("家用电器"), QStringLiteral("台"),".\\icons\\Haier.png"),

        new Product(QStringLiteral("《深入理解计算机系统》"), 89.0, 100, QStringLiteral("书籍"), QStringLiteral("本"),".\\icons\\ComputerSystem.jpg"),
        new Product(QStringLiteral("《C++ Primer》"), 99.0, 80, QStringLiteral("书籍"), QStringLiteral("本"),".\\icons\\c++Primer.jpg"),
        new Product(QStringLiteral("《算法导论》"), 120.0, 60, QStringLiteral("书籍"), QStringLiteral("本"),".\\icons\\algorithm.jpg"),
        new Product(QStringLiteral("A4打印纸"), 30.0, 200, QStringLiteral("办公用品"), QStringLiteral("包"),".\\icons\\printPaper.jpg"),
        new Product(QStringLiteral("中性笔"), 5.0, 500, QStringLiteral("办公用品"), QStringLiteral("支"),".\\icons\\pen.jpg"),
        new Product(QStringLiteral("文件夹"), 15.0, 150, QStringLiteral("办公用品"), QStringLiteral("个"),".\\icons\\folder.jpg"),

        new Product(QStringLiteral("佳能单反相机"), 5999.0, 10, QStringLiteral("摄影器材"), QStringLiteral("台"),".\\icons\\Canon.jpg")

    };
}

void ProductListWidget::loadProductsToTable() {
    productTable->setRowCount(0);

    for (Product* product : products) {
        int row = productTable->rowCount();
        productTable->insertRow(row);

        // 将图标和商品名称放在同一个单元格中
        QTableWidgetItem* nameItem = new QTableWidgetItem(product->getIcon(), product->getName());
        productTable->setItem(row, 0, nameItem);  // 第0列是商品名称（带图标）

        productTable->setItem(row, 1, new QTableWidgetItem(product->getCategory()));
        productTable->setItem(row, 2, new QTableWidgetItem(QString::number(product->getPrice())));
        productTable->setItem(row, 3, new QTableWidgetItem(product->getUnit()));

        // 设置操作列的加入购物车按钮
        QPushButton* addButton = new QPushButton(QStringLiteral("加入购物车"), this);
        connect(addButton, &QPushButton::clicked, this, [=]() { emit productSelected(product); });
        productTable->setCellWidget(row, 4, addButton);
    }
}

void ProductListWidget::searchProduct() {
    QString keyword = searchInput->text().trimmed();
    productTable->setRowCount(0);

    for (Product* product : products) {
        if (product->getName().contains(keyword, Qt::CaseInsensitive)) {
            int row = productTable->rowCount();
            productTable->insertRow(row);

            // 显示图标和商品名称在同一列
            QTableWidgetItem* nameItem = new QTableWidgetItem(product->getIcon(), product->getName());
            productTable->setItem(row, 0, nameItem);

            productTable->setItem(row, 1, new QTableWidgetItem(product->getCategory()));
            productTable->setItem(row, 2, new QTableWidgetItem(QString::number(product->getPrice())));
            productTable->setItem(row, 3, new QTableWidgetItem(product->getUnit()));

            QPushButton* addButton = new QPushButton(QStringLiteral("加入购物车"), this);
            connect(addButton, &QPushButton::clicked, this, [=]() { emit productSelected(product); });
            productTable->setCellWidget(row, 4, addButton);
        }
    }

    if (productTable->rowCount() == 0) {
        QMessageBox::information(this, QStringLiteral("搜索结果"), QStringLiteral("未找到匹配的商品。"));
    }
}

Product* ProductListWidget::getProductByName(const QString& name) const {
    for (Product* product : products) {
        if (product->getName() == name) {
            return product;
        }
    }
    return nullptr;
}
