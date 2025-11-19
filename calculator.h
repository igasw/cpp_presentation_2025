#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

class Calculator : public QWidget
{
    Q_OBJECT

public:
    explicit Calculator(QWidget *parent = nullptr);

private slots:
    void digitClicked();    // digits 0-9 and "."
    void operatorClicked(); // +, -, *, /
    void equalClicked();    // =
    void clearClicked();    // C (Clear)
    void randClicked();     // RAND

private:
    QPushButton *createButton(const QString &text, const char *member);

    QLineEdit *historyDisplay; // shows the whole equation
    QLineEdit *mainDisplay;    // shows the last clicked value or solution

    // variables for the calc logic
    double pendingValue;
    QString pendingOperator;
    bool waitingForOperand;
    bool lastClickedWasEqual;
};

#endif // CALCULATOR_H