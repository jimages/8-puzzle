cmake_minimum_required(VERSION 3.5)
project(quiz LANGUAGES CXX C)

option(test "Build all tests." OFF)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON )
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

option(test "Build all tests." OFF)
option(debug "debug mode." OFF)

if (debug)
	set(CMAKE_BUILD_TYPE Debug)
endif()

# Require packages.
#find_package(Boost REQUIRED)

# Set include
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/include)

# 这里填写添加库文件
#add_library(model STATIC)

# 这里添加执行文件的源代码
add_executable(main src/main.cc )
#target_link_libraries(library sqlite model)

if (test)

	# Set Warning
	if ( CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang|GNU" )
		add_compile_options(-Wall -Wextra -Wunreachable-code -Wpedantic)
	endif()
	if ( CMAKE_CXX_COMPILER_ID MATCHES "Clang" )
		add_compile_options(-Wweak-vtables -Wexit-time-destructors -Wglobal-constructors -Wmissing-noreturn )
	endif()
	if ( CMAKE_CXX_COMPILER_ID MATCHES "MSVC" )
		add_compile_options(/W4 /w44265 /w44061 /w44062 )
	endif()

    # add_subdirectory(lib/gtest)
    #include_directories(src/)

  enable_testing()

  # Include the gtest library. gtest_SOURCE_DIR is available due to
  # 'project(gtest)' above.
  include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

  ##############
  # Unit Tests
  ##############
  # 测试文件
  #add_executable(runUnitTests tests/test.cc)

  # Standard linking to gtest stuff.
  # 库文件
  #target_link_libraries(runUnitTests gtest gtest_main model sqlite)


  # This is so you can do 'make test' to see all your tests run, instead of
  # manually running the executable runUnitTests to see those specific tests.
  #add_test(NAME that-test-I-made COMMAND runUnitTests)

endif ()
