#ifndef HTTPCLIENT_HPP
#define HTTPCLIENT_HPP

#include <QtCore>
#include <QtNetwork>

class HttpClient : public QObject {
    Q_OBJECT

public:
    explicit HttpClient(QObject *parent = 0);

public slots:
    bool connectToHost(QString host);
    bool writeData(QByteArray data);
    void readyRead();

private:
    QTcpSocket *socket;
};

#endif
