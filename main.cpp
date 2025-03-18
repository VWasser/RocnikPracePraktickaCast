#include <QApplication>
#include <QTranslator>
#include "httpclient.hpp"
#include "BackendlessQt/StandardNetworkManager.hpp"
#include "coordinator.hpp"
#include "burger-menu/src/burgermenu.h"

BackendlessAPI* api;
AnyNetworkAccessManager* networkManager;
HttpClient* customHttpClient;
Coordinator* coordinator;
BurgerMenu* burger;

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
    /*coordinator = new Coordinator();

    coordinator->showMenuWindow();*/

    burger = new BurgerMenu();
    burger->addMenuAction(new QAction("Hello"));
    burger->addMenuAction("Other");
    burger->show();

    return myApp.exec();
}
