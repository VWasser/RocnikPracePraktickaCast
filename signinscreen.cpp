#include "signinscreen.hpp"
#include <QApplication>

SignInScreen::SignInScreen(QWidget *parent): QWidget(parent) {
    QObject::connect(&api, &API::userSignedIn, [](auto token){
        qDebug() << "Signed in" << token;
    });
    api.signInUser("APP_ID", "REST_API_KEY", "email", "password");
}

SignInScreen::~SignInScreen() {

}
