cmake_minimum_required(VERSION 3.19)
project(QBankerSystem LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt6 REQUIRED COMPONENTS Widgets Xml)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/form)

qt_standard_project_setup()

include_directories(include)

qt_add_executable(QBankerSystem
    WIN32 MACOSX_BUNDLE
    # 아까 사진에서 form 안에 있었음

    # 소스 파일 경로
    src/main.cpp
    src/mainwindow.cpp
    src/userwindow.cpp
    src/adminwindow.cpp
    src/senddialog.cpp
    src/meminfodialog.cpp
    src/userhistorywindow.cpp
    src/adminhistorywindow.cpp
    src/signup.cpp

    # 헤더 파일 경로 (include 폴더 안에 있다면)
    include/signup.h
    include/mainwindow.h
    include/userwindow.h
    include/adminwindow.h
    include/senddialog.h
    include/meminfodialog.h
    include/userhistorywindow.h
    include/adminhistorywindow.h
    ${CMAKE_CURRENT_SOURCE_DIR}/form/mainwindow.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/form/userwindow.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/form/adminwindow.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/form/senddialog.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/form/meminfodialog.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/form/userhistorywindow.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/form/adminhistorywindow.ui
    

    # UI 파일 경로
    form/mainwindow.ui
    form/signup.ui
    include/datamanager.h
    include/history.h
    src/datamanager.cpp

)

target_link_libraries(QBankerSystem
    PRIVATE
        Qt::Core
        Qt::Widgets
Qt::Xml
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
