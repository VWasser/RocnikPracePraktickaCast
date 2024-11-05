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

BackendlessAPI::BackendlessAPI(AnyNetworkAccessManager* _networkAccessManager, QString _appId, QString _apiKey, QString _endpoint): QObject(),
    networkAccessManager(_networkAccessManager),
    userAPI(_networkAccessManager, _appId, _apiKey, _endpoint),
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
        [&](auto replyValue){
            qDebug() << replyValue;
            emit itemAdded();
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
        [&](auto replyValue){
            qDebug() << replyValue;
            extractResult<DeletionResult>(
                replyValue,
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

void BackendlessAPI::loadTableItems(QString tableName, int pageSize, int offset) {
    request(
        networkAccessManager,
        this,
        endpoint + appId + "/" + apiKey + "/data/" + tableName + "?pageSize=" + QString::number(pageSize) + "&offset=" + QString::number(offset),
        {

        },
        BERequestMethod::get,
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
        [&](auto replyValue){
            qDebug() << replyValue;

            emit getItemsCountSuccess(replyValue.toInt());
        }
    );
}
