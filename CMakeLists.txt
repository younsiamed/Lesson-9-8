cmake_minimum_required(VERSION 3.5)

project(PreUDPsocket LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Подключаем модули Qt, включая Network
find_package(Qt6 COMPONENTS Core Gui Widgets Network REQUIRED)

qt_standard_project_setup()

qt_add_executable(${PROJECT_NAME}
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Network)
