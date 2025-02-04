#ifndef MOCKNETWORKMANAGER_H
#define MOCKNETWORKMANAGER_H

#include "BackendlessQt/BasicAPI.hpp"

class MockNetworkManager: public AnyNetworkAccessManager {
public:
    void get(QString, QMap<QString, QString>, const QObject*, std::function<void(QByteArray)> const&) override;
    void post(QString, QMap<QString, QString>, PostParams, const QObject*, std::function<void(QByteArray)> const&) override;
    void put(QString, QMap<QString, QString>, PostParams, const QObject* context, std::function<void(QByteArray)> const&) override;
    void deleteResource(QString, QMap<QString, QString>, const QObject* context, std::function<void(QByteArray)> const&) override;
};

#endif // MOCKNETWORKMANAGER_H

