
add_library(lsystem STATIC lsystem.h lsystem.cpp)
add_library(shader STATIC shader.hpp shader.cpp)

install(TARGETS lsystem LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
install(TARGETS shader LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
