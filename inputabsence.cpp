#include "inputabsence.hpp"
#include "coordinator.hpp"
#include "BackendlessQt/BackendlessAPI.hpp"

extern Coordinator *coordinator;

enum absenceTypes {
    OK = 0,
    UNSOLVED = 1,
    MISSED = 2,
    LATE = 3,
    SCHOOL = 4
};

inputAbsence::inputAbsence(QWidget *parent): ScreenWidget(parent) {

    QObject::connect(addAbsence, &QPushButton::clicked,this, [](){
        coordinator->showSchedule();
    });

    setLayout(mainLayout);
    nameLine->addWidget(nameLabel);
    nameLine->addWidget(nameBox);

    dateLine->addWidget(dateLabel);
    dateLine->addWidget(dateBox);

    classLine->addWidget(classLabel);
    classLine->addWidget(classBox);

    dayAndHourLine->addWidget(dayAndHourLabel);
    dayAndHourLine->addWidget(dayBox);
    dayAndHourLine->addWidget(hourBox);

    mainLayout->addLayout(nameLine);
    mainLayout->addLayout(dateLine);
    mainLayout->addLayout(classLine);
    mainLayout->addLayout(dayAndHourLine);
    mainLayout->addWidget(addAbsence);

    absenceType->insertItem(absenceTypes::OK, "Ok", *ok);
    absenceType->insertItem(absenceTypes::UNSOLVED, "Unsolved", *unsolved);
    absenceType->insertItem(absenceTypes::MISSED, "Missed", *missed);
    absenceType->insertItem(absenceTypes::LATE, "Late", *late);
    absenceType->insertItem(absenceTypes::SCHOOL, "School", *school);

    auto absenceDayParam = new IntPostParam();

    //will eventualy add some functions just dont have the idea of exactly what
    QObject::connect(addAbsence, &QPushButton::clicked, this, [&](){
        api->addItemToTable(
            "Absence",
            {
             {"AbsenceDay",},
             {"AbsenceMonth",},
             {"AbsenceRow",},
             {"AbsenceHour",},
             {"UserID",}
            }
            );
        switch(absenceType->currentIndex()){
        case absenceTypes::OK:
            break;
        case absenceTypes::UNSOLVED:
            break;
        case absenceTypes::MISSED:
            break;
        case absenceTypes::LATE:
            break;
        case absenceTypes::SCHOOL:
            break;
        }
    });


}
inputAbsence::~inputAbsence(){}

void inputAbsence::configure(QSharedPointer<ShowBasicData> data) {
    InputAbsenceData* passedData = (InputAbsenceData*)data.get();

    hourBox->setText(QString::number(passedData->hour +1));
    dayBox->setText(QString::number(passedData->day +1));
}
