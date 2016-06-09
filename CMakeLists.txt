cmake_minimum_required(VERSION 2.6)
project(kakoune)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${kakoune_SOURCE_DIR}/cmake")
set(BIN_DIR ${kakoune_SOURCE_DIR}/bin)

# Bump up warning levels appropriately for clang, gcc & msvc and build in debug mode
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=c++11")
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

if(KAK_DEBUG)
	add_definitions(-DKAK_DEBUG)
endif()

set(CURSES_NEED_NCURSESW TRUE)
find_package(NCursesw REQUIRED)

include_directories("./src")
file (GLOB kakoune_SOURCES src/*.cc)

include_directories(${CURSES_INCLUDE_DIR})
add_executable(kak ${kakoune_SOURCES})
target_link_libraries(kak PRIVATE ${CURSES_LIBRARY})

install(TARGETS kak RUNTIME DESTINATION ${BIN_DIR})
