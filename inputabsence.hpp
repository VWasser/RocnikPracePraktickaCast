#ifndef INPUTABSENCE_HPP
#define INPUTABSENCE_HPP

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QBoxLayout>
#include "screenwidget.hpp"
#include <QComboBox>

class inputAbsence : public ScreenWidget
{
    Q_OBJECT
public:
    inputAbsence(QWidget *parent = nullptr);
    ~inputAbsence();
    void configure(QSharedPointer<ShowBasicData> data) override;

private:
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *nameLine = new QHBoxLayout;
    QHBoxLayout *dateLine = new QHBoxLayout;
    QHBoxLayout *classLine = new QHBoxLayout;
    QHBoxLayout *dayAndHourLine = new QHBoxLayout;
    QHBoxLayout *absenceTypeLine = new QHBoxLayout;

private:
    QLabel *nameLabel = new QLabel(inputAbsence::tr("nameOfStudent"));
    QLabel *dateLabel = new QLabel(inputAbsence::tr("dateOfAbsence"));
    QLabel *classLabel = new QLabel(inputAbsence::tr("className"));
    QLabel *dayAndHourLabel = new QLabel(inputAbsence::tr("DayAndHour"));
    QLabel *absenceTypeLabel = new QLabel(inputAbsence::tr("absenceType"));

private:
    QComboBox *absenceType = new QComboBox;
    QVariant *ok = new QVariant;
    QVariant *unsolved = new QVariant;
    QVariant *missed = new QVariant;
    QVariant *late = new QVariant;
    QVariant *school = new QVariant;

private:
    QLineEdit *nameBox = new QLineEdit;
    QLineEdit *rowBox = new QLineEdit;
    QLineEdit *collumnBox = new QLineEdit;
    QLineEdit *classBox = new QLineEdit;
    QLineEdit *dayBox = new QLineEdit;
    QLineEdit *monthBox = new QLineEdit;
    QLineEdit *userIdBox = new QLineEdit;

    QPushButton *addAbsence = new QPushButton(inputAbsence::tr("addAbsence"));


};

#endif // INPUTABSENCE_HPP
