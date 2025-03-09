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

    void showSignInScreen();
    void showMenuWindow();
    void showAbsenceWindow();
    void showGradesWindow();
    void showInputAbsence(InputAbsenceData* data);
    void showRegisterScreen();
    void showSettingsWindow();
    void showSchedule();
    void sendAbsenceSchedule();
    void hideAllScreens(Screen exeption, ShowBasicData* data = new ShowBasicData(), ShowBasicData2 *data2 = new ShowBasicData2());
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
