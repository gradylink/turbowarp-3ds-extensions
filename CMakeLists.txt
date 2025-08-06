cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
project(turbowarp-3ds-extensions)

set_property(GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS TRUE)

set(CMAKE_C_STANDARD_LIBRARIES "")
set(CMAKE_CXX_STANDARD_LIBRARIES "")
set(CMAKE_ASM_STANDARD_LIBRARIES "")

set(CMAKE_SHARED_LIBRARY_PREFIX "")

file(GLOB ALL_SOURCES *.cpp)

foreach(SOURCE_FILE ${ALL_SOURCES})
    get_filename_component(BASE_NAME "${SOURCE_FILE}" NAME_WE)

    add_library(${BASE_NAME} SHARED ${SOURCE_FILE})
    target_link_libraries(${BASE_NAME} PRIVATE dl)

    set(RESOLVER_OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${BASE_NAME}-resolver.s")
    add_custom_command(
        OUTPUT "${RESOLVER_OUTPUT}"
        COMMAND ResGen "$<TARGET_FILE:${BASE_NAME}>" -o "${RESOLVER_OUTPUT}"
        DEPENDS ${BASE_NAME}
    )

    add_library(${BASE_NAME}-resolver OBJECT "${RESOLVER_OUTPUT}")
    target_compile_options(${BASE_NAME}-resolver PRIVATE -g0)

    install(FILES "$<TARGET_FILE:${BASE_NAME}>" TYPE BIN)
endforeach()
