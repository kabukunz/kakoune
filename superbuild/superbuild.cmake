find_package(Git)

if(NOT GIT_FOUND)
  message(ERROR "Cannot find git. git is required for Superbuild")
endif()

option( USE_GIT_PROTOCOL "If behind a firewall turn this off to use http instead." ON)

set(git_protocol "git")
if(NOT USE_GIT_PROTOCOL)
  set(git_protocol "http")
endif()

include( ExternalProject )

include(superbuild/external-zlib.cmake)

set(ep_common_args
  -DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}
  -DCMAKE_CXX_COMPILER:STRING=${CMAKE_CXX_COMPILER}
  -DCMAKE_C_COMPILER:STRING=${CMAKE_C_COMPILER}
  -DCMAKE_GENERATOR:STRING=${CMAKE_GENERATOR}
  -DCMAKE_RUNTIME_OUTPUT_DIRECTORY:PATH=${CMAKE_BINARY_DIR}/kakoune-build/bin
  )

# Compute -G arg for configuring external projects with the same CMake generator:
if(CMAKE_EXTRA_GENERATOR)
  set(gen "${CMAKE_EXTRA_GENERATOR} - ${CMAKE_GENERATOR}")
else()
  set(gen "${CMAKE_GENERATOR}" )
endif()

option(kakoune_USE_WRAP_PYTHON "Add Python wrapping to the superbuild" ON)
if(NOT EXISTS PYTHON_EXECUTABLE AND kakoune_USE_WRAP_PYTHON OR kakoune_USE_VTK)
  include(${CMAKE_SOURCE_DIR}/superbuild/External-Python.cmake)
  list(APPEND kakoune_DEPENDENCIES Python)
  set(_python_args "-DPYTHON_EXECUTABLE:FILEPATH=${PYTHON_EXECUTABLE}")
endif()
