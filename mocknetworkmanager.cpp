#include "mocknetworkmanager.hpp"

void MockNetworkManager::get(QString urlString, const QObject* context, std::function<void(QByteArray)> const& handleRequest) {
    auto fakeRespone = QString("[") +
        QString("{") +
            QString("\"dayOfWeek\": 1,") +
            QString("\"created\": 1729775924363,") +
            QString("\"hourStart\": 1,") +
            QString("\"lessonDescription\": \"Jiny text\",") +
            QString("\"___class\": \"Schedules\",") +
            QString("\"objectId\": \"2A855167-D125-479A-897C-4CDB874D63C8\"") +
        QString("}") +
    QString("]");

    auto fakeBytesArray = fakeRespone.toUtf8();
    handleRequest(fakeBytesArray);
}

void MockNetworkManager::post(QString urlString, PostParams customParams, const QObject* context, std::function<void(QByteArray)> const& handleRequest) {
    /*QUrl url(urlString);
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

    QObject::connect(&manager, &QNetworkAccessManager::finished, context, [handleRequest](auto reply) {
        handleRequest(reply->readAll());
    }, Qt::SingleShotConnection);
    manager.post(request, params.toUtf8());*/
}

void MockNetworkManager::put(QString urlString, PostParams customParams, const QObject* context, std::function<void(QByteArray)> const& handleRequest) {
    /*QUrl url(urlString);
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

    QObject::connect(&manager, &QNetworkAccessManager::finished, context, [handleRequest](auto reply) {
        handleRequest(reply->readAll());
    }, Qt::SingleShotConnection);
    manager.put(request, params.toUtf8());*/
}

void MockNetworkManager::deleteResource(QString urlString, const QObject* context, std::function<void(QByteArray)> const& handleRequest) {
    /*QUrl url(urlString);
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QObject::connect(&manager, &QNetworkAccessManager::finished, context, [handleRequest](auto reply) {
        handleRequest(reply->readAll());
    }, Qt::SingleShotConnection);
    manager.deleteResource(request);*/
}
