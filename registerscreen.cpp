#include "registerscreen.hpp"
#include <QWidget>
#include <QBoxLayout>
#include <QPushButton>

registerscreen::registerscreen(QWidget *parent): QWidget(parent),
     regist(this), logIn(this), logInLabel(this)
{
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

    QObject::connect(&regist, &QPushButton::clicked, this,[&](){
        if(password->text() != password2->text()){
            password->clear();
            password2->clear();

        }
    });



    #if !defined(Q_OS_ANDROID) && !defined(Q_OS_IOS)
    setFixedSize(640, 400);
#endif
}
registerscreen::~registerscreen()
{}
