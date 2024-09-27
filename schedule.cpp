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

extern editModeScreen* popUpWindow;

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
            calendar->setItem(dayOfWeek, hourStart, someItem);
        }
    });
    QObject::connect(editMode, &QPushButton::clicked, this, [&](){
        popUpWindow->show();
    });


    calendar->setVisible(true);

    dateLay->addSpacing(400);
    dateLay->addWidget(date);
    dateLay->addSpacing(400);
    dateLay->addWidget(editMode);
    table->addLayout(dateLay);
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

    calendar->setDisabled(true);

    time(&timestamp);
    date->setText(ctime(&timestamp));

    api->loadTableItems("Schedules");
}

Schedule::~Schedule(){}
