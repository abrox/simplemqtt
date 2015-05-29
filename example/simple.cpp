#include <iostream>
#include <sstream>

#include <unistd.h>
#include <stdlib.h>

#include "simplemqttclient.h"

int main(int argc, char *argv[])
{
    int rc,val;
    SimpleMqttClient client("localhost","dummy");
    rc = client.connectToMqttServer();
    if (rc)
    {
       std::cout << "Connect failed rc:"<< rc << std::endl;
       exit(-1);
    }
    rc = client.subscribeFromMqttServer("simple/#");

    if (rc)
    {
       std::cout << "subscribe failed rc:"<< rc << std::endl;
       exit(-1);
    }

    std::cout << "Publish few messages and exit..."<< std::endl;
    val=0;

    while(val < 5)
    {
        val++;
        std::ostringstream s;
        s << "Hello from simpleclient" << val;
        client.publishToMqttServer("simple/data",s.str());
        sleep(2);
    }

    return 0;
}
