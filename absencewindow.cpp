#include "absencewindow.hpp"
#include "BackendlessQt/BackendlessAPI.hpp"
#include "coordinator.hpp"

extern BackendlessAPI* api;
extern Coordinator* coordinator;

absenceWindow::absenceWindow(QWidget *parent): QWidget(parent) {
    QObject::connect(addAbsence, &QPushButton::clicked, this, [&](){
        coordinator->showSchedule();
        emit scheduleAbsenceOpened();
        hide();

    });
    absenceLayout->setFixedSize(315, 600);

    absenceLayout->setRowCount(ammountOfDays);
    absenceLayout->setColumnCount(6);
    for(int i =0;i < 6;i++){
        absenceLayout->setColumnWidth(i,50);
    }
    addAbsence->setText(absenceWindow::tr("addAbsence"));

    absenceLayout->setHorizontalHeaderItem(0, date);
    absenceLayout->setHorizontalHeaderItem(1,ok);
    absenceLayout->setHorizontalHeaderItem(2,unsolved);
    absenceLayout->setHorizontalHeaderItem(3,missed);
    absenceLayout->setHorizontalHeaderItem(4,late);
    absenceLayout->setHorizontalHeaderItem(5,school);


    mainLayout->addWidget(addAbsence);
    mainLayout->addWidget(absenceLayout);
    setLayout(mainLayout);

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
            auto absenceObject = item.toObject();
            AbsenceItem absenceItem(absenceObject);
            cachedItems.push_back(absenceItem);
        }
    });


    api->loadTableItems("Absences");
}


absenceWindow::~absenceWindow(){}
