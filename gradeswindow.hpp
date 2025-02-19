#ifndef GRADESWINDOW_HPP
#define GRADESWINDOW_HPP

#include "qboxlayout.h"
#include <QWidget>

class gradesWindow : public QWidget
{
    Q_OBJECT
public:
    gradesWindow(QWidget *parent = nullptr);
    ~gradesWindow();
private:
    QVBoxLayout *mainLayout = new QVBoxLayout;
};


#endif // GRADESWINDOW_HPP
