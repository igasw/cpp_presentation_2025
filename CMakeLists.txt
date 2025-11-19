cmake_minimum_required(VERSION 3.16)

project(SimpleCalculator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Włączenie automatycznej obsługi MOC (Meta-Object Compiler) dla Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Znajdowanie pakietu Qt6 (moduł Widgets)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Definicja plików źródłowych
set(PROJECT_SOURCES
    main.cpp
    calculator.cpp
    calculator.h
)

# Tworzenie pliku wykonywalnego
add_executable(SimpleCalculator ${PROJECT_SOURCES})

# Linkowanie bibliotek Qt
target_link_libraries(SimpleCalculator PRIVATE Qt6::Widgets)

# Obsługa Windows (ukrycie konsoli przy uruchamianiu)
if(WIN32)
    set_property(TARGET SimpleCalculator PROPERTY WIN32_EXECUTABLE ON)
endif()