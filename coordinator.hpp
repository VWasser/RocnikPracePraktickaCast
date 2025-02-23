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

struct InputAbsenceData: ShowBasicData {
    QString name;

    InputAbsenceData(QString _name): name(_name) { }
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
    void hideAllScreens(Screen exeption, ShowBasicData* data = new ShowBasicData());
    void implementMenuBar(QBoxLayout *layout);
public:
    int hourStart;
    int dayOfWeek;
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
