#include "registerscreen.hpp"
#include <QWidget>
#include <QBoxLayout>

registerscreen::registerscreen(QWidget *parent): QWidget(parent),
    email(this), name(this), password(this), regist(this), logIn(this), logInLabel(this)
{
    regist.setText("Zaregistrovat se");
    logIn.setText("Přihlásit se");
    logInLabel.setText("jste už zaregistrováni? ");
    registLayout.addWidget(&email);
    registLayout.addWidget(&name);
    registLayout.addWidget(&password);
    registLayout.addWidget(&regist);
    registLayout.addWidget(&logIn);
    registLayout.addWidget(&logInLabel);
    registLayout.addStretch();
    setLayout(&registLayout);
}
registerscreen::~registerscreen()
{}
