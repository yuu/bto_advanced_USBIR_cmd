cmake_minimum_required(VERSION 3.0)

project(grpc_bto)

find_package(PkgConfig)
pkg_check_modules(PROTOBUF protobuf>=3.12 REQUIRED)
pkg_check_modules(GRPC grpc++>=1.30 REQUIRED)

file(GLOB SOURCES gen/bto/*.cc)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME}
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/gen/

  PUBLIC ${PROTOBUF_INCLUDE_DIRS}
  PUBLIC ${GRPC_INCLUDE_DIRS}
)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

install(
  TARGETS ${PROJECT_NAME}
  DESTINATION lib/bto
)

install(
  FILES ${CMAKE_CURRENT_SOURCE_DIR}/gen/bto/ir_service.grpc.pb.h
        ${CMAKE_CURRENT_SOURCE_DIR}/gen/bto/ir_service.pb.h
  DESTINATION include/bto
)
