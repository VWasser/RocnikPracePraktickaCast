#include <QtTest>
#include <QSignalSpy>
#include "../BasicAPI.hpp"
#include "../BackendlessUser.hpp"

class BackendlessQtTests: public QObject {
    Q_OBJECT

public:
    BackendlessQtTests();
    ~BackendlessQtTests();

private slots:
    void initTestCase();
    void test1();
    void cleanupTestCase();
};

BackendlessQtTests::BackendlessQtTests() {

}

BackendlessQtTests::~BackendlessQtTests() {

}

void BackendlessQtTests::initTestCase() {

}

void BackendlessQtTests::test1() {
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

void BackendlessQtTests::cleanupTestCase() {

}

QTEST_MAIN(BackendlessQtTests)

#include "test.moc"
