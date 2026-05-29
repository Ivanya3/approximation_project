/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "graf.h"
#include "slidervv.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    Graf *widget;
    QLabel *labelFormula;
    QFrame *frame;
    SliderVV *sliderDegree;
    SliderVV *sliderPoints;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QComboBox *comboDistribution;
    QCheckBox *checkBox;
    QLabel *label_4;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QLabel *labelError;
    QLabel *labelRMSE;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *btnHand;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1112, 712);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        widget = new Graf(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(0, 20, 1191, 641));
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        widget->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        widget->setAutoFillBackground(false);
        widget->setStyleSheet(QString::fromUtf8("background-color: white;"));
        labelFormula = new QLabel(widget);
        labelFormula->setObjectName("labelFormula");
        labelFormula->setGeometry(QRect(340, 30, 661, 91));
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(labelFormula->sizePolicy().hasHeightForWidth());
        labelFormula->setSizePolicy(sizePolicy1);
        QFont font;
        font.setFamilies({QString::fromUtf8("Montserrat")});
        font.setPointSize(14);
        font.setBold(false);
        font.setItalic(false);
        labelFormula->setFont(font);
        labelFormula->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"border-radius: 30px;\n"
"border: none;\n"
"padding: 8px;"));
        labelFormula->setWordWrap(true);
        frame = new QFrame(widget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 0, 311, 551));
        frame->setStyleSheet(QString::fromUtf8("background-color: white;"));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        sliderDegree = new SliderVV(frame);
        sliderDegree->setObjectName("sliderDegree");
        sliderDegree->setGeometry(QRect(130, 50, 161, 41));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Montserrat")});
        font1.setPointSize(14);
        font1.setBold(false);
        sliderDegree->setFont(font1);
        sliderDegree->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        sliderDegree->setStyleSheet(QString::fromUtf8("QSlider::groove:horizontal {\n"
"    background: #E0E0E0;\n"
"    height: 4px;\n"
"    border-radius: 2px;\n"
"}\n"
"\n"
"QSlider::sub-page:horizontal {\n"
"    background: #100B2B;\n"
"    height: 4px;\n"
"    border-radius: 2px;\n"
"}\n"
"\n"
"QSlider::handle:horizontal {\n"
"    background: #100B2B;\n"
"    border-radius: 7px;\n"
"    width: 14px;\n"
"    height: 14px;\n"
"    margin: -5px 0;\n"
"}"));
        sliderPoints = new SliderVV(frame);
        sliderPoints->setObjectName("sliderPoints");
        sliderPoints->setGeometry(QRect(150, 80, 141, 41));
        sliderPoints->setFont(font1);
        sliderPoints->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        sliderPoints->setMouseTracking(false);
        sliderPoints->setTabletTracking(false);
        sliderPoints->setStyleSheet(QString::fromUtf8("QSlider::groove:horizontal {\n"
"    background: #E0E0E0;\n"
"    height: 4px;\n"
"    border-radius: 2px;\n"
"}\n"
"\n"
"QSlider::sub-page:horizontal {\n"
"    background: #100B2B;\n"
"    height: 4px;\n"
"    border-radius: 2px;\n"
"}\n"
"\n"
"QSlider::handle:horizontal {\n"
"    background: #100B2B;\n"
"    border-radius: 7px;\n"
"    width: 14px;\n"
"    height: 14px;\n"
"    margin: -5px 0;\n"
"}"));
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 30, 104, 78));
        label->setFont(font1);
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 80, 121, 41));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Montserrat")});
        font2.setPointSize(14);
        label_2->setFont(font2);
        label_2->setScaledContents(false);
        label_2->setWordWrap(false);
        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 120, 229, 21));
        label_3->setFont(font2);
        comboDistribution = new QComboBox(frame);
        comboDistribution->setObjectName("comboDistribution");
        comboDistribution->setGeometry(QRect(20, 160, 231, 32));
        comboDistribution->setFont(font2);
        comboDistribution->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        comboDistribution->setStyleSheet(QString::fromUtf8("\n"
"QComboBox {\n"
"    background-color: #100B2B;\n"
"    color: white;\n"
"    border: 1px solid #2A2348;\n"
"    border-radius: 4px;\n"
"    padding: 5px;\n"
"    text-align: center;\n"
"}\n"
"\n"
"QComboBox:hover {\n"
"    background-color: #1A1538;\n"
"}\n"
"\n"
"QComboBox::drop-down {\n"
"    width: 0px;\n"
"    border: none;\n"
"}\n"
"\n"
"QComboBox::down-arrow {\n"
"    width: 0px;\n"
"    height: 0px;\n"
"}\n"
"\n"
"/* \320\241\321\202\320\270\320\273\321\214 \320\262\321\213\320\277\320\260\320\264\320\260\321\216\321\211\320\265\320\263\320\276 \321\201\320\277\320\270\321\201\320\272\320\260 */\n"
"QComboBox QAbstractItemView {\n"
"    background-color: #100B2B;\n"
"    color: white;\n"
"    selection-background-color: #2A2348;\n"
"}"));
        checkBox = new QCheckBox(frame);
        checkBox->setObjectName("checkBox");
        checkBox->setGeometry(QRect(20, 200, 261, 41));
        checkBox->setFont(font2);
        checkBox->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        label_4 = new QLabel(frame);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(20, 5, 171, 41));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Montserrat")});
        font3.setPointSize(14);
        font3.setBold(true);
        label_4->setFont(font3);
        pushButton_2 = new QPushButton(frame);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(40, 410, 221, 31));
        QFont font4;
        font4.setFamilies({QString::fromUtf8("Montserrat")});
        font4.setBold(false);
        pushButton_2->setFont(font4);
        pushButton_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: white;\n"
