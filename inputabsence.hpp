#ifndef INPUTABSENCE_HPP
#define INPUTABSENCE_HPP

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QBoxLayout>

class inputAbsence : public QWidget
{
    Q_OBJECT
public:
    inputAbsence(QWidget *parent = nullptr);
    ~inputAbsence();
private:
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *nameLine = new QHBoxLayout;
    QHBoxLayout *dateLine = new QHBoxLayout;
    QHBoxLayout *classLine = new QHBoxLayout;
    QHBoxLayout *dayAndHourLine = new QHBoxLayout;

private:
    QLabel *nameLabel = new QLabel(inputAbsence::tr("nameOfStudent"));
    QLabel *dateLabel = new QLabel(inputAbsence::tr("dateOfAbsence"));
    QLabel *classLabel = new QLabel(inputAbsence::tr("className"));
    QLabel *dayAndHourLabel = new QLabel(inputAbsence::tr("DayAndHour"));

private:
    QLineEdit *nameBox = new QLineEdit;
    QLineEdit *dateBox = new QLineEdit;
    QLineEdit *classBox = new QLineEdit;
    QLineEdit *dayBox = new QLineEdit;
    QLineEdit *hourBox = new QLineEdit;

    QPushButton *addAbsence = new QPushButton(inputAbsence::tr("addAbsence"));


};

#endif // INPUTABSENCE_HPP
