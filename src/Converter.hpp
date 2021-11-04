#pragma once
#include <sstream>

class Converter {
public:
    Converter() = delete;

    template <typename T>
    static std::string toString(T value)
    {
        std::ostringstream o;

        o << value;

        return o.str();
    }

    template<typename T>
    static T fromString(const std::string& s)
    {
        T result;
        std::istringstream i(s);

        i >> result;

        return result;
    }
};

