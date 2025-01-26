#include "absencewindow.hpp"
#include "BackendlessQt/BackendlessAPI.hpp"

extern BackendlessAPI* api;

absenceWindow::absenceWindow(QWidget *parent): QWidget(parent) {
    QObject::connect(addAbsence, &QPushButton::clicked, this, [&](){
        addAbscPopUpWin->show();
        hide();
    });
    mainLayout->addLayout(popisky);
    mainLayout->addLayout(absenceDaily);
    mainLayout->addWidget(addAbsence);

    popisky->addWidget(date);
    popisky->addWidget(ok);
    popisky->addWidget(unsolved);
    popisky->addWidget(missed);
    popisky->addWidget(late);
    popisky->addWidget(school);

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
