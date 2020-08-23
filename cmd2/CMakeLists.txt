cmake_minimum_required(VERSION 3.0)

project(bto_client)

find_package(PkgConfig)
pkg_check_modules(LIBUSB libusb-1.0 REQUIRED)
pkg_check_modules(PROTOBUF protobuf>=3.12 REQUIRED)
pkg_check_modules(GRPC grpc++>=1.30 REQUIRED)

set(LIBS)
if (${CMAKE_SYSTEM_PROCESSOR} STREQUAL "armv7l")
  set(LIBS ${LIBS} atomic)
endif()

file(GLOB SOURCES src/*.cpp gen/**/*.cc)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME}
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/gen/
  PUBLIC ${PROTOBUF_INCLUDE_DIRS}
  PUBLIC ${GRPC_INCLUDE_DIRS}

  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../src/
  PUBLIC ${LIBUSB_INCLUDE_DIRS}
)
target_link_directories(${PROJECT_NAME}
  PUBLIC ${PROTOBUF_LIBRARY_DIRS}
  PUBLIC ${GRPC_LIBRARY_DIRS}

  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../build
  PUBLIC ${LIBUSB_LIBRARY_DIRS}
)
target_link_libraries(${PROJECT_NAME}
  PUBLIC ${PROTOBUF_LIBRARIES}
  PUBLIC ${GRPC_LIBRARIES}
  PUBLIC grpc++_reflection

  PUBLIC bto_advanced_usbir_lib
  PUBLIC ${LIBUSB_LIBRARIES}

  PUBLIC ${LIBS}
)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
