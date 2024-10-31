/********************************************************************************
** Form generated from reading UI file 'OnlineShoppingMall.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ONLINESHOPPINGMALL_H
#define UI_ONLINESHOPPINGMALL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OnlineShoppingMallClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *OnlineShoppingMallClass)
    {
        if (OnlineShoppingMallClass->objectName().isEmpty())
            OnlineShoppingMallClass->setObjectName(QString::fromUtf8("OnlineShoppingMallClass"));
        OnlineShoppingMallClass->resize(600, 400);
        menuBar = new QMenuBar(OnlineShoppingMallClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        OnlineShoppingMallClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(OnlineShoppingMallClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        OnlineShoppingMallClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(OnlineShoppingMallClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        OnlineShoppingMallClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(OnlineShoppingMallClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        OnlineShoppingMallClass->setStatusBar(statusBar);

        retranslateUi(OnlineShoppingMallClass);

        QMetaObject::connectSlotsByName(OnlineShoppingMallClass);
    } // setupUi

    void retranslateUi(QMainWindow *OnlineShoppingMallClass)
    {
        OnlineShoppingMallClass->setWindowTitle(QCoreApplication::translate("OnlineShoppingMallClass", "OnlineShoppingMall", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OnlineShoppingMallClass: public Ui_OnlineShoppingMallClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ONLINESHOPPINGMALL_H
