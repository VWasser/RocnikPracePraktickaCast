#ifndef GRADESWINDOW_HPP
#define GRADESWINDOW_HPP

#include "qboxlayout.h"
#include <QWidget>
#include "screenwidget.hpp"

class gradesWindow : public ScreenWidget
{
    Q_OBJECT
public:
    gradesWindow(QWidget *parent = nullptr);
    ~gradesWindow();
    void configure(ShowBasicData*,ShowBasicData2*) override;

private:
    QVBoxLayout *mainLayout = new QVBoxLayout;
};


#endif // GRADESWINDOW_HPP
