#ifndef REGISTERSCREEN_H
#define REGISTERSCREEN_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QBoxLayout>
#include <QCheckBox>
#include "BackendlessQt/BackendlessUser.hpp"

struct BackendlessRegisterUser: BasicBackendlessRegisterUser {
public:
    BackendlessRegisterUser(
        QString _email,
        QString _password,
        bool _someCustomField
    ): BasicBackendlessRegisterUser(_email, _password), someCustomField(_someCustomField) { }

    QMap<QString, QString> getAllParams() override {
        QMap<QString, QString> result = {{"someCustomField", someCustomField ? "true" : "false"}};
        result.insert(BasicBackendlessRegisterUser::getAllParams());
        return result;
    }

protected:
    bool someCustomField;
};

class registerscreen : public QWidget
{
    Q_OBJECT
public:
    registerscreen(QWidget *parent = nullptr);
    ~registerscreen();

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


};

#endif // REGISTERSCREEN_H
