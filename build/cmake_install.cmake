# Install script for directory: /home/fcs_basestation/catkin_ws/src/flexcraft/src

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/home/fcs_basestation/catkin_ws/src/flexcraft/install")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/home/fcs_basestation/catkin_ws/src/flexcraft/install/.catkin")
FILE(INSTALL DESTINATION "/home/fcs_basestation/catkin_ws/src/flexcraft/install" TYPE FILE FILES "/home/fcs_basestation/catkin_ws/src/flexcraft/build/catkin_generated/installspace/.catkin")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/home/fcs_basestation/catkin_ws/src/flexcraft/install/_setup_util.py")
FILE(INSTALL DESTINATION "/home/fcs_basestation/catkin_ws/src/flexcraft/install" TYPE PROGRAM FILES "/home/fcs_basestation/catkin_ws/src/flexcraft/build/catkin_generated/installspace/_setup_util.py")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/home/fcs_basestation/catkin_ws/src/flexcraft/install/env.sh")
FILE(INSTALL DESTINATION "/home/fcs_basestation/catkin_ws/src/flexcraft/install" TYPE PROGRAM FILES "/home/fcs_basestation/catkin_ws/src/flexcraft/build/catkin_generated/installspace/env.sh")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/home/fcs_basestation/catkin_ws/src/flexcraft/install/setup.bash")
FILE(INSTALL DESTINATION "/home/fcs_basestation/catkin_ws/src/flexcraft/install" TYPE FILE FILES "/home/fcs_basestation/catkin_ws/src/flexcraft/build/catkin_generated/installspace/setup.bash")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/home/fcs_basestation/catkin_ws/src/flexcraft/install/setup.sh")
FILE(INSTALL DESTINATION "/home/fcs_basestation/catkin_ws/src/flexcraft/install" TYPE FILE FILES "/home/fcs_basestation/catkin_ws/src/flexcraft/build/catkin_generated/installspace/setup.sh")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/home/fcs_basestation/catkin_ws/src/flexcraft/install/setup.zsh")
FILE(INSTALL DESTINATION "/home/fcs_basestation/catkin_ws/src/flexcraft/install" TYPE FILE FILES "/home/fcs_basestation/catkin_ws/src/flexcraft/build/catkin_generated/installspace/setup.zsh")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/home/fcs_basestation/catkin_ws/src/flexcraft/install/.rosinstall")
FILE(INSTALL DESTINATION "/home/fcs_basestation/catkin_ws/src/flexcraft/install" TYPE FILE FILES "/home/fcs_basestation/catkin_ws/src/flexcraft/build/catkin_generated/installspace/.rosinstall")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/etc/catkin/profile.d" TYPE FILE FILES "/opt/ros/hydro/share/catkin/cmake/env-hooks/05.catkin_make.bash")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/etc/catkin/profile.d" TYPE FILE FILES "/opt/ros/hydro/share/catkin/cmake/env-hooks/05.catkin_make_isolated.bash")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("/home/fcs_basestation/catkin_ws/src/flexcraft/build/gtest/cmake_install.cmake")
  INCLUDE("/home/fcs_basestation/catkin_ws/src/flexcraft/build/flexcraft_msgs/cmake_install.cmake")
  INCLUDE("/home/fcs_basestation/catkin_ws/src/flexcraft/build/control_sw/basic_translator/cmake_install.cmake")
  INCLUDE("/home/fcs_basestation/catkin_ws/src/flexcraft/build/controllers/fcs_keyboard/cmake_install.cmake")
  INCLUDE("/home/fcs_basestation/catkin_ws/src/flexcraft/build/rosserial/rosserial/cmake_install.cmake")
  INCLUDE("/home/fcs_basestation/catkin_ws/src/flexcraft/build/rosserial/rosserial_client/cmake_install.cmake")
  INCLUDE("/home/fcs_basestation/catkin_ws/src/flexcraft/build/rosserial/rosserial_msgs/cmake_install.cmake")
  INCLUDE("/home/fcs_basestation/catkin_ws/src/flexcraft/build/rosserial/rosserial_arduino/cmake_install.cmake")
  INCLUDE("/home/fcs_basestation/catkin_ws/src/flexcraft/build/rosserial/rosserial_embeddedlinux/cmake_install.cmake")
  INCLUDE("/home/fcs_basestation/catkin_ws/src/flexcraft/build/rosserial/rosserial_python/cmake_install.cmake")
  INCLUDE("/home/fcs_basestation/catkin_ws/src/flexcraft/build/rosserial/rosserial_server/cmake_install.cmake")
  INCLUDE("/home/fcs_basestation/catkin_ws/src/flexcraft/build/rosserial/rosserial_windows/cmake_install.cmake")
  INCLUDE("/home/fcs_basestation/catkin_ws/src/flexcraft/build/rosserial/rosserial_xbee/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

IF(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
ELSE(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
ENDIF(CMAKE_INSTALL_COMPONENT)

FILE(WRITE "/home/fcs_basestation/catkin_ws/src/flexcraft/build/${CMAKE_INSTALL_MANIFEST}" "")
FOREACH(file ${CMAKE_INSTALL_MANIFEST_FILES})
  FILE(APPEND "/home/fcs_basestation/catkin_ws/src/flexcraft/build/${CMAKE_INSTALL_MANIFEST}" "${file}\n")
ENDFOREACH(file)
