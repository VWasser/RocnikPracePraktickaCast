#include "inputabsence.hpp"
#include "coordinator.hpp"

extern Coordinator *coordinator;
extern BackendlessAPI* api;

class LongPostParam: public PostParam {
public:
    LongPostParam(long _value): value(_value) { }

    QString asParam() override {
        return QString::number(value);
    }

private:
    long value;
};

inputAbsence::inputAbsence(QWidget *parent): ScreenWidget(parent) {
    QObject::connect(api, &BackendlessAPI::itemAdded, this, [&](){
        // qDebug() << "Item was added " << replyValue;

    });

    QObject::connect(addAbsence, &QPushButton::clicked, this, [](){
        auto kind = new IntPostParam(14);
        auto userId = new StringPostParam("someUserId");
        auto absenceDate = new LongPostParam(1000000000000);

        api->addItemToTable(
            "Absences",
            {
                {"Kind", kind},
                {"UserID", userId},
                {"AbsenceDate", absenceDate}
            }
        );

        delete kind;
        delete userId;
        delete absenceDate;

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

void inputAbsence::configure(QSharedPointer<ShowBasicData> data) {
    InputAbsenceData* passedData = (InputAbsenceData*)data.get();

    hourBox->setText(QString::number(passedData->hour +1));
    dayBox->setText(QString::number(passedData->day +1));
}
