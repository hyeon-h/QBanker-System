cmake_minimum_required(VERSION 3.19)
project(QBankerSystem LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/form)

qt_standard_project_setup()

include_directories(include)

qt_add_executable(QBankerSystem
    WIN32 MACOSX_BUNDLE
    src/main.cpp
    src/mainwindow.cpp
    src/usermainwindow.cpp
    src/adminmainwindow.cpp
    include/mainwindow.h
    include/usermainwindow.h
    include/adminmainwindow.h
    ${CMAKE_CURRENT_SOURCE_DIR}/form/mainwindow.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/form/usermainwindow.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/form/adminmainwindow.ui
)

target_link_libraries(QBankerSystem
    PRIVATE
        Qt::Core
        Qt::Widgets
)

install(TARGETS QBankerSystem
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET QBankerSystem
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
