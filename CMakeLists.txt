cmake_minimum_required(VERSION 2.8)

set(CMAKE_INSTALL_PREFIX $ENV{HOME} CACHE PATH "install prefix")
set(CMAKE_BUILD_TYPE Release CACHE STRING "build type")
set(CMAKE_CXX_FLAGS_DEBUG "-g -W -Wall" CACHE STRING "CXX_FLAGS for debug")
set(CMAKE_C_FLAGS_DEBUG "-g -W -Wall" CACHE STRING "C_FLAGS for debug")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -W -Wall" CACHE STRING "CXX_FLAGS for release")
set(CMAKE_C_FLAGS_RELEASE "-O2 -W -Wall" CACHE STRING "C_FLAGS for release")

project(NormGeometry4)
add_definitions("-std=c++11")
set(TARGET_LIBRARY NormGeometry4)
set(G4_LIB_DIR $ENV{G4_LIB_DIR})

if(NOT DEFINED CS_INSTALL)
  if($ENV{CS_INSTALL})
    set(CS_INSTALL $ENV{CS_INSTALL})
  else($ENV{CS_INSTALL})
    set(CS_INSTALL $ENV{HOME})
  endif($ENV{CS_INSTALL})
endif(NOT DEFINED CS_INSTALL)

set(CMAKE_MODULE_PATH ${CS_INSTALL}/lib/comptonsoft ${CMAKE_MODULE_PATH})
include(UseComptonSoft)

message("-- Install destination prefix: ${CMAKE_INSTALL_PREFIX}")

option(USE_RUBY "enable Ruby binding" ON)

add_definitions(-DANL_USE_HEPVECTOR)
include_directories(include
  ${ANLG4_INC_DIR}
  ${ANLNEXT_INC_DIR}
  ${G4_INC_DIR}
  )

link_directories(
  ${ANLG4_LIB_DIR}
  ${ANLNEXT_LIB_DIR}
  ${G4_LIB_DIR}
  )

add_library(${TARGET_LIBRARY} SHARED
  src/NormMainGeometry.cc
  src/NormMainGeometryRealWorld.cc
  src/GeometryNorm.cc
  src/GeometryComptonCamera.cc
  src/AHG4ElementHandler.cc
  src/AHG4MaterialManager.cc
  src/AHG4MaterialProperty.cc
  )

target_link_libraries(${TARGET_LIBRARY}
  ${ANLG4_LIB} ${ANLNEXT_LIB} ${G4_LIB})

install(TARGETS ${TARGET_LIBRARY}
  LIBRARY
  DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

if(USE_RUBY)
  add_subdirectory(ruby)
endif(USE_RUBY)
