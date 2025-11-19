# Simple Qt 6 Calculator: A C++ GUI Example

### 🎓 This project was done for C++ Programming Course as a part of Theoretical Computer Science Studies at Jagiellonian University

## 💡 Project Concept

This project serves as a minimal, educational example demonstrating the foundational capabilities of the **Qt 6 Framework** for creating Graphical User Interfaces (GUI) using C++.

The core purpose is to illustrate the setup and use of key Qt components, including:
* **QWidget:** The base class for all user interface objects.
* **QGridLayout & QVBoxLayout:** Managers used to arrange widgets (buttons and displays).
* **QPushButton & QLineEdit:** Basic interactive widgets (buttons and text input/display fields).
* **Signals and Slots:** Qt's powerful mechanism for communication between objects (e.g., connecting a button click to a specific action/method).

---

## 💻 Code Overview (`calculator.cpp`)

The core logic is contained within the `Calculator` class, which manages the UI setup and the calculator's operational state.

### 1. User Interface Setup

The constructor sets up the layout:
* A **`historyDisplay`** (`QLineEdit`) shows the ongoing equation (e.g., "3+8+").
* A **`mainDisplay`** (`QLineEdit`) shows the currently entered number or the final result.
* A **`QGridLayout`** is used to arrange the $4 \times 5$ grid of numeric and operation buttons.
* The **`createButton`** helper function simplifies button creation and instantly connects the button's `clicked()` signal to the corresponding action slot within the `Calculator` object.

### 2. Operational Logic

The calculator uses a state-based approach based on three main private members:
* **`pendingValue`** (`double`): Stores the result of the previous operation or the first operand of the current operation.
* **`pendingOperator`** (`QString`): Stores the operator (`+`, `-`, `*`, `/`) awaiting the second operand.
* **`waitingForOperand`** (`bool`): A flag that determines if the next digit entered should **replace** the display content (`true`) or **append** to it (`false`).

| Function/Slot | Action |
| :--- | :--- |
| **`digitClicked()`** | Handles all number and decimal point inputs. It manages the `waitingForOperand` flag, ensuring a new number replaces the display after an operator or an `=` is pressed. |
| **`operatorClicked()`** | Triggers the calculation for chained operations (e.g., `5+3+`) and updates the **`pendingValue`** with the intermediate result. It updates the **`historyDisplay`** to show the full expression entered so far. |
| **`equalClicked()`** | Executes the final calculation using `pendingValue` and the number currently in the `mainDisplay`. It displays the final result and resets the operational state, setting the `lastClickedWasEqual` flag to prepare for a new, separate calculation. |
| **`randClicked()`** | Inserts a pseudo-random floating-point number between $[0, 1]$ into the `mainDisplay`, demonstrating a simple integration of non-arithmetic functions. |