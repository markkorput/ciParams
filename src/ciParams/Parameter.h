#pragma once

#include <memory>
#include <functional>
#include "cinder/Signals.h"
#include "ParameterInterface.h"
#include "ParameterBase.h"

namespace params {
    template<class T>
    class Parameter : public ParameterBase, public ParameterInterface<T> {
    public:

        typedef std::function<void(const T&)> TransformFunc;

    public:

        Parameter(){
            // use private variable instance for all ParameterInterface logic
            this->setVar(myVar);
        }

        /// Use the given function to transform the value of the parameters. The transformer
        /// is invoked for the current value as well as -if active is true- all future values
        ci::signals::Connection transform(TransformFunc func, bool active=true){
            func(this->get());
            auto connection = this->onChange.connect(func);

            if(!active)
                connection.disconnect();

            return connection;
        }
        
        virtual bool canSerialize(){ return false; }
        virtual std::string serialize(){ return ""; }
        virtual bool deserialize(const std::string& value){ return false; }

    private:
        T myVar;
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

template<>
bool params::Parameter<ci::vec3>::canSerialize(){ return true; }

template<>
std::string params::Parameter<ci::vec3>::serialize(){
    ci::vec3 val=this->get();
    return std::to_string(val.x) + "," + std::to_string(val.y) + "," + std::to_string(val.z);
}

template<>
bool params::Parameter<ci::Color>::canSerialize(){ return true; }

template<>
std::string params::Parameter<ci::Color>::serialize(){
    ci::Color val=this->get();
    return std::to_string(val.r) + "," + std::to_string(val.g) + "," + std::to_string(val.b);
}
