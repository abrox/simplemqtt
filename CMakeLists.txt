
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

INSTALL(FILES ${smqtt_SOURCE_DIR}/lib/libsmqtt.so DESTINATION ${LIB_INSTALL_DIR})

