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
#include "BackendlessQt/BackendlessUser.hpp"

struct BachelorSignInUser: BackendlessSignInUser {
    bool isTeacher;

    BachelorSignInUser(
        QJsonObject jsonObject
    ): BackendlessSignInUser(jsonObject),
    isTeacher(jsonObject["isTeacher"].toBool()) {

    }
};

class SignInScreen: public ScreenWidget
{
    Q_OBJECT

public:
    SignInScreen(QWidget *parent = nullptr);
    ~SignInScreen();

    void configure(QSharedPointer<ShowBasicData>) override;

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
