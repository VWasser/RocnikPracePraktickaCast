#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QMessageBox>
#include <QBoxLayout>
#include "BackendlessAPI.hpp"
#include "registerscreen.hpp"
//#include "schedule.hpp"

extern registerscreen* myWindow2;
//extern Schedule* myWindow3;

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
};

