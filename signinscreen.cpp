#include "signinscreen.hpp"
#include <QApplication>

SignInScreen::SignInScreen(QWidget *parent): QWidget(parent),
    api(BackendlessAPI("", "")) {

    QObject::connect(&api.userAPI, &BackendlessUserAPI::userRegistered, this, [&](){
        api.userAPI.signInUser("something@new.com", "Password");
        qDebug() << "Signing in";
    });
    QObject::connect(&api.userAPI, &BackendlessUserAPI::userSignedIn, this, [&](){
        api.userAPI.validateUserToken();
    });
    QObject::connect(&api.userAPI, &BackendlessUserAPI::userSignInError, this, [&](auto error){
        qDebug() << "Error!!!";
    });
    QObject::connect(&api.userAPI, &BackendlessUserAPI::userTokenValidated, this, [&](auto isValid){
        qDebug() << isValid;
    });
    QObject::connect(&api, &BackendlessAPI::itemAdded, this, [&](){
        api.loadTableItems("Product");
    });
    QObject::connect(&api, &BackendlessAPI::tableItemsLoaded, this, [&](auto response){
        qDebug() << "Loaded " << response;
    });
    api.userAPI.registerUser(BackendlessUser("something@new.com", "Roman", "Password"));


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



}

SignInScreen::~SignInScreen() {

}
