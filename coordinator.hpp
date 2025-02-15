#ifndef COORDINATOR_HPP
#define COORDINATOR_HPP

#include "absencewindow.hpp"
#include "gradeswindow.hpp"
#include "httpclient.hpp"
#include "menuwindow.hpp"
#include "settingsWindow.hpp"
#include "signinscreen.hpp"
#include <QObject>
#include <QPointer>

enum class Screen {
    SignIn,
    Register,
    Schedule,
    Menu,
    Absence,
    Grades,
    Settings
};

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
    QSharedPointer<absenceWindow> abscWin;
    QPointer<gradesWindow> gradeWin;
    QPointer<inputAbsence> absencePopUp;
    QPointer<menuWindow> menuWin;
    QPointer<registerscreen> registerWindow;
    QPointer<settingsWindow> popUpWindow;
    QPointer<Schedule> scheduleWindow;
    QPointer<SignInScreen> signInWindow;

signals:
    void sendScheduleAbsence();

};

#endif // COORDINATOR_HPP
