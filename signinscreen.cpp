#include "signinscreen.hpp"
#include "registerscreen.hpp"
#include <QApplication>
#include <QBoxLayout>
#include <cstdlib>

SignInScreen::SignInScreen(QWidget *parent): QWidget(parent),
    api(BackendlessAPI("7D2C33DB-05E2-4FD9-B26B-46FDB17F56D6", "19CB95DB-0235-4134-B1FB-C64750DE49E2")),
    email(this), password(this), signInButton(this), registerButton(this), resetPasswordButton(this), teacherButton(this),
    studentButton(this), errorWin(this), signInLayout(this), teachStudentLayout(this) {

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
        resetPasswordButton.show();
    });
    QObject::connect(&api.userAPI, &BackendlessUserAPI::validateUserTokenSuccess, this, [&](auto isValid){
        qDebug() << isValid;
    });
    QObject::connect(&api.userAPI, &BackendlessUserAPI::restorePasswordSuccess, this, [&](auto reply){
        qDebug() << reply;
    });
    QObject::connect(&api, &BackendlessAPI::itemAdded, this, [&](){
        api.loadTableItems("Product");
    });
    QObject::connect(&api, &BackendlessAPI::tableItemsLoaded, this, [&](auto response){
        qDebug() << "Loaded " << response;
    });
    QObject::connect(&api, &BackendlessUserAPI::resetPasswordSuccess, this,[&](){
        qDebug() << "email sent";
    });
    api.userAPI.registerUser(BackendlessRegisterUser("something@new.com", "Roman", "Password"));
    api.userAPI.registerUser(BackendlessRegisterUser("w4ss3rv7@gmail.com", "Vojta", "Password"));

    QObject::connect(&registerButton, &QPushButton::clicked, this, [&]() {
        myWindow2->show();
        hide();
    });

    api.userAPI.restorePassword("podymov.gp@gmail.com");

    ///UI
    teacherButton.setText("Učitel");
    studentButton.setText("Student");
    signInButton.setText("Přihlásit se");
    registerButton.setText("Zaregistrovat se");
    resetPasswordButton.setText("Resetovat Heslo");
    resetPasswordButton.hide();
    errorWin.setText("Incorect Email/Password");
    errorWin.setInformativeText("Please try againg or change your password");


    teachStudentLayout.addWidget(&studentButton);
    teachStudentLayout.addWidget(&teacherButton);
    signInLayout.addLayout(&teachStudentLayout);

    signInLayout.addWidget(&email);
    signInLayout.addWidget(&password);
    signInLayout.addWidget(&signInButton);
    signInLayout.addWidget(&registerButton);
    signInLayout.addWidget(&resetPasswordButton);
    signInLayout.addStretch();

    setLayout(&signInLayout);
    signInLayout.addLayout(&teachStudentLayout);

#if !defined(Q_OS_ANDROID) && !defined(Q_OS_IOS)
    setFixedSize(640, 480);
#endif
}

SignInScreen::~SignInScreen() {

}

//"https://earthydrop-eu.backendless.app/api/users/restorepassword/w4ss3rv7@gmail.com"
