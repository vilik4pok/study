/********************************************************************************
** Form generated from reading UI file 'palettetest.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PALETTETEST_H
#define UI_PALETTETEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PaletteTest
{
public:

    void setupUi(QWidget *PaletteTest)
    {
        if (PaletteTest->objectName().isEmpty())
            PaletteTest->setObjectName(QStringLiteral("PaletteTest"));
        PaletteTest->resize(400, 300);

        retranslateUi(PaletteTest);

        QMetaObject::connectSlotsByName(PaletteTest);
    } // setupUi

    void retranslateUi(QWidget *PaletteTest)
    {
        PaletteTest->setWindowTitle(QApplication::translate("PaletteTest", "PaletteTest", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PaletteTest: public Ui_PaletteTest {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PALETTETEST_H
