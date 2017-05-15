# Install script for directory: C:/Users/xchuki00/Documents/Bakalarska_prace/3rd_parties/libs/bullet3-2.85.1/src

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

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/bullet" TYPE FILE FILES
    "C:/Users/xchuki00/Documents/Bakalarska_prace/3rd_parties/libs/bullet3-2.85.1/src/btBulletCollisionCommon.h"
    "C:/Users/xchuki00/Documents/Bakalarska_prace/3rd_parties/libs/bullet3-2.85.1/src/btBulletDynamicsCommon.h"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Users/xchuki00/Documents/Bakalarska_prace/3rd_parties/libs/bullet3-2.85.1/bullet_build/src/Bullet3OpenCL/cmake_install.cmake")
  include("C:/Users/xchuki00/Documents/Bakalarska_prace/3rd_parties/libs/bullet3-2.85.1/bullet_build/src/Bullet3Serialize/Bullet2FileLoader/cmake_install.cmake")
  include("C:/Users/xchuki00/Documents/Bakalarska_prace/3rd_parties/libs/bullet3-2.85.1/bullet_build/src/Bullet3Dynamics/cmake_install.cmake")
  include("C:/Users/xchuki00/Documents/Bakalarska_prace/3rd_parties/libs/bullet3-2.85.1/bullet_build/src/Bullet3Collision/cmake_install.cmake")
  include("C:/Users/xchuki00/Documents/Bakalarska_prace/3rd_parties/libs/bullet3-2.85.1/bullet_build/src/Bullet3Geometry/cmake_install.cmake")
  include("C:/Users/xchuki00/Documents/Bakalarska_prace/3rd_parties/libs/bullet3-2.85.1/bullet_build/src/Bullet3Common/cmake_install.cmake")
  include("C:/Users/xchuki00/Documents/Bakalarska_prace/3rd_parties/libs/bullet3-2.85.1/bullet_build/src/BulletInverseDynamics/cmake_install.cmake")
  include("C:/Users/xchuki00/Documents/Bakalarska_prace/3rd_parties/libs/bullet3-2.85.1/bullet_build/src/BulletSoftBody/cmake_install.cmake")
  include("C:/Users/xchuki00/Documents/Bakalarska_prace/3rd_parties/libs/bullet3-2.85.1/bullet_build/src/BulletCollision/cmake_install.cmake")
  include("C:/Users/xchuki00/Documents/Bakalarska_prace/3rd_parties/libs/bullet3-2.85.1/bullet_build/src/BulletDynamics/cmake_install.cmake")
  include("C:/Users/xchuki00/Documents/Bakalarska_prace/3rd_parties/libs/bullet3-2.85.1/bullet_build/src/LinearMath/cmake_install.cmake")

endif()

