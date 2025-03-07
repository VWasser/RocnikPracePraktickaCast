#ifndef SIGNINSCREEN_HPP
#define SIGNINSCREEN_HPP

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QMessageBox>
#include <QCheckBox>
#include "qboxlayout.h"
#include "screenwidget.hpp"

class SignInScreen: public ScreenWidget
{
    Q_OBJECT

public:
    SignInScreen(QWidget *parent = nullptr);
    ~SignInScreen();

    void configure(ShowBasicData*,ShowBasicData2*) override;

private:
    //UI
    QLineEdit* email= new QLineEdit;
    QLineEdit* password = new QLineEdit;

    QCheckBox showPassword;
    QLabel showPasswordLabel;
    QHBoxLayout showPasswordLayout;

    QLabel emailLabel;
    QLabel passwordLabel;
    QPushButton signInButton;
    QPushButton registerButton;
    QPushButton resetPasswordButton;


    QMessageBox errorWin;
    QVBoxLayout signInLayout;
private:
    void passwordShow(auto type);
};

extern SignInScreen* myWindow;

#endif
