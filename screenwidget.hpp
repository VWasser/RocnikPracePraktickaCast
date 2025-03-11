#ifndef SCREENWIDGET_H
#define SCREENWIDGET_H

#include <QWidget>
#include <QSharedPointer>

class ShowBasicData: public QObject {
    Q_OBJECT
};

class ScreenWidget: public QWidget {
    Q_OBJECT

public:
    ScreenWidget(QWidget *parent = nullptr); // : QWidget(parent) { }
    virtual void configure(QSharedPointer<ShowBasicData>) = 0;
};

#endif // SCREENWIDGET_H
