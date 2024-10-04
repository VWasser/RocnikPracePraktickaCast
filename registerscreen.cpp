#include "registerscreen.hpp"
#include <QWidget>
#include <QBoxLayout>
#include <QPushButton>
#include "BackendlessQt/BackendlessAPI.hpp"
#include "schedule.hpp"


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

    regist.setText(registerscreen::tr("Zaregistrovat se"));
    logIn.setText(registerscreen::tr("Přihlásit se"));
    logInLabel.setText(registerscreen::tr("jste už zaregistrováni? "));

    email->setPlaceholderText(registerscreen::tr("Email"));
    name->setPlaceholderText(registerscreen::tr("Jméno"));
    password->setPlaceholderText(registerscreen::tr("heslo"));
    password2->setPlaceholderText(registerscreen::tr("heslo znovu"));
    isTeacherLabel.setText(registerscreen::tr("Jste Učitel?"));

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
