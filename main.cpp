#include "menuwindow.hpp"
#include "registerscreen.hpp"
#include "schedule.hpp"
#include "signinscreen.hpp"
#include "settingsWindow.hpp"
#include "httpclient.hpp"
#include <QApplication>
#include <QTranslator>
#include "BackendlessQt/StandardNetworkManager.hpp"
#include "BackendlessQt/BackendlessAPI.hpp"
#include "mocknetworkmanager.hpp"
#include <QQuickView>
#include <QGuiApplication>

BackendlessAPI* api;
SignInScreen* myWindow;
registerscreen* myWindow2;
Schedule* myWindow3;
settingsWindow* popUpWindow;
AnyNetworkAccessManager* networkManager;
HttpClient* customHttpClient;
menuWindow* menuWin;
gradesWindow* gradeWin;
absenceWindow* abscWin;


int main(int argc, char *argv[])
{
    /*QTranslator translator;
    auto loadResult = translator.load(":/strings");
    if (!loadResult) {
        exit(1);
    }


    QApplication myApp(argc, argv);
    myApp.installTranslator(&translator);

    customHttpClient = new HttpClient();
    networkManager = new StandardNetworkManager();
    api = new BackendlessAPI(networkManager, "7D2C33DB-05E2-4FD9-B26B-46FDB17F56D6", "19CB95DB-0235-4134-B1FB-C64750DE49E2");
    myWindow = new SignInScreen();
    myWindow2 = new registerscreen();
    myWindow3 = new Schedule();
    popUpWindow = new settingsWindow();
    menuWin = new menuWindow();
    gradeWin = new gradesWindow();
    abscWin = new absenceWindow();

    menuWin->show();*/

    QGuiApplication myApp(argc, argv);
    QQuickView* view = new QQuickView();
    /*QFile url(":/qml/example.qml");
    if (!url.isValid()) {
        exit(1);
    }*/
    //view->setSource(QUrl::fromLocalFile("/Users/romanpodymov/FinanceTracker/App/example.qml"));
    view->setSource(QUrl("qrc:/qml/example.qml"));
    view->show();


    return myApp.exec();
}
