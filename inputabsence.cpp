#include "inputabsence.hpp"
#include "coordinator.hpp"

extern Coordinator *coordinator;

inputAbsence::inputAbsence(QWidget *parent): QWidget(parent) {

    QObject::connect(addAbsence, &QPushButton::clicked,this, [](){
        coordinator->showSchedule();
    });
    QObject::connect(coordinator, &Coordinator::sendImputAbsence,this, [=](){
        dayBox->setText(QString::number(coordinator->dayOfWeek));
        hourBox->setText(QString::number(coordinator->hourStart));
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
