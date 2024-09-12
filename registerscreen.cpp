#include "registerscreen.hpp"
#include <QWidget>
#include <QBoxLayout>

registerscreen::registerscreen(QWidget *parent): QWidget(parent),
     regist(this), logIn(this), logInLabel(this)
{
    regist.setText("Zaregistrovat se");
    logIn.setText("Přihlásit se");
    logInLabel.setText("jste už zaregistrováni? ");

    name->setPlaceholderText("Jméno");
    password->setPlaceholderText("heslo");

    registLayout.addWidget(name);
    registLayout.addWidget(password);
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
