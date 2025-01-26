#include "registerscreen.hpp"
#include <QWidget>
#include <QBoxLayout>
#include <QPushButton>
#include "BackendlessQt/BackendlessAPI.hpp"
#include "schedule.hpp"
#include "signinscreen.hpp"


registerscreen::registerscreen(QWidget *parent): QWidget(parent),
     regist(this), logIn(this), logInLabel(this)
{

    QObject::connect(&regist, &QPushButton::clicked, this , [&](){
            if(password->text() != password2->text()){
                password->clear();
                password2->clear();

            }else{
                // TODO: implement your own BackendlessRegisterUser, see https://github.com/RomanPodymov/FinanceTracker/blob/main/App/registerscreen.hpp
                currentUser = new BackendlessRegisterUser(email->text(), password->text(),name->text(), isTeacher.isChecked());
                api->userAPI.registerUser(*currentUser);
                delete currentUser;
            }
    });
    QObject::connect(&logIn, &QPushButton::clicked, this, [&]() {
        // TODO: show this window
        //myWindow->show();
        hide();
    });

    regist.setText(registerscreen::tr("logIn"));
    logIn.setText(registerscreen::tr("signIn"));
    logInLabel.setText(registerscreen::tr("registeredYet"));

    email->setPlaceholderText(registerscreen::tr("email"));
    name->setPlaceholderText(registerscreen::tr("name"));
    password->setPlaceholderText(registerscreen::tr("password"));
    password2->setPlaceholderText(registerscreen::tr("passwordAgain"));
    isTeacherLabel.setText(registerscreen::tr("youTeacher"));

    teachStudentLayout.addWidget(&isTeacher);
    teachStudentLayout.addWidget(&isTeacherLabel);
    teachStudentLayout.addWidget(&passwordError);


    registLayout.addLayout(&teachStudentLayout);
    registLayout.addWidget(email);
    registLayout.addWidget(name);
    registLayout.addWidget(password);
    registLayout.addWidget(password2);
    registLayout.addWidget(&regist);
    registLayout.addWidget(&logInLabel);
    registLayout.addWidget(&logIn);
    registLayout.addStretch();
    setLayout(&registLayout);





    #if !defined(Q_OS_ANDROID) && !defined(Q_OS_IOS)
    setFixedSize(640, 400);
#endif
}
registerscreen::~registerscreen(){}
