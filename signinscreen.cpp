#include "signinscreen.hpp"
#include "registerscreen.hpp"
#include <QApplication>
#include <QBoxLayout>
#include <cstdlib>

static inline qint32 ArrayToInt(QByteArray source);

SignInScreen::SignInScreen(QWidget *parent): QWidget(parent),
    signInButton(this), registerButton(this), resetPasswordButton(this),
    errorWin(this), signInLayout(this),
    client(this)
{
    client.connectToHost("cs.wikipedia.org");
    QString dataToSendToServer = QString("GET /wiki/Wikipedie HTTP/1.1");
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

static inline QByteArray IntToArray(qint32 source);

Client::Client(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket(this);
}

bool Client::connectToHost(QString host)
{
    socket->connectToHost(host, 80);
    return socket->waitForConnected();
}

bool Client::writeData(QByteArray data)
{
    if(socket->state() == QAbstractSocket::ConnectedState)
    {
        connect(socket, SIGNAL(readyRead()), SLOT(readyRead()));
        socket->write(IntToArray(data.size())); //write size of data
        socket->write(data); //write the data itself
        return socket->waitForBytesWritten();
    }
    else
        return false;
}

void Client::readyRead()
{
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
    QByteArray *buffer = new QByteArray();
    qint32 *s = new qint32(1000); //sizes.value(socket);
    qint32 size = *s;
    while (socket->bytesAvailable() > 0)
    {
        QString data = socket->readAll();
        qDebug() << data;
        buffer->append(socket->readAll());
        while ((size == 0 && buffer->size() >= 4) || (size > 0 && buffer->size() >= size)) //While can process data, process it
        {
            if (size == 0 && buffer->size() >= 4) //if size of data has received completely, then store it on our global variable
            {
                size = ArrayToInt(buffer->mid(0, 4));
                *s = size;
                buffer->remove(0, 4);
            }
            if (size > 0 && buffer->size() >= size) // If data has received completely, then emit our SIGNAL with the data
            {
                QByteArray data = buffer->mid(0, size);
                buffer->remove(0, size);
                size = 0;
                *s = size;
                // emit dataReceived(data);
            }
        }
    }
}

QByteArray IntToArray(qint32 source) //Use qint32 to ensure that the number have 4 bytes
{
    //Avoid use of cast, this is the Qt way to serialize objects
    QByteArray temp;
    QDataStream data(&temp, QIODevice::ReadWrite);
    data << source;
    return temp;
}

qint32 ArrayToInt(QByteArray source)
{
    qint32 temp;
    QDataStream data(&source, QIODevice::ReadWrite);
    data >> temp;
    return temp;
}
