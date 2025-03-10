#ifndef REGISTERSCREEN_H
#define REGISTERSCREEN_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QBoxLayout>
#include <QCheckBox>
#include "BackendlessQt/BackendlessUser.hpp"
#include "screenwidget.hpp"

struct BackendlessRegisterUser: BasicBackendlessRegisterUser {
public:
    BackendlessRegisterUser(
        QString _email,
        QString _password,
        QString _name,
        bool _teacher
    ): BasicBackendlessRegisterUser(_email, _password), name(new StringPostParam(_name)), teacher(new StringPostParam(_teacher ? "true" : "false")) { }

    ~BackendlessRegisterUser() {
        delete name;
        delete teacher;
    }

    PostParams getAllParams() override {
        PostParams result = {{"name", name},{"teacher", teacher}};
        result.insert(BasicBackendlessRegisterUser::getAllParams());
        return result;
    }

protected:
    StringPostParam* name;
    StringPostParam* teacher;
};

class registerscreen : public ScreenWidget
{
    Q_OBJECT
public:
    registerscreen(QWidget *parent = nullptr);
    ~registerscreen();

    void configure(QSharedPointer<ShowBasicData>, QSharedPointer<ShowBasicData2>) override;

private:

    QLineEdit* name = new QLineEdit;
    QLineEdit* password = new QLineEdit;
    QLineEdit* password2 = new QLineEdit;
    QLineEdit* email = new QLineEdit;


    QCheckBox isTeacher;
    QLabel isTeacherLabel;
    QLabel passwordError;

    QPushButton regist;
    QPushButton logIn;
    QLabel logInLabel;

    QHBoxLayout teachStudentLayout;
    QVBoxLayout registLayout;

    BackendlessRegisterUserRepresentable* currentUser;
};

#endif // REGISTERSCREEN_H
