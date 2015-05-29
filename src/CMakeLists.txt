add_library (smqtt SHARED simplemqttclient.cpp)

target_include_directories (smqtt PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
