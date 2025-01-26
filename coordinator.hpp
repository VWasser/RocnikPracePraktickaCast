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


extern BackendlessAPI* api;
extern SignInScreen* myWindow;
extern registerscreen* myWindow2;
extern Schedule* myWindow3;
extern settingsWindow* popUpWindow;
extern AnyNetworkAccessManager* networkManager;
extern HttpClient* customHttpClient;
extern menuWindow* menuWin;
extern gradesWindow* gradeWin;
extern absenceWindow* abscWin;
extern inputAbsence* absencePopUp;


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

private:
    QPointer<absenceWindow> abscWin;
    QPointer<gradesWindow> gradeWin;
    QPointer<inputAbsence> absencePopUp;
    QPointer<menuWindow> menuWin;
    QPointer<registerscreen> myWindow2;
    QPointer<settingsWindow> popUpWindow;
    QPointer<Schedule> myWindow3;
    QPointer<SignInScreen> myWindow;
};

#endif // COORDINATOR_HPP
