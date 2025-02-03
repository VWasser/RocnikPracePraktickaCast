//
//  StandardNetworkManager.cpp
//  BackendlessQt
//
//  Created by Roman Podymov on 27/10/2024.
//  Copyright © 2024 BackendlessQt. All rights reserved.
//

#include "StandardNetworkManager.hpp"
#include <QNetworkRequest>
#include <QNetworkReply>

void StandardNetworkManager::get(QString urlString, QMap<QString, QString> headers, const QObject* context, std::function<void(QByteArray)> const& handleRequest) {
    QUrl url(urlString);
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    for (auto [key, value] : headers.asKeyValueRange()) {
        request.setRawHeader(key.toUtf8(), value.toUtf8());
    }

    QObject::connect(&manager, &QNetworkAccessManager::finished, context, [handleRequest](auto reply) {
        handleRequest(reply->readAll());
    }, Qt::SingleShotConnection);
    manager.get(request);
}

void StandardNetworkManager::post(QString urlString, QMap<QString, QString> headers, PostParams customParams, const QObject* context, std::function<void(QByteArray)> const& handleRequest) {
    QUrl url(urlString);
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    for (auto [key, value] : headers.asKeyValueRange()) {
        request.setRawHeader(key.toUtf8(), value.toUtf8());
    }

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

    QObject::connect(&manager, &QNetworkAccessManager::finished, context, [handleRequest](auto reply) {
        handleRequest(reply->readAll());
    }, Qt::SingleShotConnection);
    manager.post(request, params.toUtf8());
}

void StandardNetworkManager::put(QString urlString, QMap<QString, QString> headers, PostParams customParams, const QObject* context, std::function<void(QByteArray)> const& handleRequest) {
    QUrl url(urlString);
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    for (auto [key, value] : headers.asKeyValueRange()) {
        request.setRawHeader(key.toUtf8(), value.toUtf8());
    }

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

    QObject::connect(&manager, &QNetworkAccessManager::finished, context, [handleRequest](auto reply) {
        handleRequest(reply->readAll());
    }, Qt::SingleShotConnection);
    manager.put(request, params.toUtf8());
}

void StandardNetworkManager::deleteResource(QString urlString, QMap<QString, QString> headers, const QObject* context, std::function<void(QByteArray)> const& handleRequest) {
    QUrl url(urlString);
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    for (auto [key, value] : headers.asKeyValueRange()) {
        request.setRawHeader(key.toUtf8(), value.toUtf8());
    }

    QObject::connect(&manager, &QNetworkAccessManager::finished, context, [handleRequest](auto reply) {
        handleRequest(reply->readAll());
    }, Qt::SingleShotConnection);
    manager.deleteResource(request);
}
