#ifndef MOCKNETWORKMANAGER_H
#define MOCKNETWORKMANAGER_H

#include "BackendlessQt/BasicAPI.hpp"

class MockNetworkManager: public AnyNetworkAccessManager {
public:
    void get(QString, const QObject*, std::function<void(QByteArray)> const&) override;
    void post(QString, PostParams, const QObject*, std::function<void(QByteArray)> const&) override;
    void put(QString, PostParams, const QObject* context, std::function<void(QByteArray)> const&) override;
    void deleteResource(QString, const QObject* context, std::function<void(QByteArray)> const&) override;
};

#endif // MOCKNETWORKMANAGER_H

