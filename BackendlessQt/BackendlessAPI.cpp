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

BackendlessAPI::BackendlessAPI(QString _appId, QString _apiKey, QString _endpoint): QObject(),
    userAPI(&networkAccessManager, _appId, _apiKey, _endpoint),
    appId(_appId),
    apiKey(_apiKey),
    endpoint(_endpoint) {

}

BackendlessAPI::~BackendlessAPI() {

}

void BackendlessAPI::addItemToTable(QString tableName, QMap<QString, QString> params) {
    return request(
        &networkAccessManager,
        this,
        endpoint + appId + "/" + apiKey + "/data/" + tableName,
        params, true, [&](QNetworkReply* reply){
            auto replyValue = reply->readAll();
            qDebug() << replyValue;
            emit itemAdded();
        }
    );
}

void BackendlessAPI::loadTableItems(QString tableName) {
    return request(
        &networkAccessManager,
        this,
        endpoint + appId + "/" + apiKey + "/data/" + tableName,
        {

        }, false, [&](QNetworkReply* reply){
            auto replyValue = reply->readAll();
            qDebug() << replyValue;
#ifdef BACKENDLESS_VARIANT_RESPONSE

#else
            emit loadTableItemsSuccess(replyValue);
#endif
        }
    );
}
