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
};

class SignInScreen: public QWidget
{
    Q_OBJECT

public:
    SignInScreen(QWidget *parent = nullptr);
    ~SignInScreen();

private:
    //UI
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

private:
    Client client;
};

#endif
