#include "addgrades.hpp"
#include "coordinator.hpp"

extern Coordinator *coordinator;

enum class Grade {
    APLUS,// = "1",
    A,// = "1-",
    BPLUS,// = "2",
    B,// = "2-",
    CPLUS,// = "3",
    C,// = "3-",
    DPLUS,// = "4",
    D,// = "4-",
    E// = "5"
};

addGrades::addGrades(QWidget *parent): ScreenWidget(parent) {

}
addGrades::~addGrades(){ }

void addGrades::configure(QSharedPointer<ShowBasicData> data) {

}
