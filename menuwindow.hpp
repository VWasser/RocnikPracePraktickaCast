#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include "qpushbutton.h"
#include <QWidget>
#include <QGridLayout>
#include <QMenuBar>


class menuWindow : public QWidget
{
    Q_OBJECT
public:
    menuWindow(QWidget *parent = nullptr);
    ~menuWindow();


private:
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *row1 = new QHBoxLayout;
    QHBoxLayout *row2 = new QHBoxLayout;

    QPushButton *scheduleButton = new QPushButton(menuWindow::tr("Schedule"));
    QPushButton *absenceButton = new QPushButton(menuWindow::tr("Absence"));
    QPushButton *gradesButton = new QPushButton(menuWindow::tr("Grades"));
    QPushButton *settingsButton = new QPushButton;
    QPushButton *LanguageButton = new QPushButton;

signals:
    void schedulePressed();
    void gradesPressed();
    void absencePressed();
    void settingsPressed();

    //not yet created
    void logOutPressed();

};

#endif // MENUWINDOW_H
