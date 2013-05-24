cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(pi C)


if("${DISTRIBUTION}" MATCHES "debug")
  set(DISTRIBUTION "debug")
  set(CMAKE_C_FLAGS "-Wall -O0 -g -fPIC")
  add_definitions(-DDEBUG)
else()
  set(CMAKE_C_FLAGS "-Wall -Werror -O2")
  set(DISTRIBUTION "release")
endif()
message("-- Target mode: ${DISTRIBUTION}")

# update directories
set(PI_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(PI_SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(TK_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/../tk/include)
set(EXECUTABLE_OUTPUT_PATH ${PI_BINARY_DIR})

# global config
include_directories("${TK_INCLUDE_DIR}")

# removes generated files
add_custom_target(clean-all
   COMMAND ${CMAKE_BUILD_TOOL} clean
   COMMAND ${CMAKE_COMMAND} -P cmake/clean-all.cmake
)

# The version number.
set (PI_VERSION_MAJOR 2)
set (PI_VERSION_MINOR 0)

# To produce x86_64 binaries
if("${CMAKE_BUILD_TYPE}" MATCHES "x86_64")
  # the name of the target operating system
  set(CMAKE_SYSTEM_NAME Linux)

  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m64")

  set(PI_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin/${DISTRIBUTION}/x86_64)
  set(EXECUTABLE_OUTPUT_PATH ${PI_BINARY_DIR})
  file(MAKE_DIRECTORY ${PI_BINARY_DIR})
  link_directories("${CMAKE_SOURCE_DIR}/../tk/lib/${DISTRIBUTION}/x86_64")
# To produce x86 binaries
elseif("${CMAKE_BUILD_TYPE}" MATCHES "x86")
  # the name of the target operating system
  set(CMAKE_SYSTEM_NAME Linux)
 
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32")

  set(PI_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin/${DISTRIBUTION}/x86)
  set(EXECUTABLE_OUTPUT_PATH ${PI_BINARY_DIR})
  file(MAKE_DIRECTORY ${PI_BINARY_DIR})
  link_directories("${CMAKE_SOURCE_DIR}/../tk/lib/${DISTRIBUTION}/x86")
# To produce xscale binaries
elseif("${CMAKE_BUILD_TYPE}" MATCHES "xscale")
  set(CMAKE_SYSTEM_NAME Linux)
  set(CMAKE_SYSTEM_VERSION 1)

  set(CMAKE_X_HOME /usr/local/arm-linux-4.4.2-v4)
  # specify the cross compiler
  set(CMAKE_C_COMPILER ${CMAKE_X_HOME}/bin/xscale-none-linux-gnueabi-gcc)
   
  # where is the target environment 
  set(CMAKE_FIND_ROOT_PATH  ${CMAKE_X_HOME})

  # search for programs in the build host directories
  set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
  # for libraries and headers in the target directories
  set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
  set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

  add_definitions(-DTARGET_BIGENDIAN)

  set(PI_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin/${DISTRIBUTION}/xscale)
  set(EXECUTABLE_OUTPUT_PATH ${PI_BINARY_DIR})
  file(MAKE_DIRECTORY ${PI_BINARY_DIR})
  link_directories("${CMAKE_SOURCE_DIR}/../tk/lib/${DISTRIBUTION}/xscale")

else()
  message(FATAL_ERROR "Invalid usage please use: cmake -DCMAKE_BUILD_TYPE=[x86|x86_64|xscale]")
endif()

add_subdirectory(${PI_SRC_DIR})
