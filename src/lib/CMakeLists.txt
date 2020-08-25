cmake_minimum_required(VERSION 3.0)

project(bto_advanced_usbir_lib)

find_package(PkgConfig)
pkg_check_modules(LIBUSB libusb-1.0 REQUIRED)

file(GLOB LIB_SOURCES src/*.c)

add_library(${PROJECT_NAME} STATIC ${LIB_SOURCES})
target_include_directories(${PROJECT_NAME}
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/
  PUBLIC ${LIBUSB_INCLUDE_DIRS}
)

set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 11)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)

install(
  TARGETS ${PROJECT_NAME}
  DESTINATION lib/bto
)

install(
  FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/btoir.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/plarail.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/type.h
  DESTINATION include/bto
)
