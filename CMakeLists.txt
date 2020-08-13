cmake_minimum_required(VERSION 3.0)

project(bto_advanced_usbir_lib)

find_package(PkgConfig)
pkg_check_modules(LIBUSB libusb-1.0 REQUIRED)

file(GLOB LIB_SOURCES src/*.c)

add_library(${PROJECT_NAME} STATIC ${LIB_SOURCES})
target_include_directories(${PROJECT_NAME}
  PUBLIC ${LIBUSB_INCLUDE_DIRS}
)
