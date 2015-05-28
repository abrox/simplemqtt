#ifndef MQTTUTILS_H
#define MQTTUTILS_H

#endif // MQTTUTILS_H
#include<string>
#include<cstring>

#include<sstream>
#include<stdexcept>

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

///
/// \brief The Formatter class
///Utility to provide message with variables when trow.
/// from: http://stackoverflow.com/questions/12261915/howto-throw-stdexceptions-with-variable-messages
/// throw std::runtime_error(Formatter() << foo << 13 << ", bar" << myData);   // implicitly cast to std::string
///throw std::runtime_error(Formatter() << foo << 13 << ", bar" << myData >> Formatter::to_str);    // explicitly cast to std::string


class Formatter
{
public:
    Formatter() {}
    ~Formatter() {}

    template <typename Type>
    Formatter & operator << (const Type & value)
    {
        stream_ << value;
        return *this;
    }

    std::string str() const         { return stream_.str(); }
    operator std::string () const   { return stream_.str(); }

    enum ConvertToString
    {
        to_str
    };
    std::string operator >> (ConvertToString) { return stream_.str(); }

private:
    std::stringstream stream_;

    Formatter(const Formatter &);
    Formatter & operator = (Formatter &);
};

