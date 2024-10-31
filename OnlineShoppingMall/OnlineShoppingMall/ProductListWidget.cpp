#include "ProductListWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QPushButton>
#include <QHeaderView>
#include <QIcon>

ProductListWidget::ProductListWidget(QWidget* parent)
    : QWidget(parent), productTable(new QTableWidget(this)), searchInput(new QLineEdit(this)) {

    searchInput->setPlaceholderText(QStringLiteral("������Ʒ"));
    searchButton = new QPushButton(QStringLiteral("����"), this);

    // ʹ��ˮƽ���ֽ��������������ť����һ��
    QHBoxLayout* searchLayout = new QHBoxLayout;
    searchLayout->addWidget(searchInput);
    searchLayout->addWidget(searchButton);

    connect(searchButton, &QPushButton::clicked, this, &ProductListWidget::searchProduct);

    // ������
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addLayout(searchLayout);  // ��ˮƽ������ӵ�������
    layout->addWidget(productTable);
    setLayout(layout);

    // ���ñ��������ͱ���
    productTable->setColumnCount(5);  // ����Ϊ5����ͼ�����Ʒ���Ʒ���ͬһ��
    productTable->setHorizontalHeaderLabels({ QStringLiteral("��Ʒ����"), QStringLiteral("���"), QStringLiteral("�۸�"), QStringLiteral("��λ"), QStringLiteral("����") });
    productTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    productTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // ���ñ���п��Զ�����
    productTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    productTable->horizontalHeader()->setSectionResizeMode(4, QHeaderView::ResizeToContents);

    initializeProductList();
    loadProductsToTable();
}

void ProductListWidget::initializeProductList() {
    products = {
        new Product(QStringLiteral("ƻ�� iPhone 16 Pro Max"), 12999.0, 10, QStringLiteral("���Ӳ�Ʒ"), QStringLiteral("��"), ".\\icons\\iphone.jpg"),
        new Product(QStringLiteral("��Ϊ MateBook X Pro"), 8999.0, 5, QStringLiteral("���Ӳ�Ʒ"), QStringLiteral("̨"),".\\icons\\huawei.png"),
        new Product(QStringLiteral("���� Galaxy Tab S7"), 4999.0, 15, QStringLiteral("���Ӳ�Ʒ"), QStringLiteral("̨"),".\\icons\\Galaxy.jpg"),
        new Product(QStringLiteral("���� WH-1000XM4 ����"), 1999.0, 30, QStringLiteral("���Ӳ�Ʒ"), QStringLiteral("��"),".\\icons\\Sony.png"),

        new Product(QStringLiteral("�����ֵ綯��ˢ"), 299.0, 50, QStringLiteral("���˻���"), QStringLiteral("֧"),".\\icons\\Philips.jpg"),
        new Product(QStringLiteral("���µ紵��"), 399.0, 40, QStringLiteral("���˻���"), QStringLiteral("̨"),".\\icons\\songxia.png"),

        new Product(QStringLiteral("�˼�����"), 599.0, 20, QStringLiteral("�Ҿ�"), QStringLiteral("��"),".\\icons\\yijia.jpg"),
        new Product(QStringLiteral("�칫��"), 299.0, 25, QStringLiteral("�Ҿ�"), QStringLiteral("��"),".\\icons\\bangongyi.jpg"),
        new Product(QStringLiteral("����ɳ��"), 1999.0, 8, QStringLiteral("�Ҿ�"), QStringLiteral("��"),".\\icons\\sanrenshafa.jpg"),
        new Product(QStringLiteral("ʵľ�¹�"), 3999.0, 5, QStringLiteral("�Ҿ�"), QStringLiteral("��"),".\\icons\\yigui.jpg"),

        new Product(QStringLiteral("С��ɨ�ػ�����"), 1599.0, 10, QStringLiteral("���õ���"), QStringLiteral("̨"),".\\icons\\xiaomi-robot.jpg"),
        new Product(QStringLiteral("���Ŀյ�"), 2999.0, 12, QStringLiteral("���õ���"), QStringLiteral("̨"),".\\icons\\Midea.jpg"),
        new Product(QStringLiteral("��������"), 3599.0, 6, QStringLiteral("���õ���"), QStringLiteral("̨"),".\\icons\\Haier.png"),

        new Product(QStringLiteral("�������������ϵͳ��"), 89.0, 100, QStringLiteral("�鼮"), QStringLiteral("��"),".\\icons\\ComputerSystem.jpg"),
        new Product(QStringLiteral("��C++ Primer��"), 99.0, 80, QStringLiteral("�鼮"), QStringLiteral("��"),".\\icons\\c++Primer.jpg"),
        new Product(QStringLiteral("���㷨���ۡ�"), 120.0, 60, QStringLiteral("�鼮"), QStringLiteral("��"),".\\icons\\algorithm.jpg"),
        new Product(QStringLiteral("A4��ӡֽ"), 30.0, 200, QStringLiteral("�칫��Ʒ"), QStringLiteral("��"),".\\icons\\printPaper.jpg"),
        new Product(QStringLiteral("���Ա�"), 5.0, 500, QStringLiteral("�칫��Ʒ"), QStringLiteral("֧"),".\\icons\\pen.jpg"),
        new Product(QStringLiteral("�ļ���"), 15.0, 150, QStringLiteral("�칫��Ʒ"), QStringLiteral("��"),".\\icons\\folder.jpg"),

        new Product(QStringLiteral("���ܵ������"), 5999.0, 10, QStringLiteral("��Ӱ����"), QStringLiteral("̨"),".\\icons\\Canon.jpg")

    };
}

void ProductListWidget::loadProductsToTable() {
    productTable->setRowCount(0);

    for (Product* product : products) {
        int row = productTable->rowCount();
        productTable->insertRow(row);

        // ��ͼ�����Ʒ���Ʒ���ͬһ����Ԫ����
        QTableWidgetItem* nameItem = new QTableWidgetItem(product->getIcon(), product->getName());
        productTable->setItem(row, 0, nameItem);  // ��0������Ʒ���ƣ���ͼ�꣩

        productTable->setItem(row, 1, new QTableWidgetItem(product->getCategory()));
        productTable->setItem(row, 2, new QTableWidgetItem(QString::number(product->getPrice())));
        productTable->setItem(row, 3, new QTableWidgetItem(product->getUnit()));

        // ���ò����еļ��빺�ﳵ��ť
        QPushButton* addButton = new QPushButton(QStringLiteral("���빺�ﳵ"), this);
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

            // ��ʾͼ�����Ʒ������ͬһ��
            QTableWidgetItem* nameItem = new QTableWidgetItem(product->getIcon(), product->getName());
            productTable->setItem(row, 0, nameItem);

            productTable->setItem(row, 1, new QTableWidgetItem(product->getCategory()));
            productTable->setItem(row, 2, new QTableWidgetItem(QString::number(product->getPrice())));
            productTable->setItem(row, 3, new QTableWidgetItem(product->getUnit()));

            QPushButton* addButton = new QPushButton(QStringLiteral("���빺�ﳵ"), this);
            connect(addButton, &QPushButton::clicked, this, [=]() { emit productSelected(product); });
            productTable->setCellWidget(row, 4, addButton);
        }
    }

    if (productTable->rowCount() == 0) {
        QMessageBox::information(this, QStringLiteral("�������"), QStringLiteral("δ�ҵ�ƥ�����Ʒ��"));
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
