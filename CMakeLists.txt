cmake_minimum_required(VERSION 3.5)
project(tray-pumpkin)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find Qt5
find_package(Qt5 REQUIRED COMPONENTS Widgets)

# KDE Frameworks 5 (KStatusNotifierItem)
find_package(KF5Notifications REQUIRED)

# Yaml
find_package(yaml-cpp REQUIRED)

# Source files
set(SOURCES
    src/main.cpp
    src/AppConfig.cpp
    src/ConfigFinder.cpp
    src/TrayController.cpp
)

set(HEADERS
    src/AppConfig.h
    src/ConfigFinder.h
    src/TrayController.h
)

# Executable
add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
)

# Libraries
target_link_libraries(${PROJECT_NAME}
    Qt5::Widgets
    KF5::Notifications
    yaml-cpp
)

# where to find our CMake modules
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(Packing)
