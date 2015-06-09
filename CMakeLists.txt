
cmake_minimum_required (VERSION 2.8.11)
project (smqtt)

add_subdirectory (src)
add_subdirectory (example)

SET ( LIB_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/lib")

set_target_properties( smqtt simple
    PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${smqtt_SOURCE_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${smqtt_SOURCE_DIR}/bin"
)

SET ( LIB_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/lib")
SET ( HEADER_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/include/smqtt")

INSTALL(FILES
           ${smqtt_SOURCE_DIR}/lib/libsmqtt.so
        DESTINATION
           ${LIB_INSTALL_DIR}
       )

INSTALL(FILES
           ${smqtt_SOURCE_DIR}/src/mqttutils.h
           ${smqtt_SOURCE_DIR}/src/simplemqttclient.h
        DESTINATION
           ${HEADER_INSTALL_DIR}
       )

# uninstall target
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
