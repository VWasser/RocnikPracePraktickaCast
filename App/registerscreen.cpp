#include "registerscreen.hpp"
#include <QWidget>
#include <QBoxLayout>
#include <QPushButton>
#include "BackendlessAPI.hpp"
// #include "schedule.hpp"

//extern BackendlessAPI* api;

registerscreen::registerscreen(QWidget *parent): QWidget(parent),
     regist(this), logIn(this), logInLabel(this)
{

    QObject::connect(&regist, &QPushButton::clicked, this , [&](){
            if(password->text() != password2->text()){
                password->clear();
                password2->clear();

            }else{
                // api->userAPI.registerUser(BackendlessRegisterUser(email->text(), name->text(), password->text()));
            }


    });

    regist.setText("Zaregistrovat se");
    logIn.setText("Přihlásit se");
    logInLabel.setText("jste už zaregistrováni? ");

    email->setPlaceholderText("Email");
    name->setPlaceholderText("Jméno");
    password->setPlaceholderText("heslo");
    password2->setPlaceholderText("heslo znovu");
    isTeacherLabel.setText("Jste Učitel?");

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
registerscreen::~registerscreen()
{}
