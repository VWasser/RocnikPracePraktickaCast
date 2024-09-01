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

enum class BackendlessErrorCode {
    noError = 0,
    invalidLoginOrPassword = 3003
};

enum class BackendlessValidateUserTokenError {
    invalidResponse
};

struct BackendlessError {
    BackendlessErrorCode code;
    QString message;

    BackendlessError(
        BackendlessErrorCode _code,
        QString _message
    ): code(_code), message(_message) { }
};

class BackendlessUserAPI: public QObject, public BasicAPI {
    Q_OBJECT

public:
    BackendlessUserAPI(QNetworkAccessManager*, QString _appId, QString _apiKey, QString _endpoint = "https://eu-api.backendless.com/");

    void registerUser(BackendlessRegisterUser);
    void signInUser(QString, QString);
    void validateUserToken();
    void restorePassword(QString);

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
    void extractResult(
        QByteArray replyValue,
        std::function<void(BackendlessSignInUser)> const& onUser,
        std::function<void(BackendlessError)> const& onBEError,
        std::function<void(QJsonParseError)> const& onJSONError
    );

private:
    QNetworkAccessManager* networkAccessManager;
    QString appId;
    QString apiKey;
    QString endpoint;
    QString userToken;
};

#endif
