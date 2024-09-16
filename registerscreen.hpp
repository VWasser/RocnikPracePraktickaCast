#ifndef REGISTERSCREEN_H
#define REGISTERSCREEN_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QBoxLayout>
#include <QCheckBox>


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
