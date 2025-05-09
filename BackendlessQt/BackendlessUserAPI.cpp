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
    endpoint(_endpoint),
    userValue(nullptr) {
    readTokenFromDisk();
}

BackendlessUserAPI::~BackendlessUserAPI() {
    delete userValue;
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

void BackendlessUserAPI::signInUser(QString login, QString password, std::function<BackendlessSignInUser*(QJsonObject)> const& decoder) {
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
        [this, decoder](auto replyValue){
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
                decoder,
                [&](auto user) {
                    userValue = user;
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
        userValue = new BackendlessSignInUser();
        stream >> userValue->userToken;
    }
    file.close();
}

void BackendlessUserAPI::saveTokenOnDisk(QString additionalValue) {
    QFile file(tokenFilePath());
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << (additionalValue.isEmpty() ? userValue->userToken : additionalValue);
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
        endpoint + appId + "/" + apiKey + "/users/isvalidusertoken/" + userValue->userToken,
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
        {{"user-token", userValue->userToken}},
        [&](auto replyValue){
            qDebug() << replyValue;

            delete userValue;
            userValue = nullptr;
            removeTokenFromDisk();

            emit logoutSuccess();
        }
    );
}

BackendlessSignInUser* BackendlessUserAPI::user() {
    return userValue;
}
