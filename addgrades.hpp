#ifndef ADDGRADES_HPP
#define ADDGRADES_HPP

#include <QWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QBoxLayout>

class AddGrades
{
public:
    addGrades(QWidget *parent = nullptr);
    ~addGrades();
    void configure(QSharedPointer<ShowBasicData>) override;
private:
    QVBoxLayout *mainLayout = new QVBoxLayout;

    //will probably make a basic table in database to manage this
    //through a dynamicaly expanding QComboBox and will use the same one in the absence probably
    QLineEdit *lessonType = new QLineEdit;

    QHBoxLayout *dateLayout = new QHBoxLayout;
    QLineEdit *inputDay = new QLineEdit;
    QLineEdit *inputMonth = new QLineEdit;

    //bude to fungovat tak, že se vytvoří na základě údajů
    //protože formát mého generovaného studentId či co bude
    //ŠKOLATŘÍDA-INICIÁLY(POKUD UČITAL TAK UC) př.: TG8A-VWUC
    //což škola se vyplní automaticky, třída a iniciály se vyplní
    //a učitel se nemusí řešit takže to bude TG8A-VW a ten si potom
    //k ní připíše a bude se ukazovat člověku s identickým ID
    QLineEdit *nameOfStudent = new QLineEdit;
    QComboBox *classOfStudent = new QComboBox;
    QComboBox *grade = new QComboBox;
    QPushButton *addGrade = new QPushButton;

};

#endif // ADDGRADES_HPP
