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

};

