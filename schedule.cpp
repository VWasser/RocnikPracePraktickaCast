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
    auto itemAddedFuture = QtFuture::connect(api, &BackendlessAPI::itemAdded);
    itemAddedFuture.then([&](){
        updateData();
    });

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
        if (!jsonResponse.isArray()) {
            return;
        }

        auto jsonObject = jsonResponse.array();

        if (!jsonObject.empty() && jsonObject[0].toObject()["___class"] != "Schedules") {
            return;
        }

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

    QObject::connect(calendar, &QTableWidget::cellChanged, this, [&](){
        switch(editFunctions->currentIndex()){
            case Action::VIEW:
                break;
            case Action::ADD:
                addItemFunc();
                break;
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
    QObject::connect(api, &BackendlessAPI::deleteItemFromTableSuccess, this, [&](const auto &result) {
        updateData();
    }, Qt::SingleShotConnection);
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

    if (std::find_if(cachedSchedule.cbegin(), cachedSchedule.cend(), [=](ScheduleItem item){ // = means COPY all what we need
        return item.dayOfWeek == dayOfWeek && item.hourStart == hourStart;
    }) != cachedSchedule.constEnd()) {
        // TODO ALERT WINDOW
        qDebug() << "Lesson was already added there";
        return;
    }

    auto rowParam = QSharedPointer<IntPostParam>(new IntPostParam(dayOfWeek));
    auto collumnParam = QSharedPointer<IntPostParam>(new IntPostParam(hourStart));
    auto itemParam = QSharedPointer<StringPostParam>(new StringPostParam(item->text()));

    QObject::connect(
        api,
        &BackendlessAPI::itemEdited,
        this,
        [&](){
            updateData();
        },
        Qt::SingleShotConnection
    );

    api->editTableItem(
        "Schedules",
        QString("objectId") + QString("%20%3D%20") + objectId.toString(),
        {
            {"lessonDescription", itemParam.get()},
            {"dayOfWeek", rowParam.get()},
            {"hourStart", collumnParam.get()}
        }
    );
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

    auto row =  new IntPostParam(rowValue);
    auto collumn = new IntPostParam(columnValue);
    auto item = new StringPostParam(calendarItem->text());

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
    updateData();
}
