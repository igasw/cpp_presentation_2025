#include "calculator.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QRandomGenerator>

Calculator::Calculator(QWidget *parent)
    : QWidget(parent), pendingValue(0.0), waitingForOperand(true), lastClickedWasEqual(false)
{
    setWindowTitle("Kalkulator Qt6");
    setFixedSize(320, 450); // Setting the size of the window

    // Creating the displays

    // Equation display
    historyDisplay = new QLineEdit;
    historyDisplay->setReadOnly(true);
    historyDisplay->setAlignment(Qt::AlignRight);
    historyDisplay->setMinimumHeight(25);
    historyDisplay->setStyleSheet("font-size: 14px; color: #555; background: #eee; border: none;");

    // Main display - last clicked value or solution
    mainDisplay = new QLineEdit("0");
    mainDisplay->setReadOnly(true);
    mainDisplay->setAlignment(Qt::AlignRight);
    mainDisplay->setStyleSheet("font-size: 32px; padding: 10px; background: #f0f0f0; border: 1px solid #ccc;");

    // Grid for buttons
    QGridLayout *gridLayout = new QGridLayout;

    // Creating the buttons in the grid

    // Row 0: C, +/-, RAND, /
    gridLayout->addWidget(createButton("C", SLOT(clearClicked())), 0, 0);   // args: widget, row, column
    gridLayout->addWidget(createButton("+/-", SLOT(digitClicked())), 0, 1); // "=/-" is being treated as a digit, because it is an unary operator and immediately returns new value (needs only one arg for input)
    gridLayout->addWidget(createButton("RAND", SLOT(randClicked())), 0, 2);
    gridLayout->addWidget(createButton("/", SLOT(operatorClicked())), 0, 3); // operators (other than "=/-") need two values for input (it makes them wait for second one)

    // Row 1: 7, 8, 9, *
    gridLayout->addWidget(createButton("7", SLOT(digitClicked())), 1, 0);
    gridLayout->addWidget(createButton("8", SLOT(digitClicked())), 1, 1);
    gridLayout->addWidget(createButton("9", SLOT(digitClicked())), 1, 2);
    gridLayout->addWidget(createButton("*", SLOT(operatorClicked())), 1, 3);

    // Row 2: 4, 5, 6, -
    gridLayout->addWidget(createButton("4", SLOT(digitClicked())), 2, 0);
    gridLayout->addWidget(createButton("5", SLOT(digitClicked())), 2, 1);
    gridLayout->addWidget(createButton("6", SLOT(digitClicked())), 2, 2);
    gridLayout->addWidget(createButton("-", SLOT(operatorClicked())), 2, 3);

    // Row 3: 1, 2, 3, +
    gridLayout->addWidget(createButton("1", SLOT(digitClicked())), 3, 0);
    gridLayout->addWidget(createButton("2", SLOT(digitClicked())), 3, 1);
    gridLayout->addWidget(createButton("3", SLOT(digitClicked())), 3, 2);
    gridLayout->addWidget(createButton("+", SLOT(operatorClicked())), 3, 3);

    // Row 4: 0, ., =
    gridLayout->addWidget(createButton("0", SLOT(digitClicked())), 4, 0, 1, 2); // widget, row column, row span, column span = 2 (wide to fit the grid niecely)
    gridLayout->addWidget(createButton(".", SLOT(digitClicked())), 4, 2);
    gridLayout->addWidget(createButton("=", SLOT(equalClicked())), 4, 3);

    // Main window
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(historyDisplay);
    mainLayout->addWidget(mainDisplay);
    mainLayout->addLayout(gridLayout);

    setLayout(mainLayout);
}

// Helper for creating buttons
QPushButton *Calculator::createButton(const QString &text, const char *member)
{
    QPushButton *btn = new QPushButton(text); // Set "text"
    btn->setMinimumSize(40, 40);
    btn->setStyleSheet("font-size: 18px; font-weight: bold;");
    connect(btn, SIGNAL(clicked()), this, member); // (interactive part) makes sure the "member" will be called on every click
    return btn;
}

