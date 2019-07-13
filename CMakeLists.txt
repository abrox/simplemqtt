
cmake_minimum_required (VERSION 3.9)
project(smqtt VERSION 1.0.1 DESCRIPTION "Simle c++ wrapper for paho c interface")

include(GNUInstallDirs)

add_subdirectory (src)
add_subdirectory (example)

set_target_properties(smqtt PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(smqtt PROPERTIES SOVERSION 1)


# uninstall target
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
