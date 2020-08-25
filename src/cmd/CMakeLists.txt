cmake_minimum_required(VERSION 3.0)

project(bto_advanced_USBIR_cmd)

find_package(PkgConfig)
pkg_check_modules(LIBUSB libusb-1.0 REQUIRED)

GET_TARGET_PROPERTY(
  BTO_ADVANCED_USBIR_LIB_INCLUDE_DIRS
  bto_advanced_usbir_lib
  INCLUDE_DIRECTORIES
)
GET_TARGET_PROPERTY(
  BTO_ADVANCED_USBIR_LIB_BINARY_DIR
  bto_advanced_usbir_lib
  BINARY_DIR
)

message('--------')
message(${BTO_ADVANCED_USBIR_LIB_INCLUDE_DIRS})
message(${BTO_ADVANCED_USBIR_LIB_BINARY_DIR})
message('--------')

file(GLOB SOURCES src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME}
  PUBLIC ${BTO_ADVANCED_USBIR_LIB_INCLUDE_DIRS}
  PUBLIC ${LIBUSB_INCLUDE_DIRS}
)
target_link_directories(${PROJECT_NAME}
  PUBLIC ${BTO_ADVANCED_USBIR_LIB_BINARY_DIR}
  PUBLIC ${LIBUSB_LIBRARY_DIRS}
)
target_link_libraries(${PROJECT_NAME}
  PUBLIC bto_advanced_usbir_lib
  PUBLIC ${LIBUSB_LIBRARIES}
)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

install(
  TARGETS ${PROJECT_NAME}
  DESTINATION bin
)
