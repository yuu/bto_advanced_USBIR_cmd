cmake_minimum_required(VERSION 3.0)

project(bto_advanced_USBIR_cmd)

find_package(PkgConfig)
pkg_check_modules(LIBUSB libusb-1.0 REQUIRED)

file(GLOB SOURCES src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME}
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../src/
  PUBLIC ${LIBUSB_INCLUDE_DIRS}
)
target_link_directories(${PROJECT_NAME}
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../build
  PUBLIC ${LIBUSB_LIBRARY_DIRS}
)
target_link_libraries(${PROJECT_NAME}
  PUBLIC bto_advanced_usbir_lib
  PUBLIC ${LIBUSB_LIBRARIES}
)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
