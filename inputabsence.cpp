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
        coordinator->showAbsenceWindow();
    });

    setLayout(mainLayout);
    nameLine->addWidget(nameLabel);
    nameLine->addWidget(nameBox);
    nameLine->addWidget(userIdBox);


    dateLine->addWidget(dateLabel);
    dateLine->addWidget(dayBox);
    dateLine->addWidget(monthBox);

    classLine->addWidget(classLabel);
    classLine->addWidget(classBox);

    dayAndHourLine->addWidget(dayAndHourLabel);
    dayAndHourLine->addWidget(rowBox);
    dayAndHourLine->addWidget(collumnBox);

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

    QObject::connect(addAbsence, &QPushButton::clicked, this, [&](){
        //i know i dont have to do the .toInt() it is just a meassure to know what is a number
        //and what is a string etc.
        auto DayParam = new IntPostParam(dayBox->text().toInt());
        auto HourParam = new IntPostParam(monthBox->text().toInt());
        auto RowParam = new IntPostParam(rowBox->text().toInt() - 1);
        auto CollumnParam = new IntPostParam(collumnBox->text().toInt() - 1);
        auto UserIdParam = new StringPostParam(userIdBox->text());

        api->addItemToTable(
            "Absences",
            {
             {"AbsenceDay", DayParam},
             {"AbsenceMonth", HourParam},
             {"AbsenceRow", RowParam},
             {"AbsenceHour", CollumnParam},
             {"UserID", UserIdParam}
            }
        );

        //will eventualy add some functions just dont have the idea of exactly what
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

    collumnBox->setText(QString::number(passedData->hour +1));
    rowBox->setText(QString::number(passedData->day +1));
}
