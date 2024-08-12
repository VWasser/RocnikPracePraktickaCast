#include "signinscreen.hpp"
#include <QApplication>

SignInScreen::SignInScreen(QWidget *parent): QWidget(parent),
    email(this), password(this), signInButton(this), registerButton(this), resetPasswordButton(this), teacherButton(this), studentButton(this),
    api(BackendlessAPI("", "")) {

    QObject::connect(&api.userAPI, &BackendlessUserAPI::registerUserResult, this, [&](){
        api.userAPI.signInUser("something@new.com", "Password");
        qDebug() << "Signing in";
    });
    QObject::connect(&api.userAPI, &BackendlessUserAPI::signInUserSuccess, this, [&](){
        api.userAPI.validateUserToken();
    });
    QObject::connect(&api.userAPI, &BackendlessUserAPI::signInUserErrorBackendless, this, [&](auto error){
        qDebug() << "Error!!!";
    });
    QObject::connect(&api.userAPI, &BackendlessUserAPI::validateUserTokenSuccess, this, [&](auto isValid){
        qDebug() << isValid;
    });
    QObject::connect(&api, &BackendlessAPI::itemAdded, this, [&](){
        api.loadTableItems("Product");
    });
    QObject::connect(&api, &BackendlessAPI::tableItemsLoaded, this, [&](auto response){
        qDebug() << "Loaded " << response;
    });
    api.userAPI.registerUser(BackendlessRegisterUser("something@new.com", "Roman", "Password"));


    ///UI
    //Textový pole
    email.setGeometry(110 , 100, 200 , 50);
    password.setGeometry(110 , 160, 200 , 50);

    //tlačítka
    teacherButton.setGeometry(110, 40, 100, 50);
    teacherButton.setText("???Učitel");

    studentButton.setGeometry(310, 40, 100, 50);
    studentButton.setText("Student");

    signInButton.setGeometry(220 , 220, 180 , 50);
    signInButton.setText("Přihlásit se");

    registerButton.setGeometry(400, 400, 200, 50);
    registerButton.setText("Zaregistrovat se");

    //ukáže se puze když user zadá špatně heslo
    resetPasswordButton.setGeometry(220 , 270, 180, 50);
    resetPasswordButton.setText("Resetovat Heslo");
    //resetPasswordButton.hide();



}

SignInScreen::~SignInScreen() {

}
