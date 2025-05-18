#include "inputabsence.hpp"
#include "coordinator.hpp"
#include "BackendlessQt/BackendlessAPI.hpp"

extern Coordinator *coordinator;

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

    absenceTypeLine->addWidget(absenceTypeLabel);
    absenceTypeLine->addWidget(absenceType);

    mainLayout->addLayout(nameLine);
    mainLayout->addLayout(dateLine);
    mainLayout->addLayout(dayAndHourLine);
    mainLayout->addLayout(absenceTypeLine);
    mainLayout->addLayout(classLine);
    mainLayout->addWidget(addAbsence);

    absenceType->insertItem(absenceTypes::OK, "Ok", *ok);
    absenceType->insertItem(absenceTypes::UNSOLVED, "Unsolved", *unsolved);
    absenceType->insertItem(absenceTypes::MISSED, "Missed", *missed);
    absenceType->insertItem(absenceTypes::LATE, "Late", *late);
    absenceType->insertItem(absenceTypes::SCHOOL, "School", *school);

    QObject::connect(addAbsence, &QPushButton::clicked, this, [&](){
        //i know i dont have to do the .toInt() it is just a meassure to know what is a number
        //and what is a string etc.
        auto DayParam = QSharedPointer<IntPostParam>(new IntPostParam(dayBox->text().toInt()));
        auto HourParam = QSharedPointer<IntPostParam>(new IntPostParam(monthBox->text().toInt()));
        auto RowParam = QSharedPointer<IntPostParam>(new IntPostParam(rowBox->text().toInt() - 1));
        auto CollumnParam = QSharedPointer<IntPostParam>(new IntPostParam(collumnBox->text().toInt() - 1));
        auto UserIdParam = QSharedPointer<StringPostParam>(new StringPostParam(userIdBox->text()));
        auto currentIndexParam = QSharedPointer<IntPostParam>(new IntPostParam(absenceType->currentIndex()));

        api->addItemToTable(
            "Absences",
            {
             {"AbsenceDay", DayParam.get()},
             {"AbsenceMonth", HourParam.get()},
             {"AbsenceRow", RowParam.get()},
             {"AbsenceHour", CollumnParam.get()},
             {"UserID", UserIdParam.get()},
             {"Kind", currentIndexParam.get()}
            }
        );

    });


}
inputAbsence::~inputAbsence(){}

void inputAbsence::configure(QSharedPointer<ShowBasicData> data) {
    InputAbsenceData* passedData = (InputAbsenceData*)data.get();

    collumnBox->setText(QString::number(passedData->hour +1));
    rowBox->setText(QString::number(passedData->day +1));
}
