cmake_minimum_required (VERSION 2.8)

set (C2BA_LIBRARY_NAME c2ba_glutils)
set (C2BA_LIBRARY_CMAKE_PREFIX C2BA_GLUTILS)

project (${C2BA_LIBRARY_NAME})

option (${C2BA_LIBRARY_CMAKE_PREFIX}_BUILD_TESTS "Build tests for ${C2BA_LIBRARY_NAME} library" OFF)
set (${C2BA_LIBRARY_CMAKE_PREFIX}_GL3_HEADER "" CACHE STRING "Header to include for the declaration of OpenGL 3+ symbols")
set (${C2BA_LIBRARY_CMAKE_PREFIX}_GL3_INCLUDE_DIR "" CACHE STRING "Path to the header to include for the declaration of OpenGL 3+ symbols")
set (${C2BA_LIBRARY_CMAKE_PREFIX}_GL3_LIBRARIES "" CACHE STRING "Libraries to link to for the definition of OpenGL 3+ symbols (may be empty)")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(OpenGL REQUIRED)

set (${C2BA_LIBRARY_NAME}_VERSION_MAJOR 0)
set (${C2BA_LIBRARY_NAME}_VERSION_MINOR 1)
set (${C2BA_LIBRARY_NAME}_LIBRARY_NAME ${C2BA_LIBRARY_NAME})

configure_file (
    "${PROJECT_SOURCE_DIR}/lib/cmake/info.hpp.in"
    "${PROJECT_BINARY_DIR}/include/c2ba/glutils/info.hpp"
)

set_property (GLOBAL PROPERTY USE_FOLDERS ON)

include_directories ("lib/include")
include_directories ("lib/include/c2ba")
include_directories ("${PROJECT_BINARY_DIR}/include")
include_directories ("${PROJECT_BINARY_DIR}/include/c2ba")

if (DEFINED ${C2BA_LIBRARY_CMAKE_PREFIX}_GL3_HEADER)
    add_definitions(-D${C2BA_LIBRARY_CMAKE_PREFIX}_GL3_HEADER=${${C2BA_LIBRARY_CMAKE_PREFIX}_GL3_HEADER})
endif ()

add_definitions(-DNOMINMAX)

file (
    GLOB_RECURSE
    HEADER_FILES
    lib/*.hpp
)

file (
    GLOB_RECURSE
    PROJECT_FILES
    lib/*.cpp lib/*.hpp lib/*.in
)

add_library (
    ${C2BA_LIBRARY_NAME}
    ${PROJECT_FILES}
)

target_include_directories(
    ${C2BA_LIBRARY_NAME}
    PUBLIC
    ${OPENGL_INCLUDE_DIRS}
    ${${C2BA_LIBRARY_CMAKE_PREFIX}_GL3_INCLUDE_DIR}
)

target_link_libraries (
    ${C2BA_LIBRARY_NAME}
    ${OPENGL_LIBRARIES}
    ${${C2BA_LIBRARY_CMAKE_PREFIX}_GL3_LIBRARY}
)

source_group ("c2ba\\glutils" REGULAR_EXPRESSION "lib/(src|include/c2ba/glutils)/[^/]*.*")

if (${C2BA_LIBRARY_CMAKE_PREFIX}_BUILD_TESTS)
    set (${C2BA_LIBRARY_NAME}_TEST_INCLUDE_LIST "")
    
    foreach (HEADER_PATH ${HEADER_FILES})
        set (${C2BA_LIBRARY_NAME}_TEST_INCLUDE_LIST "${${C2BA_LIBRARY_NAME}_TEST_INCLUDE_LIST} #include \"${HEADER_PATH}\"\n")
    endforeach (HEADER_PATH)

    configure_file (
        "${PROJECT_SOURCE_DIR}/tests/headers_compilation_test.cpp.in"
        "${PROJECT_BINARY_DIR}/c2ba/glutils/tests/headers_compilation_test.cpp"
    )

    file (
        GLOB_RECURSE
        TEST_SRC_FILES
        tests/*.cpp tests/*.hpp "${PROJECT_BINARY_DIR}/c2ba/glutils/tests/headers_compilation_test.cpp"
    )
    
    add_executable (
        ${C2BA_LIBRARY_NAME}_run_tests
        ${TEST_SRC_FILES}
    )
    
    target_link_libraries (
        ${C2BA_LIBRARY_NAME}_run_tests
        ${C2BA_LIBRARY_NAME}
    )
    
endif (${C2BA_LIBRARY_CMAKE_PREFIX}_BUILD_TESTS)

install (DIRECTORY lib/include/c2ba DESTINATION include)
install (FILES "${PROJECT_BINARY_DIR}/include/c2ba/glutils/info.hpp" DESTINATION include/c2ba/glutils)

foreach (CONFIG ${CMAKE_CONFIGURATION_TYPES})
    install (
        TARGETS ${C2BA_LIBRARY_NAME}
        DESTINATION lib/${CONFIG}
        CONFIGURATIONS ${CONFIG}
    )
    install (
        DIRECTORY ${PROJECT_BINARY_DIR}/${CONFIG}
        DESTINATION lib
        CONFIGURATIONS ${CONFIG}
        FILES_MATCHING PATTERN ${C2BA_LIBRARY_NAME}.pdb
    )
endforeach (CONFIG)