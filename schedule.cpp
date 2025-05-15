//Side Note
//hourStart will be the number of the class
//in sense that class 0 starts 7:55
//class 2 starts 9:40
//class 3 starts 10:50
//etc....


#include "schedule.hpp"
#include "coordinator.hpp"
#include "absencewindow.hpp"
#include "httpclient.hpp"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "BackendlessQt/BackendlessAPI.hpp"
#include <QTimer>

extern Coordinator* coordinator;
extern HttpClient* customHttpClient;
extern absenceWindow* abscWin;

using namespace std;

enum Action {
    VIEW = 0,
    ADD = 1,
    DELETE = 2,
    EDIT = 3
};

Schedule::Schedule(QWidget*parent): ScreenWidget(parent) {
    customHttpClient->connectToHost("178.32.127.114");
    auto dataToSendToServer = QString("GET /7D2C33DB-05E2-4FD9-B26B-46FDB17F56D6/19CB95DB-0235-4134-B1FB-C64750DE49E2/data/Schedules HTTP/1.0\r\nHost: eu-api.backendless.com\r\n\r\n");
    customHttpClient->writeData(dataToSendToServer.toUtf8());
    // customHttpClient->readyRead();

    auto itemAddedFuture = QtFuture::connect(api, &BackendlessAPI::itemAdded);
    itemAddedFuture.then([&](){
        updateData();
    });

    //QObject::connect(api, &BackendlessAPI::deleteItemFromTableSuccess, this, [&](){
        //updateData();
    //});

    QObject::connect(api, &BackendlessAPI::loadTableItemsSuccess, this, [&](auto replyValue){
        qDebug() << "Loaded " << replyValue;

        cachedSchedule.clear();

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
            ScheduleItem scheduleItem(lessonObject);
            cachedSchedule.push_back(scheduleItem);
            auto oldItem = calendar->item(scheduleItem.dayOfWeek, scheduleItem.hourStart);
            delete oldItem;

            QTableWidgetItem* someItem = new QTableWidgetItem(scheduleItem.desc, QTableWidgetItem::Type);
            someItem->setData(Qt::UserRole, scheduleItem.objectId);
            calendar->setItem(scheduleItem.dayOfWeek, scheduleItem.hourStart, someItem);
        }
    });

    //absence signal recieved
    QObject::connect(coordinator, &Coordinator::sendScheduleAbsence, this, [&](){
        this->onSomething();
    });

    //in absence add mode
    QObject::connect(calendar, &QTableWidget::cellClicked, this, [&](){
        qDebug()<< "cell clicked";
        if(isAbsenceMode == true){
            qDebug()<< "if statement triggered";
            dayOfWeek = calendar->currentRow();
            hourStart = calendar->currentColumn();
            qDebug() << "variables set";
            //crashes here
            coordinator->showInputAbsence(
                QSharedPointer<InputAbsenceData>(
                    new InputAbsenceData(hourStart, dayOfWeek)
                )
            );
            qDebug() << "show input absence called";
            emit sendImputAbsenceData();
            qDebug() <<"signal emited";
        }else{
            return;
        }
    });

    QObject::connect(deleteItemButton, &QPushButton::clicked, this, [&](){
        deleteItemFunc();
        updateData();
    });
    QObject::connect(editMode, &QPushButton::clicked, this, [&](){
         coordinator->showSettingsWindow();
    });
    /*QObject::connect(calendar, &QTableWidget::cellClicked, this, [&](){
        if(exeptionForAdd() == true){
            isTaken = true;
        }else{
            isTaken = false;
        }
    });*/

    QObject::connect(calendar, &QTableWidget::cellChanged, this, [&](){
        switch(editFunctions->currentIndex()){
            case Action::VIEW:
                break;
            case Action::ADD:
                /*if(isTaken == true){
                    break;
                }else{*/
                    addItemFunc();
                    break;
                //}
            case Action::DELETE:
                break;
            case Action::EDIT:
                editItemFunc();
                break;
            }
    });

    QObject::connect(editFunctions, &QComboBox::currentIndexChanged, this, [&](){
        if(editFunctions->currentIndex() == Action::DELETE){

            deleteItemButton->show();
            calendar->setDisabled(false);
        }else if(editFunctions->currentIndex() == (Action::VIEW )){

            deleteItemButton->hide();
            calendar->setDisabled(true);

        }else if(editFunctions->currentIndex() == (Action::ADD )){

            deleteItemButton->hide();
            calendar->setDisabled(false);

        }else if(editFunctions->currentIndex() == (Action::EDIT )){

            deleteItemButton->hide();
            calendar->setDisabled(false);
        }
    });

    for(int i = 0; i < 5; i++){
        for(int j = 0; j <10;j++){
            auto item = calendar->item(i, j);
            if(!item){
            calendar->setItem(i,j,new QTableWidgetItem(""));
            }
        }
        qDebug() << "ROW " << i <<" SET";
    }
    // void scheduleAbsenceOpened();

    deleteItemButton->hide();

    calendar->setVisible(true);

    editMode->setText(Schedule::tr("Edit Mode"));
    deleteItemButton->setText(Schedule::tr("deleteClass"));
    notDeletable.setText(Schedule::tr("NothingHere"));
    notDeletable.setInformativeText(Schedule::tr("CanNotDelete"));

    editFunctions->insertItem(Action::VIEW, "Viewing", *viewingMode);
    auto currentUser = static_cast<BachelorSignInUser*>(api->userAPI.user());
    if (currentUser->isTeacher) {
        editFunctions->insertItem(Action::ADD, "Add", *addItem);
        editFunctions->insertItem(Action::DELETE, "Delete", *deleteItem);
        editFunctions->insertItem(Action::EDIT, "Edit", *editItem);
    }


    dateLay->addSpacing(calendar->width()/2);
    dateLay->addWidget(date);
    dateLay->addSpacing((calendar->width())/4);
    dateLay->addWidget(editFunctions);
    dateLay->addWidget(deleteItemButton);

    coordinator->implementMenuBar(table);

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

