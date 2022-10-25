cmake_minimum_required(VERSION 3.23)
project(KF_Predict)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(OpenCV REQUIRED)
find_package(Ceres REQUIRED COMPONENTS EigenSparse)
find_package(Eigen3 REQUIRED)
find_package(Qt5 COMPONENTS Core Gui Widgets PrintSupport REQUIRED)

include_directories(${EIGEN3_INCLUDE_DIRS})
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(KF_Predict
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        qcustomplot.h
        qcustomplot.cpp
        KF/kf_cv_one.cpp KF/kf_cv_one.h KF/kf_ca_one.cpp KF/kf_ca_one.h EKF/ekf_cv_one.cpp EKF/ekf_cv_one.h KF/kf_cv_three.cpp KF/kf_cv_three.h predict/Buffpredict.cpp predict/Buffpredict.h)

target_link_libraries(KF_Predict
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::PrintSupport
        ${Eigen3_LIBRARIES}
        ${OpenCV_LIBS}
        )

