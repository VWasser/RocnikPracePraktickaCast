//Side Note
//hourStart will be the number of the class
//in sense that class 0 starts 7:55
//class 2 starts 9:40
//class 3 starts 10:50
//etc....


#include "schedule.hpp"
#include "editmodescreen.hpp"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "BackendlessQt/BackendlessAPI.hpp"
#include <QTimer>

using namespace std;

Schedule::Schedule(QWidget*parent): QWidget(parent)  {
    QObject::connect(api, &BackendlessAPI::itemAdded, this, [&](){
        updateData();
    });
    QObject::connect(api, &BackendlessAPI::itemDeleted, this, [&](){
        updateData();
    });

    QObject::connect(api, &BackendlessAPI::loadTableItemsSuccess, this, [&](auto replyValue){
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

            auto objectId = lessonObject["objectId"].toString();
            auto desc = lessonObject["lessonDescription"].toString();
            auto dayOfWeek = lessonObject["dayOfWeek"].toInt();
            auto hourStart = lessonObject["hourStart"].toInt();

            auto oldItem = calendar->item(dayOfWeek, hourStart);
            delete oldItem;

            QTableWidgetItem* someItem = new QTableWidgetItem(desc, QTableWidgetItem::Type);
            someItem->setData(Qt::UserRole, objectId);
            calendar->setItem(dayOfWeek, hourStart, someItem);
        }
    });
    QObject::connect(deleteItemButton, &QPushButton::clicked, this, [&](){
        auto dayOfWeek = calendar->currentRow();
        auto hourStart = calendar->currentColumn();

        auto item = calendar->item(dayOfWeek, hourStart);
        auto objectId = item->data(Qt::UserRole);

        qDebug() << "objectId" << objectId;
        if(objectId == "")
        {
            notDeletable.exec();
        }else{
            api->deleteItemFromTable("Schedules", objectId.toString());
        }
    });

    QObject::connect(editMode, &QPushButton::clicked, this, [&](){
        auto dayOfWeek = calendar->currentRow();
        auto hourStart = calendar->currentColumn();

        auto item = calendar->item(dayOfWeek, hourStart);
        auto objectId = item->data(Qt::UserRole);

        qDebug() << objectId;

        api->deleteItemFromTable("Schedules", objectId.toString());

        //popUpWindow->show();
    });



    calendar->setVisible(true);

    editMode->setText(Schedule::tr("Edit Mode"));
    deleteItemButton->setText(Schedule::tr("deleteClass"));

    dateLay->addSpacing(400);
    dateLay->addWidget(date);
    dateLay->addSpacing(400);
    dateLay->addWidget(editMode);
    dateLay->addWidget(deleteItemButton);
    table->addLayout(dateLay);
    dateLay->addSpacing(350);
    table ->addWidget(calendar);
    table->addStretch();
    setLayout(table);

    calendar->setVerticalHeaderItem(0, monday);
    calendar->setVerticalHeaderItem(1, tuesday);
    calendar->setVerticalHeaderItem(2, wednesday);
    calendar->setVerticalHeaderItem(3, thursday);
    calendar->setVerticalHeaderItem(4, friday);

    calendar->setHorizontalHeaderItem(0, zero);
    calendar->setHorizontalHeaderItem(1, one);
    calendar->setHorizontalHeaderItem(2, two);
    calendar->setHorizontalHeaderItem(3, three);
    calendar->setHorizontalHeaderItem(4, four);
    calendar->setHorizontalHeaderItem(5, five);
    calendar->setHorizontalHeaderItem(6, six);
    calendar->setHorizontalHeaderItem(7, seven);
    calendar->setHorizontalHeaderItem(8, eight);
    calendar->setHorizontalHeaderItem(9, nine);



    calendar->setRowHeight(0, 75);
    calendar->setRowHeight(1, 75);
    calendar->setRowHeight(2, 75);
    calendar->setRowHeight(3, 75);
    calendar->setRowHeight(4, 75);

    calendar->setFixedSize(1086,402);

    // calendar->setDisabled(true);

    time(&timestamp);
    date->setText(ctime(&timestamp));

    updateData();
}

Schedule::~Schedule(){}

void Schedule::updateData() {
    api->loadTableItems("Schedules");
}
