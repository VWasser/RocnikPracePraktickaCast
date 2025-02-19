#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include "qboxlayout.h"
#include <QWidget>

class settingsWindow: public QWidget
{
    Q_OBJECT

public:
    settingsWindow(QWidget *parent = nullptr);
    ~settingsWindow();
private:
    QVBoxLayout *mainLayout = new QVBoxLayout;
};

#endif // SETTINGSWINDOW_H

