#ifndef SCREENWIDGET_H
#define SCREENWIDGET_H

#include <QWidget>

struct ShowBasicData {

};

struct ShowBasicData2{

};

class ScreenWidget: public QWidget {
    Q_OBJECT

public:
    ScreenWidget(QWidget *parent = nullptr); // : QWidget(parent) { }
    virtual void configure(ShowBasicData*, ShowBasicData2*) = 0;
};

#endif // SCREENWIDGET_H