"    border-radius: 20px !important;\n"
"	overflow: hidden;\n"
"    color: #100B2B;\n"
"    padding: 8px 20px;\n"
"    font-size: 14px;\n"
"    font-weight: normal;\n"
"    border: none;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #F5F5F5;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #E8E8E8;\n"
"}"));
        pushButton = new QPushButton(frame);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(40, 370, 221, 31));
        pushButton->setFont(font4);
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: white;\n"
"    border-radius: 20px !important;\n"
"	overflow: hidden;\n"
"    color: #100B2B;\n"
"    padding: 8px 20px;\n"
"    font-size: 14px;\n"
"    font-weight: normal;\n"
"    border: none;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #F5F5F5;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #E8E8E8;\n"
"}"));
        labelError = new QLabel(frame);
        labelError->setObjectName("labelError");
        labelError->setGeometry(QRect(20, 255, 201, 21));
        labelError->setFont(font2);
        labelRMSE = new QLabel(frame);
        labelRMSE->setObjectName("labelRMSE");
        labelRMSE->setGeometry(QRect(20, 290, 111, 31));
        labelRMSE->setFont(font2);
        pushButton_4 = new QPushButton(frame);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(40, 450, 221, 31));
        pushButton_4->setFont(font4);
        pushButton_4->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: white;\n"
"    border-radius: 20px !important;\n"
"	overflow: hidden;\n"
"    color: #100B2B;\n"
"    padding: 8px 20px;\n"
"    font-size: 14px;\n"
"    font-weight: normal;\n"
"    border: none;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #F5F5F5;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #E8E8E8;\n"
"}"));
        pushButton_5 = new QPushButton(frame);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(40, 490, 221, 31));
        pushButton_5->setFont(font4);
        pushButton_5->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: white;\n"
"    border-radius: 20px !important;\n"
"	overflow: hidden;\n"
"    color: #100B2B;\n"
"    padding: 8px 20px;\n"
"    font-size: 14px;\n"
"    font-weight: normal;\n"
"    border: none;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #F5F5F5;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #E8E8E8;\n"
"}"));
        label->raise();
        label_2->raise();
        label_3->raise();
        comboDistribution->raise();
        checkBox->raise();
        pushButton_2->raise();
        sliderDegree->raise();
        sliderPoints->raise();
        pushButton->raise();
        labelError->raise();
        labelRMSE->raise();
        pushButton_4->raise();
        pushButton_5->raise();
        label_4->raise();
        btnHand = new QPushButton(widget);
        btnHand->setObjectName("btnHand");
        btnHand->setGeometry(QRect(330, 140, 191, 32));
        btnHand->setFont(font4);
        btnHand->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: white;\n"
"    border-radius: 20px !important;\n"
"	overflow: hidden;\n"
"    color: #100B2B;\n"
"    padding: 8px 20px;\n"
"    font-size: 14px;\n"
"    font-weight: normal;\n"
"    border: none;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #F5F5F5;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #E8E8E8;\n"
"}"));
        btnHand->setCheckable(true);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1112, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        labelFormula->setText(QCoreApplication::translate("MainWindow", "\320\244\320\276\321\200\320\274\321\203\320\273\320\260:...", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\265\320\277\320\265\320\275\321\214:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\320\237\320\273\320\276\321\202\320\275\320\276\321\201\321\202\321\214:", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\321\201\320\277\321\200\320\265\320\264\320\265\320\273\320\265\320\275\320\270\320\265:", nullptr));
        checkBox->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\272\320\260\320\267\321\213\320\262\320\260\321\202\321\214 \321\202\320\276\321\207\320\272\320\270", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\321\201\321\202\321\200\320\276\320\270\321\202\321\214", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214", nullptr));
        labelError->setText(QCoreApplication::translate("MainWindow", "\320\234\320\260\320\272\321\201. \320\276\321\210\320\270\320\261\320\272\320\260: --", nullptr));
        labelRMSE->setText(QCoreApplication::translate("MainWindow", "RMSE: --", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "\320\234\320\260\321\202\321\201\321\202\320\260\321\202", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "\320\230\320\274\320\277\320\276\321\200\321\202", nullptr));
        btnHand->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\321\205\320\262\320\260\321\202 \320\276\320\261\320\273\320\260\321\201\321\202\320\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
