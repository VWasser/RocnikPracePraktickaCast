#ifndef GRADESWINDOW_HPP
#define GRADESWINDOW_HPP

#include <QWidget>
#include <QTableWidget>
#include <QBoxLayout>
#include <QPushButton>

class GradesWindow
{

    Q_OBJECT
public:
    gradesWindow(QWidget *parent = nullptr);
    ~gradesWindow();
    void configure(QSharedPointer<ShowBasicData>) override;
private:
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QPushButton *addButton = new QPushButton;





};

#endif // GRADESWINDOW_HPP
