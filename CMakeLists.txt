cmake_minimum_required(VERSION 3.16)

project(SimpleCalculator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable automatic MOC (Meta-Object Compiler) handling for Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find the Qt6 package (Widgets module)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Definition of source files
set(PROJECT_SOURCES
    main.cpp
    calculator.cpp
    calculator.h
)

# Create the executable file
add_executable(SimpleCalculator ${PROJECT_SOURCES})

# Link Qt libraries
target_link_libraries(SimpleCalculator PRIVATE Qt6::Widgets)

# Windows-specific handling (hide console when launching)
if(WIN32)
    set_property(TARGET SimpleCalculator PROPERTY WIN32_EXECUTABLE ON)
endif()