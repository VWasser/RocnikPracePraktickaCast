#ifndef EDITMODESCREEN_H
#define EDITMODESCREEN_H

#include "qboxlayout.h"
#include "qlineedit.h"
#include "qpushbutton.h"
#include <QWidget>

class editModeScreen: public QWidget
{
    Q_OBJECT

public:
    editModeScreen(QWidget *parent = nullptr);
    ~editModeScreen();
private:
    QLineEdit* nameOfClass = new QLineEdit;
    QLineEdit* classRow = new QLineEdit;
    QLineEdit* classCollumn = new QLineEdit;

    QHBoxLayout* rowsAndCollums = new QHBoxLayout;
    QVBoxLayout* mainLayout = new QVBoxLayout;

    QPushButton* addButt = new QPushButton;
    QString objID;

};

#endif // EDITMODESCREEN_H
