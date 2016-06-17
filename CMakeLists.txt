cmake_minimum_required(VERSION 2.8.12)
foreach(p
  CMP0025
  CMP0042
  CMP0046
  CMP0054
  )
  if(POLICY ${p})
    cmake_policy(SET ${p} NEW)
  endif()
endforeach()

project(kakoune)

# Bump up warning levels appropriately for clang, gcc & msvc and build in debug mode
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "AppleClang")
        # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=c++14")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w -std=c++14")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O2")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
	if (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
		string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
	endif()
endif()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${kakoune_SOURCE_DIR}/cmake")

set(BIN_DIR ${kakoune_SOURCE_DIR}/bin)

if(KAK_DEBUG)
	add_definitions(-DKAK_DEBUG)
endif()

set(CURSES_NEED_NCURSESW TRUE)
find_package(NCursesw REQUIRED)

include_directories("./src")
include_directories("./src_module")

file (GLOB kakoune_SOURCES src/*.cc)
list(REMOVE_ITEM kakoune_SOURCES src/main.cc)
set(module_SOURCES src_module/kakoune.cc)

add_subdirectory(superbuild)

set(PYTHONLIBS_FOUND TRUE)
set(PYTHON_MODULE_EXTENSION .so)
set(PYTHON_MODULE_PREFIX "")
add_subdirectory(pybind11)


include_directories(${CURSES_INCLUDE_DIR} ${PYTHON_INCLUDE_DIR} ${PYBIND11_INCLUDE_DIR})

MESSAGE(STATUS "PYTHON_INCLUDE_DIR: " ${PYTHON_INCLUDE_DIR})
MESSAGE(STATUS "PYTHON_LIBRARY: " ${PYTHON_LIBRARY})

add_custom_target(superbuild
  cmake --build . --target Python
  BYPRODUCTS ${PYTHON_LIBRARY} ${ZLIB_LIBRARY}
  DEPENDS Python zlib
)

pybind11_add_module(kakoune ${module_SOURCES} ${kakoune_SOURCES} src_module/main.cc )
target_link_libraries(kakoune PRIVATE ${CURSES_LIBRARY})
add_dependencies(kakoune superbuild)

add_executable(kak ${kakoune_SOURCES} ${module_SOURCES} src/main.cc)
add_dependencies(kak Python zlib)
add_dependencies(kak superbuild)

target_link_libraries(kak ${CURSES_LIBRARY} ${PYTHON_LIBRARY})

MESSAGE(STATUS "BIN_DIR: " ${BIN_DIR})
install(TARGETS kak RUNTIME DESTINATION ${BIN_DIR})
