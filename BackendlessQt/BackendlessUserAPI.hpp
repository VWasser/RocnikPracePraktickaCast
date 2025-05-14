//
//  BackendlessUserAPI.hpp
//  BackendlessQt
//
//  Created by Roman Podymov on 07/08/2024.
//  Copyright © 2024 BackendlessQt. All rights reserved.
//

#ifndef BACKENDLESS_USER_API_H
#define BACKENDLESS_USER_API_H

// #define BACKENDLESS_VARIANT_RESPONSE

#include <QString>
#include <QMap>
#include <QNetworkAccessManager>
#include <QJsonParseError>
#include "BackendlessUser.hpp"
#include "BasicAPI.hpp"

class AnyNetworkAccessManager;

class BackendlessSignInUserCoder: public Coder {
    Codable* decode(QJsonObject obj) override {
        return new BackendlessSignInUser(obj);
    }

    void write(QTextStream& stream, QSharedPointer<Codable> codable, QSharedPointer<Codable> defaultValue) override {
        auto userValue = (BackendlessSignInUser*)(defaultValue.get() ? defaultValue.get() : codable.get());
        stream << userValue->userToken << Qt::endl;
        stream << userValue->email << Qt::endl;
        stream << userValue->name << Qt::endl;
    }

    Codable* read(QTextStream& stream) override {
        auto result = new BackendlessSignInUser();
        stream >> result->userToken >> Qt::endl;
        stream >> result->email >> Qt::endl;
        stream >> result->name >> Qt::endl;
        return result;
    }
};

class BackendlessUserAPI: public QObject, public BasicAPI {
    Q_OBJECT

    friend class BackendlessQtTests;

public:
    BackendlessUserAPI(AnyNetworkAccessManager*, QSharedPointer<Coder> coder, QString _appId, QString _apiKey, QString _endpoint = "https://eu-api.backendless.com/");

    void registerUser(BackendlessRegisterUserRepresentable&);
    void signInUser(QString, QString);
    void validateUserToken();
    void restorePassword(QString);
    void logout();
    BackendlessSignInUser* user() const {
        return userValue.get();
    }

private:
    QString tokenFilePath();
    void readUserFromDisk();
    void saveUserOnDisk(QSharedPointer<BackendlessSignInUser> = QSharedPointer<BackendlessSignInUser>(nullptr));
    void removeUserFromDisk();

signals:
    void registerUserResult();

#ifdef BACKENDLESS_VARIANT_RESPONSE
    void signInUserResult(std::variant<BackendlessSignInUser, BackendlessError, QJsonParseError>);
#else
    void signInUserSuccess(BackendlessSignInUser*);
    void signInUserErrorBackendless(BackendlessError);
    void signInUserErrorJson(QJsonParseError);
#endif

#ifdef BACKENDLESS_VARIANT_RESPONSE
    void validateUserTokenResult(std::variant<bool, BackendlessValidateUserTokenError>);
#else
    void validateUserTokenSuccess(bool);
    void validateUserTokenError(BackendlessValidateUserTokenError);
#endif

    void restorePasswordSuccess(QString);
    void logoutSuccess();

private:
    AnyNetworkAccessManager* networkAccessManager;
    QSharedPointer<Coder> coder;
    QString appId;
    QString apiKey;
    QString endpoint;
    QSharedPointer<BackendlessSignInUser> userValue;
};

#endif
