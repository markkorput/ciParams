#pragma once

#include <memory>
#include <functional>
#include "cinder/Signals.h"
#include "ParameterBase.h"

namespace params {
    template<class T>
    class Parameter : public ParameterBase<T> {
    public:

        typedef std::function<void(const T&)> TransformFunc;

    public:

        ci::signals::Connection transform(TransformFunc func, bool active=true){
            func(this->get());
            auto connection = this->onChange.connect(func);

            if(!active)
                connection.disconnect();

            return connection;
        }

        bool canSerialize(){ return false; }
        std::string serialize(){ return ""; }
    };
}

// some serializers for common types

template<>
bool params::Parameter<float>::canSerialize(){ return true; }

template<>
std::string params::Parameter<float>::serialize(){
    return std::to_string(this->get());
}

template<>
bool params::Parameter<double>::canSerialize(){ return true; }

template<>
std::string params::Parameter<double>::serialize(){
    return std::to_string(this->get());
}

template<>
bool params::Parameter<int>::canSerialize(){ return true; }

template<>
std::string params::Parameter<int>::serialize(){
    return std::to_string(this->get());
}

template<>
bool params::Parameter<long>::canSerialize(){ return true; }

template<>
std::string params::Parameter<long>::serialize(){
    return std::to_string(this->get());
}

template<>
bool params::Parameter<std::string>::canSerialize(){ return true; }

template<>
std::string params::Parameter<std::string>::serialize(){
    return this->get();
}

template<>
bool params::Parameter<bool>::canSerialize(){ return true; }

template<>
std::string params::Parameter<bool>::serialize(){
    return std::to_string(this->get());
}
