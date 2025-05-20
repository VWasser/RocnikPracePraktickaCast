//
//  BackendlessAPI.cpp
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
#include "BackendlessAPI.hpp"

class DeletionResultCoder: public Coder {
    Codable* decode(QJsonObject obj) override {
        return new DeletionResult(obj);
    }

    void write(QTextStream&, QSharedPointer<Codable>, QSharedPointer<Codable>) override {

    }

    Codable* read(QTextStream&) override {
        return nullptr;
    }
};

BackendlessAPI::BackendlessAPI(
    AnyNetworkAccessManager* _networkAccessManager,
    QSharedPointer<BackendlessSignInUserCoder> _coder,
    QString _appId,
    QString _apiKey,
    QString _endpoint
): QObject(),
    userAPI(
        _networkAccessManager,
        _coder,
        _appId,
        _apiKey,
        _endpoint
    ),
    networkAccessManager(_networkAccessManager),
    appId(_appId),
    apiKey(_apiKey),
    endpoint(_endpoint) {

}

void BackendlessAPI::addItemToTable(QString tableName, PostParams params) {
    request(
        networkAccessManager,
        this,
        endpoint + appId + "/" + apiKey + "/data/" + tableName,
        params,
        BERequestMethod::post,
        {},
        [&](auto replyValue){
            qDebug() << replyValue;
            emit itemAdded();
        }
    );
}

void BackendlessAPI::editTableItem(QString tableName, QString whereClause, PostParams params) {
    auto requestURL = endpoint + appId + "/" + apiKey + "/data/" + tableName;
    if (!whereClause.isEmpty()) {
        requestURL += "?where=" + whereClause;
    }
    request(
        networkAccessManager,
        this,
        requestURL,
        params,
        BERequestMethod::put,
        {},
        [&](auto replyValue){
            qDebug() << replyValue;
            emit itemEdited();
        }
    );
}

void BackendlessAPI::deleteItemFromTable(QString tableName, QString objectId) {
    request(
        networkAccessManager,
        this,
        endpoint + appId + "/" + apiKey + "/data/" + tableName + "/" + objectId,
        {

        },
        BERequestMethod::deleteResource,
        {},
        [&](auto replyValue){
            qDebug() << replyValue;
            extractResult<DeletionResult>(
                replyValue,
                new DeletionResultCoder(),
                [&](auto result) {
                    emit deleteItemFromTableSuccess(result);
                },
                [&](auto beError) {
                    emit deleteItemFromTableError(beError);
                },
                [&](auto jsonError) {

                }
            );
        }
    );
}

void BackendlessAPI::loadTableItems(QString tableName, int pageSize, int offset, QString whereClause) {
    auto requestURL = endpoint + appId + "/" + apiKey + "/data/" + tableName + "?pageSize=" + QString::number(pageSize) + "&offset=" + QString::number(offset);
    if (!whereClause.isEmpty()) {
        requestURL += "&where=" + whereClause;
    }
    request(
        networkAccessManager,
        this,
        requestURL,
        {

        },
        BERequestMethod::get,
        {},
        [&](auto replyValue){
            qDebug() << replyValue;
#ifdef BACKENDLESS_VARIANT_RESPONSE

#else
            emit loadTableItemsSuccess(replyValue);
#endif
        }
    );
}

void BackendlessAPI::getItemsCount(QString tableName) {
    request(
        networkAccessManager,
        this,
        endpoint + appId + "/" + apiKey + "/data/" + tableName + "/count",
        {

        },
        BERequestMethod::get,
        {},
        [&](auto replyValue){
            qDebug() << replyValue;

            emit getItemsCountSuccess(replyValue.toInt());
        }
    );
}
