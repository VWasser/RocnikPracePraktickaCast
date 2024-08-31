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
    QMap<QString, QString> customParams,
    bool isPost,
    std::function<void(QNetworkReply*)> const& handleRequest
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
        params += "\"";
        params += value;
        params += "\"";
        params += ",";
    }

    params.removeLast();
    params += "}";

    QObject::connect(networkAccessManager, &QNetworkAccessManager::finished, context, [handleRequest](QNetworkReply* reply) {
        handleRequest(reply);
    }, Qt::SingleShotConnection);
    if (isPost) {
        networkAccessManager->post(request, params.toUtf8());
    } else {
        networkAccessManager->get(request);
    }
}

