#include <QtTest>
#include <QSignalSpy>
#include "../BasicAPI.hpp"
#include "../BackendlessUserAPI.hpp"
#include "../BackendlessUser.hpp"

class BackendlessQtTests: public QObject {
    Q_OBJECT

public:
    BackendlessQtTests();
    ~BackendlessQtTests();

private slots:
    void initTestCase();
    void testGetAllParams();
    void testDisk();
    void cleanupTestCase();
};

BackendlessQtTests::BackendlessQtTests() {

}

BackendlessQtTests::~BackendlessQtTests() {

}

void BackendlessQtTests::initTestCase() {

}

void BackendlessQtTests::testGetAllParams() {
    // Given
    QString email = "email@email.com";
    QString password = "somePassword";
    BasicBackendlessRegisterUser user(email, password);

    // When
    auto emailAsParam = user.getAllParams()["email"]->asParam();
    auto passwordAsParams = user.getAllParams()["password"]->asParam();

    // Then
    QCOMPARE(emailAsParam, "\"" + email + "\"");
    QCOMPARE(passwordAsParams, "\"" + password + "\"");
}

void BackendlessQtTests::testDisk() {
    // Given
    auto token = "Hello";
    BackendlessUserAPI userAPI(nullptr, "", "", "");

    // When
    userAPI.removeTokenFromDisk();
    userAPI.saveTokenOnDisk(token);
    userAPI.readTokenFromDisk();

    // Then
    QCOMPARE(userAPI.user()->userToken, token);
}

void BackendlessQtTests::cleanupTestCase() {

}

QTEST_MAIN(BackendlessQtTests)

#include "test.moc"
