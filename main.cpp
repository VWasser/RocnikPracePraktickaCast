#include "registerscreen.hpp"
#include "schedule.hpp"
#include "signinscreen.hpp"
#include "editmodescreen.hpp"
#include "httpclient.hpp"
#include <QApplication>
#include <QTranslator>
#include "BackendlessQt/StandardNetworkManager.hpp"
#include "BackendlessQt/BackendlessAPI.hpp"
#include "mocknetworkmanager.hpp"

BackendlessAPI* api;
SignInScreen* myWindow;
registerscreen* myWindow2;
Schedule* myWindow3;
editModeScreen* popUpWindow;
AnyNetworkAccessManager* networkManager;
HttpClient* customHttpClient;

int main(int argc, char *argv[])
{
    QTranslator translator;
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
    popUpWindow = new editModeScreen();

    myWindow3->show();


    return myApp.exec();
}
