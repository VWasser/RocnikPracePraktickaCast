//
//  BackendlessAPI.hpp
//  BackendlessQt
//
//  Created by Roman Podymov on 07/08/2024.
//  Copyright © 2024 BackendlessQt. All rights reserved.
//

#ifndef BACKENDLESS_API_H
#define BACKENDLESS_API_H

#include <QString>
#include <QMap>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include "BackendlessUserAPI.hpp"

struct DeletionResult {
    long deletionTime;

    DeletionResult(QJsonObject jsonObject): deletionTime(jsonObject["deletionTime"].toInteger()) { }
};

class AnyNetworkAccessManager;

class BackendlessAPI: public QObject, public BasicAPI {
    Q_OBJECT

public:
    BackendlessAPI(AnyNetworkAccessManager* _networkAccessManager, QString _appId, QString _apiKey, QString _endpoint = "https://eu-api.backendless.com/");
    void addItemToTable(QString, PostParams);
    void deleteItemFromTable(QString, QString);
    void loadTableItems(QString);

signals:
    void itemAdded();
    void deleteItemFromTableSuccess(DeletionResult);
    void deleteItemFromTableError(BackendlessError);
#ifdef BACKENDLESS_VARIANT_RESPONSE

#else
    void loadTableItemsSuccess(QString);
    void loadTableItemsError(BackendlessError);
#endif

public:
    BackendlessUserAPI userAPI;

private:
    AnyNetworkAccessManager* networkAccessManager;
    QString appId;
    QString apiKey;
    QString endpoint;
};

#endif
