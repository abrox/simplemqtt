
/*
MIT License
Copyright (c) 2019 Jukka-Pekka Sarjanen
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
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
