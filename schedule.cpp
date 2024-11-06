//Side Note
//hourStart will be the number of the class
//in sense that class 0 starts 7:55
//class 2 starts 9:40
//class 3 starts 10:50
//etc....


#include "schedule.hpp"
#include "httpclient.hpp"
#include "editmodescreen.hpp"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "BackendlessQt/BackendlessAPI.hpp"
#include <QTimer>

extern HttpClient* customHttpClient;

using namespace std;

enum Action {
    VIEW = 0,
    ADD = 1,
    DELETE = 2,
    EDIT = 3
};

Schedule::Schedule(QWidget*parent): QWidget(parent) {
    customHttpClient->connectToHost("178.32.127.114");
    auto dataToSendToServer = QString("GET /7D2C33DB-05E2-4FD9-B26B-46FDB17F56D6/19CB95DB-0235-4134-B1FB-C64750DE49E2/data/Schedules HTTP/1.0\r\nHost: eu-api.backendless.com\r\n\r\n");
    customHttpClient->writeData(dataToSendToServer.toUtf8());
    // customHttpClient->readyRead();

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
    });
    QObject::connect(editMode, &QPushButton::clicked, this, [&](){
        popUpWindow->show();
    });
    QObject::connect(calendar, &QTableWidget::cellChanged, this, [&](){
        switch(editFunctions->currentIndex()){
            case Action::VIEW:
                break;
            case Action::ADD:
                addItemFunc();
                break;
            case Action::DELETE:
                deleteItemFunc();
                break;
            case Action::EDIT:
                break;
            }
    });



    calendar->setVisible(true);

    editMode->setText(Schedule::tr("Edit Mode"));
    deleteItemButton->setText(Schedule::tr("deleteClass"));
    notDeletable.setText(Schedule::tr("NothingHere"));
    notDeletable.setInformativeText(Schedule::tr("CanNotDelete"));

    editFunctions->insertItem(Action::VIEW, "Viewing", *viewingMode);
    editFunctions->insertItem(Action::ADD, "Add", *addItem);
    editFunctions->insertItem(Action::DELETE, "Delete", *deleteItem);
    editFunctions->insertItem(Action::EDIT, "Edit", *editItem);


    dateLay->addSpacing(calendar->width()/2);
    dateLay->addWidget(date);
    dateLay->addSpacing((calendar->width())/4);
    dateLay->addWidget(editFunctions);
    dateLay->addWidget(deleteItemButton);
    table->addLayout(dateLay);
    dateLay->addSpacing(calendar->width()/2);
    table ->addWidget(calendar);
    table->addStretch();
    setLayout(table);
    calendar->setFixedSize(350,600);

    setupUI();

    for(int i = 0; i < 5; i++){
        calendar->setRowHeight(i, 100);
    }

    time(&timestamp);
    date->setText(ctime(&timestamp));

    updateData();
}

void Schedule::setupUI() {
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

void Schedule::deleteItemFunc(){
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
}

void Schedule::addItemFunc(){
    auto row =  new IntPostParam(calendar->currentRow());
    auto collumn = new IntPostParam(calendar->currentColumn());
    auto item = new StringPostParam(calendar->item(calendar->currentRow(), calendar->currentColumn())->text());

    if(item->asParam() == ""){
        close();
    }else{
        api->addItemToTable(
            "Schedules",
            {
             {"lessonDescription", item},
                {"dayOfWeek", row},
                {"hourStart",collumn}
            }
            );
    }

    delete item;
    delete row;
    delete collumn;
}
