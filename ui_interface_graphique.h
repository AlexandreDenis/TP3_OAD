/********************************************************************************
** Form generated from reading UI file 'interface_graphique.ui'
**
** Created: Sun Dec 29 18:54:40 2013
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTERFACE_GRAPHIQUE_H
#define UI_INTERFACE_GRAPHIQUE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGraphicsView>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_interface_graphique_2
{
public:
    QGraphicsView *interface_graphique;
    QPushButton *afficher_graphe;
    QPushButton *client;
    QSpinBox *spinBox;
    QPushButton *savings;
    QPushButton *insertion;
    QLabel *dist_tot;
    QPushButton *deux_opt;
    QPushButton *shift;
    QPushButton *mult;
    QSpinBox *spinBox_2;
    QPushButton *infosTournees;

    void setupUi(QWidget *interface_graphique_2)
    {
        if (interface_graphique_2->objectName().isEmpty())
            interface_graphique_2->setObjectName(QString::fromUtf8("interface_graphique_2"));
        interface_graphique_2->resize(1300, 617);
        interface_graphique = new QGraphicsView(interface_graphique_2);
        interface_graphique->setObjectName(QString::fromUtf8("interface_graphique"));
        interface_graphique->setGeometry(QRect(25, 21, 1161, 501));
        afficher_graphe = new QPushButton(interface_graphique_2);
        afficher_graphe->setObjectName(QString::fromUtf8("afficher_graphe"));
        afficher_graphe->setGeometry(QRect(340, 550, 141, 27));
        client = new QPushButton(interface_graphique_2);
        client->setObjectName(QString::fromUtf8("client"));
        client->setGeometry(QRect(1190, 50, 101, 27));
        spinBox = new QSpinBox(interface_graphique_2);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setGeometry(QRect(1190, 20, 101, 26));
        savings = new QPushButton(interface_graphique_2);
        savings->setObjectName(QString::fromUtf8("savings"));
        savings->setGeometry(QRect(1200, 200, 92, 27));
        insertion = new QPushButton(interface_graphique_2);
        insertion->setObjectName(QString::fromUtf8("insertion"));
        insertion->setGeometry(QRect(1200, 230, 91, 27));
        dist_tot = new QLabel(interface_graphique_2);
        dist_tot->setObjectName(QString::fromUtf8("dist_tot"));
        dist_tot->setGeometry(QRect(820, 550, 471, 61));
        deux_opt = new QPushButton(interface_graphique_2);
        deux_opt->setObjectName(QString::fromUtf8("deux_opt"));
        deux_opt->setGeometry(QRect(1200, 260, 91, 27));
        shift = new QPushButton(interface_graphique_2);
        shift->setObjectName(QString::fromUtf8("shift"));
        shift->setGeometry(QRect(1200, 290, 92, 27));
        mult = new QPushButton(interface_graphique_2);
        mult->setObjectName(QString::fromUtf8("mult"));
        mult->setGeometry(QRect(1200, 320, 91, 27));
        spinBox_2 = new QSpinBox(interface_graphique_2);
        spinBox_2->setObjectName(QString::fromUtf8("spinBox_2"));
        spinBox_2->setGeometry(QRect(1190, 80, 101, 27));
        spinBox_2->setMinimum(0);
        infosTournees = new QPushButton(interface_graphique_2);
        infosTournees->setObjectName(QString::fromUtf8("infosTournees"));
        infosTournees->setGeometry(QRect(1190, 110, 101, 27));

        retranslateUi(interface_graphique_2);

        QMetaObject::connectSlotsByName(interface_graphique_2);
    } // setupUi

    void retranslateUi(QWidget *interface_graphique_2)
    {
        interface_graphique_2->setWindowTitle(QApplication::translate("interface_graphique_2", "OAD", 0, QApplication::UnicodeUTF8));
        afficher_graphe->setText(QApplication::translate("interface_graphique_2", "charger instance", 0, QApplication::UnicodeUTF8));
        client->setText(QApplication::translate("interface_graphique_2", "infos clients", 0, QApplication::UnicodeUTF8));
        savings->setText(QApplication::translate("interface_graphique_2", "savings", 0, QApplication::UnicodeUTF8));
        insertion->setText(QApplication::translate("interface_graphique_2", "insertion", 0, QApplication::UnicodeUTF8));
        dist_tot->setText(QString());
        deux_opt->setText(QApplication::translate("interface_graphique_2", "2-opt*", 0, QApplication::UnicodeUTF8));
        shift->setText(QApplication::translate("interface_graphique_2", "shift", 0, QApplication::UnicodeUTF8));
        mult->setText(QApplication::translate("interface_graphique_2", "Multistart", 0, QApplication::UnicodeUTF8));
        infosTournees->setText(QApplication::translate("interface_graphique_2", "infos tournees", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class interface_graphique_2: public Ui_interface_graphique_2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERFACE_GRAPHIQUE_H
