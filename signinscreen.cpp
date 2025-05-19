#include "signinscreen.hpp"
#include "coordinator.hpp"
#include <QApplication>
#include <QBoxLayout>
#include <QQuickView>
#include <QQuickItem>
#include <QQmlProperty>

extern Coordinator* coordinator;

SignInScreen::SignInScreen(QWidget *parent): ScreenWidget(parent),
    signInButton(this), registerButton(this), resetPasswordButton(this),
    errorWin(this), signInLayout(this)
{
    QObject::connect(&(api->userAPI), &BackendlessUserAPI::signInUserSuccess, this, [&](){
        coordinator->showMenuWindow();
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
    QObject::connect(&(api->userAPI), &BackendlessUserAPI::restorePasswordSuccess, this, [&](auto response){
        qDebug() << "email sent";
    });

    QObject::connect(&registerButton, &QPushButton::clicked, this, [&]() {
        coordinator->showRegisterScreen();
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

    createEmailField();
    signInLayout.addWidget(this->email);
    createPasswordField();
    signInLayout.addWidget(this->password);
    signInLayout.addLayout(&showPasswordLayout);
    signInLayout.addWidget(&signInButton);
    signInLayout.addWidget(&registerButton);
    signInLayout.addWidget(&resetPasswordButton);

    QObject::connect(&signInButton, &QPushButton::clicked, this, [&]() {
        api->userAPI.signInUser(
            currentEmailValue(),
            currentPasswordValue()
        );
    });

    signInLayout.addStretch();

    setLayout(&signInLayout);

#if !defined(Q_OS_ANDROID) && !defined(Q_OS_IOS)
    setFixedSize(640, 480);
#endif
}

SignInScreen::~SignInScreen() {

}

void SignInScreen::configure(QSharedPointer<ShowBasicData>) {

}

void SignInScreen::createEmailField() {
    email = new QLineEdit;
    email->setPlaceholderText(SignInScreen::tr("email"));
}

void SignInScreen::createPasswordField() {
    password = new QLineEdit;
    password->setPlaceholderText(SignInScreen::tr("password"));
    password->setEchoMode(QLineEdit::Password);
}

QString SignInScreen::currentEmailValue() {
    QString value;
    value = email->text();
    return value;
}

QString SignInScreen::currentPasswordValue() {
    QString value;
    value = password->text();
    return value;
}

void SignInScreen::passwordShow(auto type) {
    if(type == QLineEdit::Password){
        password->setEchoMode(QLineEdit::Normal);
    }else{
        password->setEchoMode(QLineEdit::Password);
    }
}
