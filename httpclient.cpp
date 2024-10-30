#include "httpclient.hpp"

HttpClient::HttpClient(QObject *parent) : QObject(parent) {
    socket = new QTcpSocket(this);
    connect(socket, &QIODevice::readyRead, this, [&](){
        auto receivedData = socket->readAll();
        qDebug() << "I WAS THERE";
        qDebug() << QString(receivedData);
    });
}

bool HttpClient::connectToHost(QString host) {
    socket->connectToHost(QHostAddress(host), 80);
    auto result = socket->waitForConnected();
    if (!result) {
        qDebug() << socket->errorString();
        exit(100);
    }
    return result;
}

bool HttpClient::writeData(QByteArray data)
{
    if(socket->state() == QAbstractSocket::ConnectedState)
    {
        connect(socket, SIGNAL(readyRead()), SLOT(readyRead()));
        //socket->write(IntToArray(data.size())); //write size of data
        socket->write(data); //write the data itself
        return socket->waitForBytesWritten();
    }
    else
        return false;
}

void HttpClient::readyRead()
{
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
    QByteArray *buffer = new QByteArray();
    qint32 *s = new qint32(1000); //sizes.value(socket);
    qint32 size = *s;
    while (socket->bytesAvailable() > 0)
    {
        QString data = socket->readAll();
        qDebug() << data;
        buffer->append(socket->readAll());
        /*while ((size == 0 && buffer->size() >= 4) || (size > 0 && buffer->size() >= size)) //While can process data, process it
        {
            if (size == 0 && buffer->size() >= 4) //if size of data has received completely, then store it on our global variable
            {
                size = ArrayToInt(buffer->mid(0, 4));
                *s = size;
                buffer->remove(0, 4);
            }
            if (size > 0 && buffer->size() >= size) // If data has received completely, then emit our SIGNAL with the data
            {
                QByteArray data = buffer->mid(0, size);
                buffer->remove(0, size);
                size = 0;
                *s = size;
                // emit dataReceived(data);
            }
        }*/
    }
}
