add_library (smqtt SHARED simplemqttclient.cpp)

set_target_properties(smqtt PROPERTIES PUBLIC_HEADER "simplemqttclient.h")
target_include_directories (smqtt PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS smqtt
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
