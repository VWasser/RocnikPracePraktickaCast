#include "signinscreen.hpp"
#include "coordinator.hpp"
#include "registerscreen.hpp"
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

#if defined(Q_OS_ANDROID) // Or you can use it for any other platform if you like QML, but for Android it is essential
    auto view = new QQuickView();
    view->setSource(QUrl("qrc:/qml/example.qml"));

    auto qmlWrapper = this->createWindowContainer(view);
    qmlWrapper->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    qmlWrapper->setMaximumHeight(30);
    signInLayout.addWidget(qmlWrapper);
#else
    signInLayout.addWidget(email);
#endif

    signInLayout.addWidget(password);
    signInLayout.addLayout(&showPasswordLayout);
    signInLayout.addWidget(&signInButton);
    signInLayout.addWidget(&registerButton);
    signInLayout.addWidget(&resetPasswordButton);

    QObject::connect(&signInButton, &QPushButton::clicked, this, [=]() {
        QString signInValue;
        #if defined(Q_OS_ANDROID)
        auto signInTextFieldObject = view->rootObject();
        signInValue = signInTextFieldObject->property("text").toString();
        #else
        signInValue = email->text();
        #endif

        qDebug() << "SIGN IN email " << signInValue;

        api->userAPI.signInUser(
            signInValue,
            password->text()
        );
    });

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

void SignInScreen::configure(QSharedPointer<ShowBasicData>) {

}

void SignInScreen::passwordShow(auto type){
    if(type == QLineEdit::Password){
        password->setEchoMode(QLineEdit::Normal);
    }else{
        password->setEchoMode(QLineEdit::Password);
    }
}
