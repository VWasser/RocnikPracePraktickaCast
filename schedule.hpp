#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <QWidget>
#include <QFormLayout>
#include <QPushButton>
#include <QTableWidget>
#include <QHeaderView>
#include <QCalendarWidget>
#include "BackendlessQt/BackendlessAPI.hpp"
#include "inputabsence.hpp"
#include "qlabel.h"
#include "qmessagebox.h"
#include <ctime>
#include <QComboBox>
#include "screenwidget.hpp"

extern BackendlessAPI* api;

struct ScheduleItem {
    QString objectId;
    QString desc;
    int dayOfWeek;
    int hourStart;

    ScheduleItem(QJsonObject lessonObject) {
        objectId = lessonObject["objectId"].toString();
        desc = lessonObject["lessonDescription"].toString();
        dayOfWeek = lessonObject["dayOfWeek"].toInt();
        hourStart = lessonObject["hourStart"].toInt();
    }
};

class Schedule : public ScreenWidget
{
    Q_OBJECT

public:
    friend class Coordinator;
    Schedule(QWidget *parent = nullptr);
    ~Schedule();
    void updateData();
    void configure(ShowBasicData*,ShowBasicData2*) override;

private:
    void setupUI();

private:
    int hourStart;
    int dayOfWeek;
    bool isUpdating = true;
    bool isAbsenceMode = false;

    int hourStart;
    int dayOfWeek;

    //bool isTaken = true;
    QList<ScheduleItem> cachedSchedule;
    QTableWidget* calendar = new QTableWidget(5,10);

    QPushButton *deleteItemButton = new QPushButton;
    QPushButton *editMode = new QPushButton;
    QVBoxLayout *table = new QVBoxLayout;
    QHBoxLayout *dateLay = new QHBoxLayout;
    QVector<QPushButton*> dayButtons;
    QVector<QTableWidgetItem*>dayItems;
    QVector<QTableWidgetItem*>classItems;
    QComboBox *editFunctions = new QComboBox;
    QVariant *viewingMode = new QVariant;
    QVariant *editItem = new QVariant;
    QVariant *deleteItem = new QVariant;
    QVariant *addItem = new QVariant;

    void deleteItemFunc();
    void editItemFunc();
    void addItemFunc(int predefinedColumnValue = -1, int predefinedRowValue = -1);
    bool exeptionForAdd();
    void onSomething();
signals:
    void sendImputAbsenceData();

private:
    QMessageBox notDeletable;

    QLabel* date = new QLabel;
    time_t timestamp;

    QTableWidgetItem *placeholderItem;

    QTableWidgetItem *monday = new QTableWidgetItem(tr("Monday"));
    QTableWidgetItem *tuesday = new QTableWidgetItem(tr("Tuesday"));
    QTableWidgetItem *wednesday = new QTableWidgetItem(tr("Wednesday"));
    QTableWidgetItem *thursday = new QTableWidgetItem(tr("Thursday"));
    QTableWidgetItem *friday = new QTableWidgetItem(tr("Friday"));



    QTableWidgetItem *zero = new QTableWidgetItem(tr("7:55 - 8:40"));
    QTableWidgetItem *one = new QTableWidgetItem(tr("8:45 - 9:30"));
    QTableWidgetItem *two = new QTableWidgetItem(tr("9:40 - 10:25"));
    QTableWidgetItem *three = new QTableWidgetItem(tr("10:50 - 11:35"));
    QTableWidgetItem *four = new QTableWidgetItem(tr("11:45 - 12:30"));
    QTableWidgetItem *five = new QTableWidgetItem(tr("12:40 - 13:25"));
    QTableWidgetItem *six = new QTableWidgetItem(tr("13:30 - 14:15"));
    QTableWidgetItem *seven = new QTableWidgetItem(tr("14:20 - 15:05"));
    QTableWidgetItem *eight = new QTableWidgetItem(tr("15:10 - 15:55"));
    QTableWidgetItem *nine = new QTableWidgetItem(tr("16:00 - 16:45"));


};

template<class T, class UnaryPred>
bool myFindIf(typename QList<T>::Iterator begin, typename QList<T>::Iterator end, UnaryPred isWhatWeAreSearchingFor) {
    return false;
}

#endif // SCHEDULE_H

