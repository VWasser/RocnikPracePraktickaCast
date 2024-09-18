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
#include "BackendlessUserAPI.hpp"

BackendlessUserAPI::BackendlessUserAPI(QNetworkAccessManager* _networkAccessManager, QString _appId, QString _apiKey, QString _endpoint): QObject(),
    networkAccessManager(_networkAccessManager),
    appId(_appId),
    apiKey(_apiKey),
    endpoint(_endpoint) {

}

void BackendlessUserAPI::registerUser(BackendlessRegisterUserRepresentable& user) {
    return request(
        networkAccessManager,
        this,
        endpoint + appId + "/" + apiKey + "/users/register",
        user.getAllParams(),
        true,
        [&](QNetworkReply* reply){
            auto replyValue = reply->readAll();
            qDebug() << replyValue;

            emit registerUserResult();
        }
    );
}

void BackendlessUserAPI::signInUser(QString login, QString password) {
    return request(
        networkAccessManager,
        this,
        endpoint + appId + "/" + apiKey + "/users/login",
        {
            {"login", login},
            {"password", password}
        }, true, [&](QNetworkReply* reply){
            auto replyValue = reply->readAll();
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

void BackendlessUserAPI::validateUserToken() {
    return request(
        networkAccessManager,
        this,
        endpoint + appId + "/" + apiKey + "/users/isvalidusertoken/" + userToken,
        {

        }, false, [&](QNetworkReply* reply){
            auto replyValue = reply->readAll();
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
    return request(
        networkAccessManager,
        this,
        endpoint + appId + "/" + apiKey + "/users/restorepassword/" + email,
        {

        }, false, [&](QNetworkReply* reply){
            auto replyValue = reply->readAll();
            qDebug() << replyValue;

            emit restorePasswordSuccess(replyValue);
        }
    );
}
