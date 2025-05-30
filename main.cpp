#include <QApplication>
#include <QTranslator>
#include "httpclient.hpp"
#include "BackendlessQt/StandardNetworkManager.hpp"
#include "coordinator.hpp"

BackendlessAPI* api;
AnyNetworkAccessManager* networkManager;
HttpClient* customHttpClient;
Coordinator* coordinator;

void reloadScreen() {
    auto user = api->userAPI.user();
    if (!user || user->userToken.isEmpty()) {
        coordinator->showSignInScreen();
    } else {
        coordinator->showMenuWindow();
    }
}

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
    auto coder = QSharedPointer<BackendlessSignInUserCoder>(new BachelorSignInUserCoder());
    api = new BackendlessAPI(
        networkManager,
        coder,
        "7D2C33DB-05E2-4FD9-B26B-46FDB17F56D6",
        "19CB95DB-0235-4134-B1FB-C64750DE49E2"
    );
    coordinator = new Coordinator();

    QObject::connect(&api->userAPI, &BackendlessUserAPI::logoutSuccess, [&](){
        reloadScreen();
    });
    reloadScreen();

    return myApp.exec();
}
