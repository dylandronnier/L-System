CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

FIND_PACKAGE(Imagine REQUIRED)

PROJECT(lsys_sto)
add_executable(sto.out main.cpp lsystem.h lsystem.cpp)
ImagineUseModules(sto.out Graphics)

install(TARGETS sto.out RUNTIME DESTINATION bin)
