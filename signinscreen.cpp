#include "signinscreen.hpp"
#include "registerscreen.hpp"
#include <QApplication>
#include <QBoxLayout>

SignInScreen::SignInScreen(QWidget *parent): QWidget(parent),
    signInButton(this), registerButton(this), resetPasswordButton(this),
    errorWin(this), signInLayout(this),
    client(this)
{
    client.connectToHost("stackoverflow.com");
    QString dataToSendToServer = QString("GET / HTTP/1.1 \n\r\nHost: stackoverflow.com\n\r\n");
    client.writeData(dataToSendToServer.toUtf8());

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
        api->userAPI.signInUser(email->text(), password->text());
    });
    QObject::connect(&registerButton, &QPushButton::clicked, this, [&]() {
        myWindow2->show();
        hide();
    });
    QObject::connect(&showPassword, &QCheckBox::clicked, this, [&]() {
        passwordShow(password->echoMode());
    });
    ///UI
    signInButton.setText(SignInScreen::tr("signIn"));
    registerButton.setText(SignInScreen::tr("logIn"));
    resetPasswordButton.setText(SignInScreen::tr("resetPassword"));
    resetPasswordButton.hide();
    errorWin.setText(SignInScreen::tr("incorectEmail/Password"));
    errorWin.setInformativeText(SignInScreen::tr("passwordErrorMsg"));
    showPasswordLabel.setText(SignInScreen::tr("showPassword"));


    showPasswordLayout.addWidget(&showPassword);
    showPasswordLayout.addWidget(&showPasswordLabel);
    showPasswordLayout.addStretch();


    signInLayout.addWidget(email);
    signInLayout.addWidget(password);
    signInLayout.addLayout(&showPasswordLayout);
    signInLayout.addWidget(&signInButton);
    signInLayout.addWidget(&registerButton);
    signInLayout.addWidget(&resetPasswordButton);
    signInLayout.addStretch();

    setLayout(&signInLayout);

    email->setPlaceholderText(SignInScreen::tr("email"));
    password->setPlaceholderText(SignInScreen::tr("password"));
    password->setEchoMode(QLineEdit::Password);

#if !defined(Q_OS_ANDROID) && !defined(Q_OS_IOS)
    setFixedSize(640, 480);
#endif
}

SignInScreen::~SignInScreen() {

}

void SignInScreen::passwordShow(auto type){
    if(type == QLineEdit::Password){
        password->setEchoMode(QLineEdit::Normal);
    }else{
        password->setEchoMode(QLineEdit::Password);
    }
}
