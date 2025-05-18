#ifndef SIGNINSCREEN_HPP
#define SIGNINSCREEN_HPP

#include <QQuickView>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QMessageBox>
#include <QCheckBox>
#include "qboxlayout.h"
#include "screenwidget.hpp"
#include "BackendlessQt/BackendlessUserAPI.hpp"

struct BachelorSignInUser: BackendlessSignInUser {
    bool isTeacher;

    BachelorSignInUser(
        QJsonObject jsonObject
    ): BackendlessSignInUser(jsonObject),
        isTeacher(jsonObject["isTeacher"].toBool()) {

    }

    BachelorSignInUser() {}
};

struct BachelorSignInUserCoder: BackendlessSignInUserCoder {
    Codable* decode(QJsonObject obj) override {
        return new BachelorSignInUser(obj);
    }

    void write(QTextStream& stream, QSharedPointer<Codable> codable, QSharedPointer<Codable> defaultValue) override {
        auto userValue = (BachelorSignInUser*)(defaultValue.get() ? defaultValue.get() : codable.get());
        stream << userValue->userToken << Qt::endl;
        stream << userValue->email << Qt::endl;
        stream << userValue->name << Qt::endl;
        stream << (userValue->isTeacher ? "YES" : "NO") << Qt::endl;
    }

    Codable* read(QTextStream& stream) override {
        auto result = new BachelorSignInUser();
        stream >> result->userToken >> Qt::endl;
        stream >> result->email >> Qt::endl;
        stream >> result->name >> Qt::endl;
        QString isTeacher;
        stream >> isTeacher >> Qt::endl;
        result->isTeacher = isTeacher == "YES";
        return result;
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
    QQuickView* emailQuickView;
    QQuickView* passwordQuickView;
    QWidget* email;
    QWidget* password;

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
    void createEmailField();
    void createPasswordField();
    QString currentEmailValue();
    QString currentPasswordValue();
};

extern SignInScreen* myWindow;

#endif
