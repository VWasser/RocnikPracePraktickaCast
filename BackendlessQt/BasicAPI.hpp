//
//  BasicAPI.hpp
//  BackendlessQt
//
//  Created by Roman Podymov on 09/08/2024.
//  Copyright © 2024 BackendlessQt. All rights reserved.
//

#ifndef BASIC_API_H
#define BASIC_API_H

#include <QString>
#include <QMap>
#include <QNetworkAccessManager>
#include <QJsonObject>

enum class BackendlessErrorCode {
    noError = 0,
    unknownEntity = 1009,
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

template<typename T>
void extractResult(
    QByteArray replyValue,
    std::function<void(T)> const& onUser,
    std::function<void(BackendlessError)> const& onBEError,
    std::function<void(QJsonParseError)> const& onJSONError
) {
    QJsonParseError jsonError;
    auto jsonResponse = QJsonDocument::fromJson(replyValue, &jsonError);

    switch (jsonError.error) {
    case QJsonParseError::NoError:
        break;
    default:
        onJSONError(jsonError);
        return;
    }

    auto jsonObject = jsonResponse.object();
    auto code = static_cast<BackendlessErrorCode>(jsonObject["code"].toInt());
    switch (code) {
    case BackendlessErrorCode::noError:
        onUser(T(
            jsonObject["user-token"].toString()
        ));
        break;
    default:
        onBEError(BackendlessError(
            code,
            jsonObject["message"].toString()
        ));
    }
}

class BasicAPI {
protected:
    void request(QNetworkAccessManager*, const QObject*, QString, QMap<QString, QString>, bool, std::function<void(QNetworkReply*)> const&);
};

#endif
