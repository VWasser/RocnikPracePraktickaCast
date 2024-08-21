#ifndef REGISTERSCREEN_H
#define REGISTERSCREEN_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QBoxLayout>

class registerscreen : public QWidget
{
    Q_OBJECT
public:
    registerscreen(QWidget *parent = nullptr);
    ~registerscreen();

private:
    QLineEdit email;
    QLineEdit name;
    QLineEdit password;

    QPushButton regist;
    QPushButton logIn;
    QLabel logInLabel;

    QVBoxLayout registLayout;


};

#endif // REGISTERSCREEN_H
