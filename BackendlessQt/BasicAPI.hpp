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
#include <QJsonParseError>

class PostParam {
public:
    virtual ~PostParam() = default;
    virtual QString asParam() = 0;
};

typedef QMap<QString, PostParam*> PostParams;

class StringPostParam: public PostParam {
public:
    StringPostParam(QString _value): value(_value) { }

    QString asParam() override {
        return "\"" + value + "\"";
    }

private:
    QString value;
};

template<typename T>
class NumericPostParam: public PostParam {
public:
    NumericPostParam(int _value): value(_value) { }

    QString asParam() override {
        return QString::number(value);
    }

private:
    T value;
};

enum class BackendlessErrorCode {
    noError = 0,
    entityNotFound = 1000,
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
    std::function<void(T)> const& onSuccess,
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
        onSuccess(
            T(
                jsonObject
            )
        );
        break;
    default:
        onBEError(BackendlessError(
            code,
            jsonObject["message"].toString()
        ));
    }
}

enum class BERequestMethod {
    get,
    post,
    put,
    deleteResource
};

class AnyNetworkAccessManager {
public:
    virtual void get(QString, QMap<QString, QString>, const QObject*, std::function<void(QByteArray)> const&) = 0;
    virtual void post(QString, QMap<QString, QString>, PostParams, const QObject*, std::function<void(QByteArray)> const&) = 0;
    virtual void put(QString, QMap<QString, QString>, PostParams, const QObject*, std::function<void(QByteArray)> const&) = 0;
    virtual void deleteResource(QString, QMap<QString, QString>, const QObject*, std::function<void(QByteArray)> const&) = 0;
};

class BasicAPI {
protected:
    void request(
        AnyNetworkAccessManager*,
        const QObject*,
        QString,
        PostParams,
        BERequestMethod,
        QMap<QString, QString>,
        std::function<void(QByteArray)> const&
    );
};

#endif
