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

class BackendlessUserAPI: public QObject, public BasicAPI {
    Q_OBJECT

public:
    BackendlessUserAPI(AnyNetworkAccessManager*, QString _appId, QString _apiKey, QString _endpoint = "https://eu-api.backendless.com/");

    void registerUser(BackendlessRegisterUserRepresentable&);
    void signInUser(QString, QString);
    void validateUserToken();
    void restorePassword(QString);
    void logout();
    QString userToken();

private:
    QString tokenFilePath();
    void readTokenFromDisk();
    void saveTokenOnDisk();
    void removeTokenFromDisk();

signals:
    void registerUserResult();

#ifdef BACKENDLESS_VARIANT_RESPONSE
    void signInUserResult(std::variant<BackendlessSignInUser, BackendlessError, QJsonParseError>);
#else
    void signInUserSuccess(BackendlessSignInUser);
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

private:
    AnyNetworkAccessManager* networkAccessManager;
    QString appId;
    QString apiKey;
    QString endpoint;
    QString userTokenValue;
};

#endif