void Calculator::digitClicked()
{
    QPushButton *btn = qobject_cast<QPushButton *>(sender());
    if (!btn)
        return;
    QString digit = btn->text();

    if (digit == "+/-")
    {
        if (mainDisplay->text() != "0")
        {
            double value = mainDisplay->text().toDouble();
            mainDisplay->setText(QString::number(-value)); // Set displayed value to value*(-1)
        }
        return;
    }

    if (waitingForOperand) // New input overrides the current text on main display
    {
        if (digit == ".")
        {
            mainDisplay->setText("0.");
        }
        else
        {
            mainDisplay->setText(digit);
        }
        waitingForOperand = false;
    }
    else
    {
        if (digit == ".")
        {
            if (!mainDisplay->text().contains('.'))
            {
                mainDisplay->setText(mainDisplay->text() + digit);
            }
        }
        else
        {
            // Avoids leading zeros (e.g. 007)
            if (mainDisplay->text() == "0")
            {
                mainDisplay->setText(digit);
            }
            else
            {
                mainDisplay->setText(mainDisplay->text() + digit);
            }
        }
    }
}

void Calculator::operatorClicked()
{
    QPushButton *btn = qobject_cast<QPushButton *>(sender());
    if (!btn)
        return;
    QString newOperator = btn->text();

    // Clear history if previous click was on "=" button
    if (lastClickedWasEqual)
    {
        historyDisplay->clear();
        // Do not clear main display, beacuse that's where the solution is being shown
    }
    lastClickedWasEqual = false; // Resetujemy flagę

    // Change of operator (no number was provided) - "=/-" operator is being treated like a digit (digitClicked()) because it does not need the second argument for input
    if (waitingForOperand && !pendingOperator.isEmpty())
    {
        if (!historyDisplay->text().isEmpty())
        {
            QString currentHistory = historyDisplay->text();
            currentHistory.chop(1); // Remove the previous operator
            historyDisplay->setText(currentHistory + newOperator);
            pendingOperator = newOperator;
        }
        return;
    }

    // There was an operator set already,- calculate intermediate value (based on pending operator) and display it
    if (!pendingOperator.isEmpty())
    {
        double currentValue = mainDisplay->text().toDouble();

        // Calculate intermediate value and set pendingValue
        if (pendingOperator == "+")
        {
            pendingValue += currentValue;
        }
        else if (pendingOperator == "-")
        {
            pendingValue -= currentValue;
        }
        else if (pendingOperator == "*")
        {
            pendingValue *= currentValue;
        }
        else if (pendingOperator == "/")
        {
            if (currentValue != 0.0)
                pendingValue /= currentValue;
        }

        // Main display shows intermediate solution
        mainDisplay->setText(QString::number(pendingValue));
    }
    else
    {
        pendingValue = mainDisplay->text().toDouble();
    }

    // Set the new state of operation
    pendingOperator = newOperator;
    waitingForOperand = true;

    // Update history display
    historyDisplay->setText(historyDisplay->text() + mainDisplay->text() + pendingOperator);
}

void Calculator::equalClicked()
{
    if (pendingOperator.isEmpty() || waitingForOperand)
    {
        return;
    }

    double currentValue = mainDisplay->text().toDouble();
    double result = pendingValue;

    // Update history display
    QString expression = historyDisplay->text() + mainDisplay->text() + " =";

    // Calculation logic
    if (pendingOperator == "+")
    {
        result += currentValue;
    }
    else if (pendingOperator == "-")
    {
        result -= currentValue;
    }
    else if (pendingOperator == "*")
    {
        result *= currentValue;
    }
    else if (pendingOperator == "/")
    {
        if (currentValue == 0.0)
        {
            mainDisplay->setText("Błąd");
            historyDisplay->clear();
            pendingValue = 0.0;
            pendingOperator.clear();
            waitingForOperand = true;
            lastClickedWasEqual = true;
            return;
        }
        result /= currentValue;
    }

    // Display the solution and history
    historyDisplay->setText(expression);
    mainDisplay->setText(QString::number(result));

    // Reset the state
    pendingValue = result;
    waitingForOperand = true;
    pendingOperator.clear();

    // Flag
    lastClickedWasEqual = true;
}

void Calculator::clearClicked()
{
    mainDisplay->setText("0");
    historyDisplay->clear();
    pendingValue = 0.0;
    pendingOperator.clear();
    waitingForOperand = true;
}

void Calculator::randClicked()
{
    // Generate rand() in range [0,1]
    double randomValue = QRandomGenerator::global()->generateDouble();
    QString randomString = QString::number(randomValue, 'f', 6); // Cleanup

    // Show the result
    mainDisplay->setText(randomString);

    // Set the proper state
    waitingForOperand = false;
    lastClickedWasEqual = false;

    // Clear History if there was a completed expression there
    if (historyDisplay->text().contains('='))
    {
        historyDisplay->clear();
    }
}