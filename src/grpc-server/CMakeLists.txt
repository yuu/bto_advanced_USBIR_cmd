cmake_minimum_required(VERSION 3.0)

project(bto_server)

find_package(PkgConfig)
pkg_check_modules(LIBUSB libusb-1.0 REQUIRED)
pkg_check_modules(PROTOBUF protobuf>=3.12 REQUIRED)
pkg_check_modules(GRPC grpc++>=1.30 REQUIRED)

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

GET_TARGET_PROPERTY(
  GRPC_BTO_BINARY_DIR
  grpc_bto
  BINARY_DIR
)

set(LIBS)
if (${CMAKE_SYSTEM_PROCESSOR} STREQUAL "armv7l")
   set(LIBS ${LIBS} atomic)
endif()

file(GLOB SOURCES src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME}
  PUBLIC ${BTO_ADVANCED_USBIR_LIB_INCLUDE_DIRS}
  PUBLIC ${GRPC_BTO_INCLUDE_DIRS}

  PUBLIC ${LIBUSB_INCLUDE_DIRS}
)
target_link_directories(${PROJECT_NAME}
  PUBLIC ${BTO_ADVANCED_USBIR_LIB_BINARY_DIR}
  PUBLIC ${GRPC_BTO_BINARY_DIR}

  PUBLIC ${LIBUSB_LIBRARY_DIRS}
  PUBLIC ${PROTOBUF_LIBRARY_DIRS}
  PUBLIC ${GRPC_LIBRARY_DIRS}
)
target_link_libraries(${PROJECT_NAME}
  PUBLIC bto_advanced_usbir_lib
  PUBLIC grpc_bto

  PUBLIC ${LIBUSB_LIBRARIES}
  PUBLIC ${PROTOBUF_LIBRARIES}
  PUBLIC ${GRPC_LIBRARIES}
  PUBLIC grpc++_reflection

  PUBLIC ${LIBS}
)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

install(
  TARGETS ${PROJECT_NAME}
  DESTINATION bin
)
