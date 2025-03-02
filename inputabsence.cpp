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

void inputAbsence::configure(ShowBasicData* data) {
    InputAbsenceData* castedData = qobject_cast<InputAbsenceData*>(data);
    if (!castedData) {
        return; // Someone is trying to configure inputAbsence with a non-InputAbsenceData instance
    }
    dayBox->setText(QString::number(castedData->day));
    hourBox->setText(QString::number(castedData->hour));
}
