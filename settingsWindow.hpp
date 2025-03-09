#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include "qboxlayout.h"
#include <QWidget>
#include "screenwidget.hpp"

class settingsWindow: public ScreenWidget
{
    Q_OBJECT

public:
    settingsWindow(QWidget *parent = nullptr);
    ~settingsWindow();
    void configure(ShowBasicData*, ShowBasicData2*) override;

private:
    QVBoxLayout *mainLayout = new QVBoxLayout;
};

#endif // SETTINGSWINDOW_H

