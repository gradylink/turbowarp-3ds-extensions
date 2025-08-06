cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(turbowarp-3ds-extensions CXX ASM)

if(NINTENDO_3DS)
set_property(GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS TRUE)

set(CMAKE_C_STANDARD_LIBRARIES "")
set(CMAKE_CXX_STANDARD_LIBRARIES "")
set(CMAKE_ASM_STANDARD_LIBRARIES "")
endif()

set(CMAKE_SHARED_LIBRARY_PREFIX "")

include(cmake/CPM.cmake)

CPMAddPackage(
    URI "gh:boostorg/regex#boost-1.88.0"
    OPTIONS "BOOST_REGEX_STANDALONE ON"
)

file(GLOB ALL_SOURCES *.cpp)

foreach(SOURCE_FILE ${ALL_SOURCES})
    get_filename_component(BASE_NAME "${SOURCE_FILE}" NAME_WE)

    if(NOT NINTENDO_WIIU)
      add_library(${BASE_NAME} SHARED ${SOURCE_FILE})
      target_link_libraries(${BASE_NAME} PRIVATE dl Boost::regex)
    endif()

    if(NINTENDO_3DS)
      set(RESOLVER_OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${BASE_NAME}-resolver.s")
      add_custom_command(
        OUTPUT "${RESOLVER_OUTPUT}"
        COMMAND ResGen "$<TARGET_FILE:${BASE_NAME}>" -o "${RESOLVER_OUTPUT}"
        DEPENDS ${BASE_NAME}
      )

      add_library(${BASE_NAME}-resolver OBJECT "${RESOLVER_OUTPUT}")
      target_compile_options(${BASE_NAME}-resolver PRIVATE -g0)
    elseif(NINTENDO_WIIU)
      add_executable(${BASE_NAME} "${SOURCE_FILE}")
      target_link_libraries(${BASE_NAME} PRIVATE Boost::regex)
      wut_add_exports(${BASE_NAME} ${BASE_NAME}.def)
      wut_create_rpl(${BASE_NAME})
    else()

    endif()

    # install(FILES "$<TARGET_FILE:${BASE_NAME}>" TYPE BIN)
endforeach()
