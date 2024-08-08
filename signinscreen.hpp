#include <QWidget>
#include "BackendlessQt/API.hpp"
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>

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
    

};

