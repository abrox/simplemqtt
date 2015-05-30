
cmake_minimum_required (VERSION 2.8.11)
project (smqtt)

add_subdirectory (src)
add_subdirectory (example)

set_target_properties( smqtt simple
    PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${smqtt_SOURCE_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${smqtt_SOURCE_DIR}/bin"
)


