#include "signinscreen.hpp"
#include <QApplication>

SignInScreen::SignInScreen(QWidget *parent): QWidget(parent),
    api(BackendlessAPI("", "")) {

    QObject::connect(&api.userAPI, &BackendlessUserAPI::userRegistered, &api.userAPI, [&](){
        api.userAPI.signInUser("something@new.com", "Password");
        qDebug() << "Signing in";
    });
    QObject::connect(&api.userAPI, &BackendlessUserAPI::userSignedIn, &api.userAPI, [&](){
        api.userAPI.validateUserToken();
    });
    QObject::connect(&api.userAPI, &BackendlessUserAPI::userTokenValidated, &api.userAPI, [&](auto isValid){
        qDebug() << isValid;
    });
    QObject::connect(&api, &BackendlessAPI::itemAdded, &api, [&](){
        api.loadTableItems("Product");
    });
    QObject::connect(&api, &BackendlessAPI::tableItemsLoaded, &api, [&](auto response){
        qDebug() << "Loaded " << response;
    });

    api.userAPI.registerUser(BackendlessUser("something@new.com", "Roman", "Password"));
}

SignInScreen::~SignInScreen() {

}
