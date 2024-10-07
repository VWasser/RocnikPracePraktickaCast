#ifndef SIGNINSCREEN_HPP
#define SIGNINSCREEN_HPP

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QMessageBox>
#include "BackendlessQt/BackendlessAPI.hpp"
#include "qboxlayout.h"
#include "registerscreen.hpp"
#include "schedule.hpp"

extern registerscreen* myWindow2;
extern Schedule* myWindow3;

#include <QtCore>
#include <QtNetwork>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);

public slots:
    bool connectToHost(QString host);
    bool writeData(QByteArray data);
    void readyRead();

private:
    QTcpSocket *socket;
    // void readyRead();
};

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);

signals:
    void dataReceived(QByteArray);

private slots:
    void newConnection();
    void disconnected();
    void readyRead();

private:
    QTcpServer *server;
    QHash<QTcpSocket*, QByteArray*> buffers; //We need a buffer to store data until block has completely received
    QHash<QTcpSocket*, qint32*> sizes; //We need to store the size to verify if a block has received completely
};

class SignInScreen: public QWidget
{
    Q_OBJECT

public:
    SignInScreen(QWidget *parent = nullptr);
    ~SignInScreen();

private:
    //UI
    Server server;
    Client client;
    QLineEdit* email= new QLineEdit;
    QLineEdit* password = new QLineEdit;

    QCheckBox showPassword;
    QLabel showPasswordLabel;
    QHBoxLayout showPasswordLayout;

    QLabel emailLabel;
    QLabel passwordLabel;
    QPushButton signInButton;
    QPushButton registerButton;
    QPushButton resetPasswordButton;


    QMessageBox errorWin;
    QVBoxLayout signInLayout;
private:
    void passwordShow(auto type);
};

#endif
