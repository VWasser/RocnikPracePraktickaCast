#ifndef COORDINATOR_HPP
#define COORDINATOR_HPP

#include "BackendlessQt/BackendlessAPI.hpp"
#include "absencewindow.hpp"
#include "gradeswindow.hpp"
#include "httpclient.hpp"
#include "menuwindow.hpp"
#include "settingsWindow.hpp"
#include "signinscreen.hpp"
#include <QObject>
#include <QPointer>

class Coordinator : public QObject {
    Q_OBJECT

public:
    explicit Coordinator(QObject *parent = nullptr);
    ~Coordinator();

    void showSignInScreen();
    void showMenuWindow();
    void showAbsenceWindow();
    void showGradesWindow();
    void showInputAbsence();
    void showRegisterScreen();
    void showSettingsWindow();
    void showSchedule();
    void sendAbsenceSchedule();

private:
    QPointer<absenceWindow> abscWin;
    QPointer<gradesWindow> gradeWin;
    QPointer<inputAbsence> absencePopUp;
    QPointer<menuWindow> menuWin;
    QPointer<registerscreen> myWindow2;
    QPointer<settingsWindow> popUpWindow;
    QPointer<Schedule> myWindow3;
    QPointer<SignInScreen> myWindow;

signals:
    void sendScheduleAbsence();

};

#endif // COORDINATOR_HPP
