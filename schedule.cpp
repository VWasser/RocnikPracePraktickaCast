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
    QObject::connect(api, &BackendlessAPI::deleteItemFromTableSuccess, this, [&](){
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

        calendar->clearContents();

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

    //For debuging
    QObject::connect(calendar, &QTableWidget::cellClicked, this, [&](){
        qDebug() << calendar->currentRow() << " Row";
        qDebug() << calendar->currentColumn() << " Column";
        // qDebug() << calendar->currentItem()->text();
    });

    QObject::connect(deleteItemButton, &QPushButton::clicked, this, [&](){
        auto dayOfWeek = calendar->currentRow();
        auto hourStart = calendar->currentColumn();

        auto item = calendar->item(dayOfWeek, hourStart);
        if (!item) {
            qDebug() << "ITEM IS NOT SELECTED!!!";
            notDeletable.show();
            return;
        }
        auto objectId = item->data(Qt::UserRole);


        qDebug() << "objectId" << objectId;

        if(item->text() == ""){
            notDeletable.exec();
        }else{
            api->deleteItemFromTable("Schedules", objectId.toString());
        }
    });
    QObject::connect(editMode, &QPushButton::clicked, this, [&](){
        popUpWindow->show();
    });

    calendar->setVisible(true);

    editMode->setText(Schedule::tr("Edit Mode"));
    deleteItemButton->setText(Schedule::tr("deleteClass"));
    notDeletable.setText(Schedule::tr("NothingHere"));
    notDeletable.setInformativeText(Schedule::tr("CanNotDelete"));

    dateLay->addSpacing(400);
    dateLay->addWidget(date);
    dateLay->addSpacing(385);
    dateLay->addWidget(editMode);
    dateLay->addWidget(deleteItemButton);
    table->addLayout(dateLay);
    dateLay->addSpacing(350);
    table ->addWidget(calendar);
    table->addStretch();
    setLayout(table);

    dayItems.push_back(monday);
    dayItems.push_back(tuesday);
    dayItems.push_back(wednesday);
    dayItems.push_back(thursday);
    dayItems.push_back(friday);

    classItems.push_back(zero);
    classItems.push_back(one);
    classItems.push_back(two);
    classItems.push_back(three);
    classItems.push_back(four);
    classItems.push_back(five);
    classItems.push_back(six);
    classItems.push_back(seven);
    classItems.push_back(eight);
    classItems.push_back(nine);

    setupUI();

    for(int i = 0; i < 5; i++){
        calendar->setRowHeight(i, 75);
    }

    calendar->setFixedSize(1086,402);

    // calendar->setDisabled(true);

    time(&timestamp);
    date->setText(ctime(&timestamp));

    updateData();

    //qDebug()<< dayItems[0];

}

void Schedule::setupUI() {
    for(int i = 0; i < 10; i++){
        if(i < 5){
            calendar->setVerticalHeaderItem( i, dayItems[i]);
            calendar->setHorizontalHeaderItem( i, classItems[i]);
        }else{
            calendar->setHorizontalHeaderItem( i, classItems[i]);
        }
    }
}

Schedule::~Schedule(){}

void Schedule::updateData() {
    api->loadTableItems("Schedules");
}
