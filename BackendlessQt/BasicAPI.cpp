//
//  BasicAPI.cpp
//  BackendlessQt
//
//  Created by Roman Podymov on 09/08/2024.
//  Copyright © 2024 BackendlessQt. All rights reserved.
//

#include <QNetworkAccessManager>
#include <QUrlQuery>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include "BasicAPI.hpp"

void BasicAPI::request(
    AnyNetworkAccessManager* networkAccessManager,
    const QObject* context,
    QString urlString,
    PostParams customParams,
    BERequestMethod method,
    std::function<void(QByteArray)> const& handleRequest
) {
    switch (method) {
    case BERequestMethod::get:
        networkAccessManager->get(urlString, context, handleRequest);
        break;
    case BERequestMethod::post:
        networkAccessManager->post(urlString, customParams, context, handleRequest);
        break;
    case BERequestMethod::deleteResource:
        networkAccessManager->deleteResource(urlString, context, handleRequest);
        break;
    case BERequestMethod::put:
        networkAccessManager->put(urlString, customParams, context, handleRequest);
        break;
    }
}

