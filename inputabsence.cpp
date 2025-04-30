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

    absenceType->insertItem(0, "Ok", *ok);
    absenceType->insertItem(1, "Unsolved", *unsolved);
    absenceType->insertItem(2, "Missed", *missed);
    absenceType->insertItem(3, "Late", *late);
    absenceType->insertItem(5, "School", *school);

    QObject::connect(addAbsence, &QPushButton::clicked, this, [&](){
        //i know i dont have to do the .toInt() it is just a meassure to know what is a number
        //and what is a string etc.
        auto DayParam = new IntPostParam(dayBox->text().toInt());
        auto HourParam = new IntPostParam(monthBox->text().toInt());
        auto RowParam = new IntPostParam(rowBox->text().toInt() - 1);
        auto CollumnParam = new IntPostParam(collumnBox->text().toInt() - 1);
        auto UserIdParam = new StringPostParam(userIdBox->text());
        auto currentIndexParam = new IntPostParam(absenceType->currentIndex());

        api->addItemToTable(
            "Absences",
            {
             {"AbsenceDay", DayParam},
             {"AbsenceMonth", HourParam},
             {"AbsenceRow", RowParam},
             {"AbsenceHour", CollumnParam},
             {"UserID", UserIdParam},
             {"Kind", currentIndexParam}
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
