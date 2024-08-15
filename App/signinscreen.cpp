#include "signinscreen.hpp"
#include <QApplication>

SignInScreen::SignInScreen(QWidget *parent): QWidget(parent),
    api(BackendlessAPI("7D2C33DB-05E2-4FD9-B26B-46FDB17F56D6", "19CB95DB-0235-4134-B1FB-C64750DE49E2")), email(this), password(this), signInButton(this), registerButton(this), resetPasswordButton(this), teacherButton(this),
    studentButton(this), errorWin(this) {

    QObject::connect(&api.userAPI, &BackendlessUserAPI::registerUserResult, this, [&](){
        api.userAPI.signInUser("something@new.com", "Password");
        qDebug() << "Signing in";
    });
    QObject::connect(&api.userAPI, &BackendlessUserAPI::signInUserSuccess, this, [&](){
        api.userAPI.validateUserToken();
    });
    QObject::connect(&api.userAPI, &BackendlessUserAPI::signInUserErrorBackendless, this, [&](auto error){
        qDebug() << "Error!!!";
        errorWin.exec();
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
    email.setGeometry(210 , 100, 200 , 50);
    password.setGeometry(210 , 160, 200 , 50);

    //tlačítka
    teacherButton.setGeometry(210, 40, 100, 50);
    teacherButton.setText("Učitel");

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

    errorWin.setText("Incorect Email/Password");
    errorWin.setInformativeText("Please try againg or change your password");



}

SignInScreen::~SignInScreen() {

}
