#ifndef COORDINATOR_HPP
#define COORDINATOR_HPP

#include "absencewindow.hpp"
#include "gradeswindow.hpp"
#include "registerscreen.hpp"
#include "menuwindow.hpp"
#include "settingsWindow.hpp"
#include "signinscreen.hpp"
#include "screenwidget.hpp"
#include <QObject>
#include <QPointer>

enum class Screen {
    SignIn,
    Register,
    Schedule,
    Menu,
    Absence,
    InputAbsence,
    Grades,
    Settings
};

enum absenceTypes {
    OK = 0,
    UNSOLVED = 1,
    MISSED = 2,
    LATE = 3,
    SCHOOL = 4
};
class InputAbsenceData: public ShowBasicData {
    Q_OBJECT

public:
    InputAbsenceData(int _day, int _hour): day(_day), hour(_hour) { }

    int day;
    int hour;
};

class Coordinator : public QObject {
    Q_OBJECT

public:
    explicit Coordinator(QObject *parent = nullptr);
    ~Coordinator();
    absenceTypes getAbsenceType(int) const;

    void showSignInScreen();
    void showMenuWindow();
    void showAbsenceWindow();
    void showGradesWindow();
    void showInputAbsence(QSharedPointer<InputAbsenceData> data);
    void showRegisterScreen();
    void showSettingsWindow();
    void showSchedule();
    void sendAbsenceSchedule();
    void hideAllScreens(
        Screen exeption,
        QSharedPointer<ShowBasicData> data = QSharedPointer<ShowBasicData>(new ShowBasicData())
    );
    void implementMenuBar(QBoxLayout *layout);



private:
    QMap<Screen, ScreenWidget*>windows;

private:
    //had to refrain from using shared pointer,
    //it was making an error while making hide all function
    QPointer<absenceWindow> abscWin;
    QPointer<gradesWindow> gradeWin;
    QPointer<inputAbsence> absencePopUp;
    QPointer<menuWindow> menuWin;
    QPointer<registerscreen> registerWindow;
    QPointer<settingsWindow> popUpWindow;
    QPointer<Schedule> scheduleWindow;
    QPointer<SignInScreen> signInWindow;

signals:
    void sendScheduleAbsence();
    void sendImputAbsence();

};

#endif // COORDINATOR_HPP
