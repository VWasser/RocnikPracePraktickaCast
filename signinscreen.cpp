#include "signinscreen.hpp"
#include "coordinator.hpp"
#include <QApplication>
#include <QBoxLayout>
#include <QQuickView>
#include <QQuickItem>
#include <QQmlProperty>

extern Coordinator* coordinator;

// #define SHOULD_USE_ANDROID_UI_FORCEDLY true

SignInScreen::SignInScreen(QWidget *parent): ScreenWidget(parent),
    signInButton(this), registerButton(this), resetPasswordButton(this),
    errorWin(this), signInLayout(this)
{
    QObject::connect(&(api->userAPI), &BackendlessUserAPI::signInUserSuccess, this, [&](){
        // api.userAPI.validateUserToken();
        coordinator->showMenuWindow();
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

    QObject::connect(&registerButton, &QPushButton::clicked, this, [&]() {
        coordinator->showRegisterScreen();
        hide();
    });
    QObject::connect(&showPassword, &QCheckBox::clicked, this, [&]() {
        // passwordShow(password->echoMode());
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
        qDebug() << "HELE " << currentEmailValue() << currentPasswordValue();

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
#if SHOULD_USE_ANDROID_UI_FORCEDLY || defined(Q_OS_ANDROID) // Or you can use it for any other platform if you like QML, but for Android it is essential
    emailQuickView = new QQuickView();
    emailQuickView->setSource(QUrl("qrc:/qml/example.qml"));

    email = this->createWindowContainer(emailQuickView);
    email->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    email->setMaximumHeight(30);
#else
    email = new QLineEdit;
    ((QLineEdit*)email)->setPlaceholderText(SignInScreen::tr("email"));
#endif
}

void SignInScreen::createPasswordField() {
#if SHOULD_USE_ANDROID_UI_FORCEDLY || defined(Q_OS_ANDROID) // Or you can use it for any other platform if you like QML, but for Android it is essential
    passwordQuickView = new QQuickView();
    passwordQuickView->setSource(QUrl("qrc:/qml/example.qml"));

    password = this->createWindowContainer(passwordQuickView);
    password->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    password->setMaximumHeight(30);
#else
    password = new QLineEdit;
    ((QLineEdit*)password)->setPlaceholderText(SignInScreen::tr("password"));
    ((QLineEdit*)password)->setEchoMode(QLineEdit::Password);
#endif
}

QString SignInScreen::currentEmailValue() {
    QString value;
#if SHOULD_USE_ANDROID_UI_FORCEDLY || defined(Q_OS_ANDROID)
    auto textFieldObject = emailQuickView->rootObject();
    value = textFieldObject->property("text").toString();
#else
    value = ((QLineEdit*)email)->text();
#endif
    return value;
}

QString SignInScreen::currentPasswordValue() {
    QString value;
#if SHOULD_USE_ANDROID_UI_FORCEDLY || defined(Q_OS_ANDROID)
    auto textFieldObject = passwordQuickView->rootObject();
    value = textFieldObject->property("text").toString();
#else
    value = ((QLineEdit*)password)->text();
#endif
    return value;
}

void SignInScreen::passwordShow(auto type) {
    // TODO
    /*if(type == QLineEdit::Password){
        password->setEchoMode(QLineEdit::Normal);
    }else{
        password->setEchoMode(QLineEdit::Password);
    }*/
}
