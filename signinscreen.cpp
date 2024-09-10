#include "signinscreen.hpp"
#include "registerscreen.hpp"
#include <QApplication>
#include <QBoxLayout>
#include <cstdlib>

SignInScreen::SignInScreen(QWidget *parent): QWidget(parent),
    email(this), password(this), signInButton(this), registerButton(this), resetPasswordButton(this), teacherButton(this),
    studentButton(this), errorWin(this), signInLayout(this), teachStudentLayout(this) {

    // Sign in screen should not register a new user, we already have registerscreen.cpp for it
    /*QObject::connect(&api.userAPI, &BackendlessUserAPI::registerUserResult, this, [&](){
        api.userAPI.signInUser("something@new.com", "Password");
        qDebug() << "Signing in";
        myWindow3->show();
        hide();
    });*/
    QObject::connect(&(api->userAPI), &BackendlessUserAPI::signInUserSuccess, this, [&](){
        // api.userAPI.validateUserToken();

        myWindow3->show();
        hide();
    });
    QObject::connect(&(api->userAPI), &BackendlessUserAPI::signInUserErrorBackendless, this, [&](auto error){
        qDebug() << "Error!!!";
        errorWin.exec();
        resetPasswordButton.show();
    });
    QObject::connect(&(api->userAPI), &BackendlessUserAPI::validateUserTokenSuccess, this, [&](auto isValid){
        qDebug() << isValid;
    });
    QObject::connect(&(api->userAPI), &BackendlessUserAPI::restorePasswordSuccess, this, [&](auto reply){
        qDebug() << reply;
    });
    // For now commented, later you can use it to load schedule
    /*QObject::connect(&api, &BackendlessAPI::itemAdded, this, [&](){
        api.loadTableItems("Product");
    });
    QObject::connect(&api, &BackendlessAPI::tableItemsLoaded, this, [&](auto response){
        qDebug() << "Loaded " << response;
    });*/
    QObject::connect(&(api->userAPI), &BackendlessUserAPI::restorePasswordSuccess, this, [&](auto response){
        qDebug() << "email sent";
    });
    QObject::connect(&signInButton, &QPushButton::clicked, this, [&]() {
        api->userAPI.signInUser(email.text(), password.text());
    });
    QObject::connect(&registerButton, &QPushButton::clicked, this, [&]() {
        myWindow2->show();
        hide();
    });

    ///UI
    teacherButton.setText(SignInScreen::tr("Teacher"));
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
