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
#include <QNetworkAccessManager>
#include "BackendlessUserAPI.hpp"

#if defined MAKE_BACKENDLESS_LIB
#define BACKENDLESS_LIB_EXPORT Q_DECL_EXPORT
#else
#define BACKENDLESS_LIB_EXPORT Q_DECL_IMPORT
#endif

class BACKENDLESS_LIB_EXPORT BackendlessAPI: public QObject, public BasicAPI {
    Q_OBJECT

public:
    BackendlessAPI(QString _appId, QString _apiKey, QString _endpoint = "https://eu-api.backendless.com/");
    void addItemToTable(QString, QMap<QString, QString>);
    void loadTableItems(QString);
    ~BackendlessAPI();

signals:
    void itemAdded();
#ifdef BACKENDLESS_VARIANT_RESPONSE

#else
    void loadTableItemsSuccess(QString);
    void loadTableItemsError(BackendlessErrorCode);
#endif

public:
    BackendlessUserAPI userAPI;

private:
    QNetworkAccessManager networkAccessManager;
    QString appId;
    QString apiKey;
    QString endpoint;
};

#endif
