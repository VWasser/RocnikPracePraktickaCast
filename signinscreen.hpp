#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QMessageBox>
#include "BackendlessQt/BackendlessAPI.hpp"
#include "qboxlayout.h"

class SignInScreen: public QWidget
{
    Q_OBJECT

public:
    SignInScreen(QWidget *parent = nullptr);
    ~SignInScreen();

private:
    BackendlessAPI api;

private:
    //UI
    QLineEdit email;
    QLineEdit password;
    QLabel emailLabel;
    QLabel passwordLabel;
    QPushButton signInButton;
    QPushButton registerButton;
    QPushButton resetPasswordButton;
    QPushButton teacherButton;
    QPushButton studentButton;

    QMessageBox errorWin;
    QVBoxLayout signInLayout;
    QHBoxLayout teachStudentLayout;

private:
    void onClickRegisterButton();

};

