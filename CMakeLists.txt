cmake_minimum_required(VERSION 3.10)

project(Concepcao-veiculos-inteligentes)

set(OpenCV_DIR C:/opencv/build)
find_package(OpenCV REQUIRED)

add_executable(${PROJECT_NAME} src/Main.cpp src/HandTrackingModule.cpp)

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})