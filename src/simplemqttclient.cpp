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
#include "simplemqttclient.h"
#include <iostream>
#include <assert.h>
#include"mqttutils.h"

int msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message)
{
    SimpleMqttClient* ctx = (SimpleMqttClient*) context;
    assert(ctx);
    return ctx->handleRawMsgArrvd(topicName,topicLen,message);
}

void connlost(void *context, char *cause)
{
    SimpleMqttClient* ctx = (SimpleMqttClient*) context;
    assert(ctx);
    ctx->handleConnectionLost(cause);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

SimpleMqttClient::SimpleMqttClient(const char* addr, const char * clientId)
{
    int rc;
    rc = MQTTClient_create(&mqqtClient, addr, clientId, MQTTCLIENT_PERSISTENCE_NONE, NULL);
    if ( rc != MQTTCLIENT_SUCCESS )
    {
        throw std::runtime_error(Formatter()<< __FILENAME__
                                            << __LINE__
                                            << " MQTTClient_create() fails rc: " << rc);
    }

    rc = MQTTClient_setCallbacks(mqqtClient, this, connlost, msgarrvd, NULL);
    if ( rc != MQTTCLIENT_SUCCESS )
    {
        throw std::runtime_error(Formatter()<< __FILENAME__
                                            << __LINE__
                                            << " MQTTClient_setCallbacks() fails rc: " << rc);
    }
}


SimpleMqttClient::~SimpleMqttClient()
{
    MQTTClient_disconnect(mqqtClient, 10000);
    MQTTClient_destroy(&mqqtClient);

}

int SimpleMqttClient::publishToMqttServer(const std::string& topic, const std::string& data, SimpleMqttClient::Qos qos)
{
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    MQTTClient_deliveryToken token;

    pubmsg.payload = (char*)data.c_str();
    pubmsg.payloadlen = data.length();
    pubmsg.qos = qos;
    pubmsg.retained = 0;

    return MQTTClient_publishMessage(mqqtClient, topic.c_str(), &pubmsg, &token);
}

int SimpleMqttClient::subscribeFromMqttServer(const std::string& topic, SimpleMqttClient::Qos qos)
{
    return MQTTClient_subscribe(mqqtClient, topic.c_str(), qos);

}

int SimpleMqttClient::handleStringMsgArrvd(std::string & topic, std::string & data)
{
    std::cout << "Topic: " << topic << " Data: "  << data  << std::endl;
    return 1;
}

int SimpleMqttClient::handleRawMsgArrvd(char *topicName, int topicLen, MQTTClient_message *message)
{
    char* payloadptr = (char*)message->payload;
    std::string topic(topicName );
    std::string data(payloadptr, message->payloadlen);

    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);

    return handleStringMsgArrvd(topic,data);
}

void SimpleMqttClient::handleConnectionLost(char * cause)
{

     std::cout << "Connection Lost: " << cause << std::endl;
}

int SimpleMqttClient::connectToMqttServer()
{
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;

    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;

    return MQTTClient_connect(mqqtClient, &conn_opts);
}
