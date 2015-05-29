add_executable (simple simple.cpp)

target_link_libraries (simple LINK_PUBLIC smqtt paho-mqtt3c)
