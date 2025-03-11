#include "inputabsence.hpp"
#include "coordinator.hpp"

extern Coordinator *coordinator;

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

}
inputAbsence::~inputAbsence(){}

void inputAbsence::configure(QSharedPointer<ShowBasicData> data, QSharedPointer<ShowBasicData2> data2) {
    InputAbsenceData* passedData1 = (InputAbsenceData*)data.data();
    // InputAbsenceData* passedData2 = (InputAbsenceData*)data2.data();
    hourBox->setText(QString::number(passedData1->hour +1));
    dayBox->setText(QString::number(passedData1->day +1));
}
