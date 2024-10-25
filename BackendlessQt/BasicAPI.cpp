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
    QNetworkAccessManager* networkAccessManager,
    const QObject* context,
    QString urlString,
    PostParams customParams,
    BERequestMethod method,
    std::function<void(QByteArray)> const& handleRequest
) {
    QUrl url(urlString);
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QString params = "{";

    for (auto [key, value] : customParams.asKeyValueRange()) {
        params += "\"";
        params += key;
        params += "\"";
        params += ":";
        params += value->asParam();
        params += ",";
    }

    params.removeLast();
    params += "}";

    QObject::connect(networkAccessManager, &QNetworkAccessManager::finished, context, [handleRequest](QNetworkReply* reply) {
        handleRequest(reply->readAll());
    }, Qt::SingleShotConnection);
    switch (method) {
    case BERequestMethod::get:
        networkAccessManager->get(request);
        break;
    case BERequestMethod::post:
        networkAccessManager->post(request, params.toUtf8());
        break;
    case BERequestMethod::deleteResource:
        networkAccessManager->deleteResource(request);
        break;
    case BERequestMethod::put:
        networkAccessManager->put(request, params.toUtf8());
        break;
    }
}

