# Install script for directory: C:/Users/xchuki00/Documents/Bakalarska_prace/libs/bullet3-2.85.1/examples

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files/BULLET_PHYSICS")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Users/xchuki00/Documents/Bakalarska_prace/bullet_build/examples/HelloWorld/cmake_install.cmake")
  include("C:/Users/xchuki00/Documents/Bakalarska_prace/bullet_build/examples/BasicDemo/cmake_install.cmake")
  include("C:/Users/xchuki00/Documents/Bakalarska_prace/bullet_build/examples/ExampleBrowser/cmake_install.cmake")
  include("C:/Users/xchuki00/Documents/Bakalarska_prace/bullet_build/examples/ThirdPartyLibs/Gwen/cmake_install.cmake")
  include("C:/Users/xchuki00/Documents/Bakalarska_prace/bullet_build/examples/ThirdPartyLibs/BussIK/cmake_install.cmake")
  include("C:/Users/xchuki00/Documents/Bakalarska_prace/bullet_build/examples/OpenGLWindow/cmake_install.cmake")

endif()

