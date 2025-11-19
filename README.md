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

Equation is being solved in the order of input, this overrides the natural order of operations.

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

---

## ▶️ Getting Started: Building and Running the App

This project uses **CMake** as the build system, which simplifies dependency management for Qt applications.

### Prerequisites (What you need to install)

To compile and run this application, you need the following:

1.  **C++ Compiler:** A modern compiler (like GCC, Clang, or MSVC) supporting C++17.
2.  **CMake:** The cross-platform build system.
3.  **Qt 6 Library:** Specifically, the **Qt Widgets** module.
    * **Download:** The recommended way to install Qt 6 is via the **official Qt Installer** available on the Qt website. Ensure you select the appropriate compiler kit (e.g., MinGW or MSVC) that matches your system.
4.  **Extensions:** The **`C/C++`** and **`CMake Tools`** extensions.

### Build and Run Instructions (using VS Code)

1.  **Open the Project:** Open the project folder (containing `CMakeLists.txt`) in Visual Studio Code.
2.  **Configure CMake:** VS Code's CMake Tools extension will detect the `CMakeLists.txt` file.
    * **Select a Kit:** Click the "No active Kit" or "Select a Kit" prompt on the status bar and choose a **Kit** that correctly points to your C++ compiler and the **Qt 6 installation** you downloaded. *Tip: If CMake fails to find Qt, you may need to manually configure the `CMAKE_PREFIX_PATH` in the CMake settings to point to your Qt installation directory.*
    * **Run Configuration:** Once a Kit is selected, CMake automatically configures the project (creating a `build` directory).
3.  **Compile the Code:**
    * Press **`F7`** or open the Command Palette (`Ctrl+Shift+P` / `Cmd+Shift+P`) and search for **`CMake: Build`**. Select the target **`SimpleCalculator`**.
4.  **Run the Application:**
    * After a successful build, click the **Run** button (a small triangle next to the build status) on the VS Code status bar, or use the Command Palette command **`CMake: Launch Target`** and select **`SimpleCalculator`**.

The compiled executable will be located inside the generated `build/` directory (e.g., `build/SimpleCalculator.exe`).