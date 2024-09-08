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
            // onJSONError(jsonError);
            return;
        }

        auto jsonObject = jsonResponse.array();
        for (const auto& item : jsonObject) {
            auto desc = item.toObject()["lessonDescription"].toString();
            QTableWidgetItem* someItem = new QTableWidgetItem(desc, QTableWidgetItem::Type);
            calendar->setItem(0, 0, someItem);
        }
    });

    calendar->setVisible(true);

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

    calendar->setFixedSize(1090,410);

    calendar->setDisabled(true);

    api->loadTableItems("Schedules");
}

Schedule::~Schedule(){}
