cmake_minimum_required(VERSION 3.5)

project(07.homework)

# Lookup for pre-built gtest
find_package(GTest)

# Main target
add_executable(containers src/main.cpp)

# clang-format
find_program(CLANG-FORMAT_PATH NAMES clang-format REQUIRED)
message(STATUS "Найден clang-format: ${CLANG-FORMAT_PATH}")
file(GLOB_RECURSE CLANG-FORMAT_SRC CONFIGURE_DEPENDS *.*pp)
message(STATUS "Найдены src: ${CLANG-FORMAT_SRC}")
add_custom_target(clangformat
    COMMAND ${CLANG-FORMAT_PATH} -i ${CLANG-FORMAT_SRC}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Форматирование ${PROJECT_NAME} с ${CLANG-FORMAT_PATH}"
)
add_dependencies(containers clangformat)

# Test target
add_executable(test_cont test/list_test.cpp test/serial_test.cpp 
)

# Add src to the include directories for the test target
target_include_directories(
    test_cont PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/src"
)

message(STATUS ${GTEST_INCLUDE_DIRS})
message(STATUS ${GTEST_LIBRARY})

# Add googletest to the include directories for the test target
target_include_directories(
    test_cont PRIVATE
    ${GTEST_INCLUDE_DIRS}
)

# Link test target against gtest libraries
target_link_libraries(
    test_cont PRIVATE
    ${GTEST_LIBRARY}
)

set_target_properties(containers PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
set_target_properties(test_cont PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

target_compile_options(containers PRIVATE
    -Wall
    -Wextra
    -pedantic
    -Werror
    # -fsanitize=address # only for debug and test builds!
)
# target_link_options(containers PRIVATE
#     -fsanitize=address
# )

target_compile_options(test_cont PRIVATE
    -Wall
    -Wextra
    -pedantic
    -Werror
)

