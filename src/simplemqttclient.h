#ifndef SIMPLEMQTTCLIENT_H
#define SIMPLEMQTTCLIENT_H

#include "MQTTClient.h"
#include <string>


///
/// \brief The SimpleMqttClient class
///Yber simple mqtt implementation to create C++ interface for
/// paho( http://www.eclipse.org/paho/)
class SimpleMqttClient
{
public:
    ///
    /// \brief The Qos enum
    /// follows normal mqtt quality of service values.
     enum Qos{ QoS0=0,///< Fire and forget - the message may not be delivered .
               Qos1=1,///< At least once - the message will be delivered, but may be delivered more than once in some circumstances.
               Qos2=2 ///< Once and one only - the message will be delivered exactly once.
             };

     ///
     /// \brief SimpleMqttClient
     /// Intilize mqtt client and callback fuctions
     /// \throw std::runtime_error with rc in case fail.
     /// \param addr mqtt server address.
     /// \param clientId
     ///
    SimpleMqttClient(const char* addr, const char * clientId);

    ~SimpleMqttClient();
    ///
    /// \brief connect to Mqtt server
    /// \return 0 on success( MQTTCLIENT_SUCCESS) , \see Eclipse Paho documentation
    ///  about detailed error codes
    ///
    int connectToMqttServer();

    int subscribeFromMqttServer(const std::string& topic,
                                Qos qos= QoS0
                                );

    int publishToMqttServer(const std::string& topic,
                            const std::string& data,
                            Qos qos= QoS0
                           );


    virtual int handleRawMsgArrvd(char *topicName,
                                  int topicLen,
                                  MQTTClient_message *message
                                  );

    virtual int handleStringMsgArrvd(std::string & topic,
                                     std::string & data
                                     );



    virtual void handleConnectionLost(char * cause);
private:
    MQTTClient mqqtClient;
};

#endif // SIMPLEMQTTCLIENT_H
