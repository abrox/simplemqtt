add_executable (smqtt-example simple.cpp)

target_link_libraries (smqtt-example LINK_PUBLIC smqtt paho-mqtt3c)
install(TARGETS smqtt-example DESTINATION ${CMAKE_INSTALL_BINDIR})