void Schedule::onSomething() {
    isAbsenceMode = true;
    date->hide();
    editFunctions->hide();
    calendar->setDisabled(false);
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

    api->deleteItemFromTable("Schedules", objectId.toString());

    auto itemDeleteFuture = QtFuture::connect(api, &BackendlessAPI::deleteItemFromTableSuccess)
    .then([=, this](const auto &result) {
    updateData();
    });

}


void Schedule::editItemFunc(){
    auto dayOfWeek = calendar->currentRow();
    auto hourStart = calendar->currentColumn();
    auto item = calendar->item(dayOfWeek, hourStart);
    if (!item) {
        qDebug() << "NOTHING TO EDIT!!!";
        return;
    }
    auto objectId = item->data(Qt::UserRole);

    qDebug() << "objectId" << objectId;

    auto itemDeleteFuture = QtFuture::connect(api, &BackendlessAPI::deleteItemFromTableSuccess);
    itemDeleteFuture
        .then([=, this](auto result){
            addItemFunc(hourStart, dayOfWeek);
            return QtFuture::connect(api, &BackendlessAPI::itemAdded);
        })
        .unwrap()
        .then([&]() {
            updateData();
        });

    api->deleteItemFromTable("Schedules", objectId.toString());
}

void Schedule::addItemFunc(int predefinedColumnValue, int predefinedRowValue){
    auto rowValue = predefinedRowValue >= 0 ? predefinedRowValue : calendar->currentRow();
    auto columnValue = predefinedColumnValue >= 0 ? predefinedColumnValue : calendar->currentColumn();
    auto calendarItem = calendar->item(rowValue, columnValue);

    if (rowValue < 0 || columnValue < 0 || !calendarItem) {
        return;
    }

    if (std::find_if(cachedSchedule.cbegin(), cachedSchedule.cend(), [=](ScheduleItem item){ // = means COPY all what we need
        return item.dayOfWeek == rowValue && item.hourStart == columnValue;
    }) != cachedSchedule.constEnd()) {
        // TODO ALERT WINDOW
        qDebug() << "Lesson was already added there";
        return;
    }

    /*QList arr = {1, 2, 3, 4};
    myFindIf<int, std::function<bool(int)>>(arr, [](int a) {
        return a > 0;
    });*/

    /*auto iterator = std::find_if(
        cachedSchedule.begin(),
        cachedSchedule.end(),
        [rowValue, columnValue](ScheduleItem scheduleItem) {
            return scheduleItem.dayOfWeek == rowValue && scheduleItem.hourStart == columnValue;
        }
    );
    if (iterator != cachedSchedule.end()) {
        return;
    }*/

    auto row =  new IntPostParam(rowValue);
    auto collumn = new IntPostParam(columnValue);
    auto item = new StringPostParam(calendarItem->text());

    if(item->asParam() == ""){
        close();
    }else{
    //
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

/*void Schedule::scheduleAbsenceOpened(){
    calendar->hide();
}*/


bool Schedule::exeptionForAdd(){
        auto dayOfWeek = calendar->currentRow();
        auto hourStart = calendar->currentColumn();
        auto item = calendar->item(dayOfWeek, hourStart);
        if (item) {
            qDebug() << "ITEM ALREADY EXISTS!!!";
            return true;
        }else{
            return false;
        }

}

void Schedule::configure(QSharedPointer<ShowBasicData>) {

}
