CMAKE_MINIMUM_REQUIRED(VERSION 2.6)


FIND_PACKAGE(Imagine REQUIRED)

PROJECT(context-sensitive)
add_executable(cs.out main.cpp lsystem.h lsystem.cpp)
ImagineUseModules(cs.out Graphics)

install(TARGETS cs.out RUNTIME DESTINATION bin)
