add_library(shader Shader.cpp)

set(glad_DIR ../../build/)

find_package(glad REQUIRED)

target_link_libraries(shader glad::glad)
