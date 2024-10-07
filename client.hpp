#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <QtCore>
#include <QtNetwork>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);

public slots:
    bool connectToHost(QString host);
    bool writeData(QByteArray data);
    void readyRead();

private:
    QTcpSocket *socket;
};

#endif
