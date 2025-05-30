#include "absencewindow.hpp"
#include "BackendlessQt/BackendlessAPI.hpp"
#include "coordinator.hpp"

extern BackendlessAPI* api;
extern Coordinator* coordinator;

absenceWindow::absenceWindow(QWidget *parent): ScreenWidget(parent) {
    QObject::connect(addAbsence, &QPushButton::clicked, this, [&](){
        coordinator->showSchedule();
        emit scheduleAbsenceOpened();
    });
    absenceLayout->setFixedSize(315, 600);

    absenceLayout->setColumnCount(absenceTypes::COUNT + 1);
    for(int i =0;i < absenceTypes::COUNT + 1;i++){
        absenceLayout->setColumnWidth(i,50);
    }
    addAbsence->setText(absenceWindow::tr("addAbsence"));

    absenceLayout->setHorizontalHeaderItem(0, date);
    absenceLayout->setHorizontalHeaderItem(absenceTypes::OK + 1,ok);
    absenceLayout->setHorizontalHeaderItem(absenceTypes::UNSOLVED + 1,unsolved);
    absenceLayout->setHorizontalHeaderItem(absenceTypes::MISSED + 1,missed);
    absenceLayout->setHorizontalHeaderItem(absenceTypes::LATE + 1,late);
    absenceLayout->setHorizontalHeaderItem(absenceTypes::SCHOOL + 1,school);

    coordinator->implementMenuBar(mainLayout);


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

        if (!jsonResponse.isArray()) {
            return;
        }

        auto jsonObject = jsonResponse.array();

        if (!jsonObject.empty() && jsonObject[0].toObject()["___class"] != "Absences") {
            return;
        }

        cachedItems.clear();
        absenceLayout->clearContents();
        absenceLayout->setRowCount(jsonObject.count());

        for (const auto& item : jsonObject) {
            auto absenceObject = item.toObject();

            AbsenceItem absenceItem(absenceObject);
            cachedItems.push_back(absenceItem);

            QTableWidgetItem* dateItem = new QTableWidgetItem(
                QString::number(absenceItem.absenceMonth) + "/" +
                QString::number(absenceItem.absenceDay) + "/" +
                QString::number(absenceItem.absenceHour),
                QTableWidgetItem::Type
            );
            absenceLayout->setItem(cachedItems.size() - 1, 0, dateItem);

            QTableWidgetItem* crossItem = new QTableWidgetItem(
                "X",
                QTableWidgetItem::Type
            );
            absenceLayout->setItem(cachedItems.size() - 1, absenceItem.kind + 1, crossItem);
        }
    });

    updateData();
}

void absenceWindow::updateData() {
    api->loadTableItems("Absences");
}

absenceWindow::~absenceWindow(){}

void absenceWindow::configure(QSharedPointer<ShowBasicData>) {
    updateData();
}
