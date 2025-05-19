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

BackendlessUserAPI::BackendlessUserAPI(AnyNetworkAccessManager* _networkAccessManager, QSharedPointer<Coder> coder, QString _appId, QString _apiKey, QString _endpoint): QObject(),
    networkAccessManager(_networkAccessManager),
    coder(coder),
    appId(_appId),
    apiKey(_apiKey),
    endpoint(_endpoint),
    userValue(nullptr) {
    readUserFromDisk();
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
    auto loginParam = QSharedPointer<StringPostParam>(new StringPostParam(login));
    auto passwordParam = QSharedPointer<StringPostParam>(new StringPostParam(password));
    request(
        networkAccessManager,
        this,
        endpoint + appId + "/" + apiKey + "/users/login",
        {
            {"login", loginParam.get()},
            {"password", passwordParam.get()}
        },
        BERequestMethod::post,
        {},
        [this](auto replyValue){
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
                coder.get(),
                [&](auto user) {
                    userValue = QSharedPointer<BackendlessSignInUser>(user);
                    saveUserOnDisk();
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

void BackendlessUserAPI::readUserFromDisk() {
    QFile file(tokenFilePath());
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        userValue = QSharedPointer<BackendlessSignInUser>((BackendlessSignInUser*)(coder->read(stream)));
    }
    file.close();
}

void BackendlessUserAPI::saveUserOnDisk(QSharedPointer<BackendlessSignInUser> additionalValue) {
    QFile file(tokenFilePath());
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        coder->write(stream, userValue, additionalValue);
    }
    file.close();
}

void BackendlessUserAPI::removeUserFromDisk() {
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
    if (!userValue) {
        return;
    }
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

            userValue.reset();
            removeUserFromDisk();

            emit logoutSuccess();
        }
    );
}
