//
//  BackendlessUserAPI.cpp
//  BackendlessQt
//
//  Created by Roman Podymov on 07/08/2024.
//  Copyright © 2024 BackendlessQt. All rights reserved.
//

#include <QNetworkAccessManager>
#include <QUrlQuery>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>
#include <QFile>
#include "BackendlessUserAPI.hpp"

BackendlessUserAPI::BackendlessUserAPI(AnyNetworkAccessManager* _networkAccessManager, QString _appId, QString _apiKey, QString _endpoint): QObject(),
    networkAccessManager(_networkAccessManager),
    appId(_appId),
    apiKey(_apiKey),
    endpoint(_endpoint) {
    readTokenFromDisk();
    qDebug() << userTokenValue;
}

void BackendlessUserAPI::registerUser(BackendlessRegisterUserRepresentable& user) {
    request(
        networkAccessManager,
        this,
        endpoint + appId + "/" + apiKey + "/users/register",
        user.getAllParams(),
        BERequestMethod::post,
        {},
        [&](auto replyValue){
            qDebug() << replyValue;

            emit registerUserResult();
        }
    );
}

void BackendlessUserAPI::signInUser(QString login, QString password) {
    request(
        networkAccessManager,
        this,
        endpoint + appId + "/" + apiKey + "/users/login",
        {
            {"login", new StringPostParam(login)},
            {"password", new StringPostParam(password)}
        },
        BERequestMethod::post,
        {},
        [&](auto replyValue){
            qDebug() << replyValue;

            #ifdef BACKENDLESS_VARIANT_RESPONSE
            extractResult(
                replyValue,
                [=](auto user) {
                    emit signInUserResult(user);
                },
                [=](auto beError) {
                    emit signInUserResult(beError);
                },
                [=](auto jsonError) {
                    emit signInUserResult(jsonError);
                }
            );
            #else
            extractResult<BackendlessSignInUser>(
                replyValue,
                [&](auto user) {
                    userTokenValue = user.userToken;
                    saveTokenOnDisk();
                    emit signInUserSuccess(user);
                },
                [&](auto beError) {
                    emit signInUserErrorBackendless(beError);
                },
                [&](auto jsonError) {
                    emit signInUserErrorJson(jsonError);
                }
            );
            #endif
        }
    );
}

QString BackendlessUserAPI::tokenFilePath() {
    auto path = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    return path + "/backendless_token.txt";
}

void BackendlessUserAPI::readTokenFromDisk() {
    QFile file(tokenFilePath());
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        stream >> userTokenValue;
    }
    file.close();
}

void BackendlessUserAPI::saveTokenOnDisk() {
    QFile file(tokenFilePath());
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << userTokenValue;
    }
    file.close();
}

void BackendlessUserAPI::removeTokenFromDisk() {
    QFile file(tokenFilePath());
    file.remove();
}

void BackendlessUserAPI::validateUserToken() {
    request(
        networkAccessManager,
        this,
        endpoint + appId + "/" + apiKey + "/users/isvalidusertoken/" + userTokenValue,
        {

        },
        BERequestMethod::get,
        {},
        [&](auto replyValue) {
            qDebug() << replyValue;

            #ifdef BACKENDLESS_VARIANT_RESPONSE
            if (replyValue == "true") {
                emit validateUserTokenResult(true);
            } else if (replyValue == "false") {
                emit validateUserTokenResult(false);
            } else {
                emit validateUserTokenResult(BackendlessValidateUserTokenError::invalidResponse);
            }
            #else
            if (replyValue == "true") {
                emit validateUserTokenSuccess(true);
            } else if (replyValue == "false") {
                emit validateUserTokenSuccess(false);
            } else {
                emit validateUserTokenError(BackendlessValidateUserTokenError::invalidResponse);
            }
            #endif
        }
    );
}

void BackendlessUserAPI::restorePassword(QString email) {
    request(
        networkAccessManager,
        this,
        endpoint + appId + "/" + apiKey + "/users/restorepassword/" + email,
        {

        },
        BERequestMethod::get,
        {},
        [&](auto replyValue){
            qDebug() << replyValue;

            emit restorePasswordSuccess(replyValue);
        }
    );
}

void BackendlessUserAPI::logout() {
    request(
        networkAccessManager,
        this,
        endpoint + appId + "/" + apiKey + "/users/logout",
        {

        },
        BERequestMethod::get,
        {{"user-token", userTokenValue}},
        [&](auto replyValue){
            qDebug() << replyValue;

            userTokenValue = "";
            removeTokenFromDisk();

            emit restorePasswordSuccess(replyValue);
        }
    );
}

QString BackendlessUserAPI::userToken() {
    return userTokenValue;
}
