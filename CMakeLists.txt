cmake_minimum_required(VERSION 3.18)

set(CMAKE_POLICY_DEFAULT_CMP0048 NEW)

# Allow to set up the options for the dependencies.
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

# Allow to specify the MSVC runtime library for the dependencies.
set(CMAKE_POLICY_DEFAULT_CMP0091 NEW)

option(LAPLACE_ENABLE_EXE       "Enable building executable" ON)
option(LAPLACE_ENABLE_LIB       "Enable building static library" OFF)
option(LAPLACE_ENABLE_TESTING   "Enable testing" OFF)
option(LAPLACE_ENABLE_COVERAGE  "Enable coverage reporting" OFF)
option(LAPLACE_VERBOSE          "Enable verbose logging" ON)

set(LAPLACE_PROJECT   laplace)
set(LAPLACE_OBJ       laplace-obj)
set(LAPLACE_LIB       laplace)
set(LAPLACE_CONFIG    laplace-config)
set(LAPLACE_SOCKETS   laplace-sockets)
set(LAPLACE_UNITTESTS laplace-unittests)
set(QUADWAR_OBJ       quadwar-obj)
set(QUADWAR_EXE       quadwar)

set(CMAKE_CXX_STANDARD 20)

project(
  ${LAPLACE_PROJECT}
    VERSION 0.1.1
    DESCRIPTION "A game engine focused on RTS."
    LANGUAGES CXX
)

include(cmake/fetch-deps.cmake)

if(LAPLACE_ENABLE_EXE OR LAPLACE_ENABLE_LIB)

  find_package(Python3 REQUIRED)

  execute_process(
    COMMAND ${Python3_EXECUTABLE} embed.py
    COMMAND ${Python3_EXECUTABLE} gen-gl.py
    WORKING_DIRECTORY tools
  )

  if(LAPLACE_VERBOSE)
    add_compile_definitions(LAPLACE_VERBOSE)
  endif()

  add_library(${LAPLACE_OBJ} OBJECT)
  add_library(${QUADWAR_OBJ} OBJECT)
  add_subdirectory(source)

  include(cmake/config.cmake)

  target_link_libraries(
    ${LAPLACE_OBJ}
      PUBLIC
        ${LAPLACE_CONFIG}
        gtest benchmark wolfssl freetype
  )

  target_link_libraries(${QUADWAR_OBJ} PUBLIC ${LAPLACE_OBJ})

  target_compile_features(${LAPLACE_OBJ} PRIVATE cxx_std_20)
  target_compile_features(${QUADWAR_OBJ} PRIVATE cxx_std_20)

  if(LAPLACE_ENABLE_LIB)
    add_library(${LAPLACE_LIB} STATIC)
    target_link_libraries(${LAPLACE_LIB} PUBLIC ${LAPLACE_OBJ})
  endif()

  if(LAPLACE_ENABLE_EXE)
    add_executable(${QUADWAR_EXE})
    target_link_libraries(${QUADWAR_EXE} PUBLIC ${QUADWAR_OBJ} ${LAPLACE_OBJ})

    if(MSVC)
      target_link_options(${QUADWAR_EXE} PRIVATE "/SUBSYSTEM:CONSOLE")
    endif()

    if(LAPLACE_ENABLE_TESTING OR LAPLACE_ENABLE_COVERAGE)
      enable_testing()

      add_test(
        NAME ${LAPLACE_UNITTESTS}
        COMMAND ${QUADWAR_EXE} --tests
      )

      set_tests_properties(
        ${LAPLACE_UNITTESTS}
          PROPERTIES
            TIMEOUT "40"
      )
    endif()
  endif()

endif()

include(GNUInstallDirs)
include(cmake/hotfix-ft2.cmake)
