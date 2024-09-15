#include "schedule.hpp"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

Schedule::Schedule(QWidget*parent): QWidget(parent)  {
    QObject::connect(api, &BackendlessAPI::tableItemsLoaded, this, [&](auto replyValue){
        qDebug() << "Loaded " << replyValue;

        QJsonParseError jsonError;
        auto jsonResponse = QJsonDocument::fromJson(replyValue.toUtf8(), &jsonError);

        switch (jsonError.error) {
        case QJsonParseError::NoError:
            break;
        default:
            return;
        }

        auto jsonObject = jsonResponse.array();
        for (const auto& item : jsonObject) {
            auto lessonObject = item.toObject();
            auto desc = lessonObject["lessonDescription"].toString();
            auto dayOfWeek = lessonObject["dayOfWeek"].toInt();
            auto hourStart = lessonObject["hourStart"].toInt();
            QTableWidgetItem* someItem = new QTableWidgetItem(desc, QTableWidgetItem::Type);
            calendar->setItem(0, 0, someItem);
        }
    });

    calendar->setVisible(true);

    dateLay->addWidget(date);
    dateLay->addSpacing(350);
    table->addLayout(dateLay);
    table ->addWidget(calendar);
    setLayout(table);

    calendar->setVerticalHeaderItem(0, monday);
    calendar->setVerticalHeaderItem(1, tuesday);
    calendar->setVerticalHeaderItem(2, wednesday);
    calendar->setVerticalHeaderItem(3, thursday);
    calendar->setVerticalHeaderItem(4, friday);

    calendar->setRowHeight(0, 75);
    calendar->setRowHeight(1, 75);
    calendar->setRowHeight(2, 75);
    calendar->setRowHeight(3, 75);
    calendar->setRowHeight(4, 75);

    calendar->setFixedSize(1082,402);

    calendar->setDisabled(true);

    time(&timestamp);
    date->setText(ctime(&timestamp));

    api->loadTableItems("Schedules");
}

Schedule::~Schedule(){}
