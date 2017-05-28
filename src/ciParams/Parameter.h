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

        Parameter<T>& init(const std::string& name, const T& newValue){
            this->setName(name);
            this->set(newValue);
            return *this;
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

        virtual bool canSerialize() const;
        virtual std::string serialize() const;
        virtual bool deserialize(const std::string& value);

    private:
        T myVar;
    };
}

// some serializers for common types
template<class ParamType>
bool params::Parameter<ParamType>::canSerialize() const { return false; }

template<class ParamType>
std::string params::Parameter<ParamType>::serialize() const { return ""; }

template<class ParamType>
bool params::Parameter<ParamType>::deserialize(const std::string& value){ return false; }


template<>
bool params::Parameter<float>::canSerialize() const { return true; }

template<>
std::string params::Parameter<float>::serialize() const {
    return std::to_string(this->get());
}

template<>
bool params::Parameter<double>::canSerialize() const { return true; }

template<>
std::string params::Parameter<double>::serialize() const {
    return std::to_string(this->get());
}

template<>
bool params::Parameter<int>::canSerialize() const { return true; }

template<>
std::string params::Parameter<int>::serialize() const {
    return std::to_string(this->get());
}

template<>
bool params::Parameter<long>::canSerialize() const { return true; }

template<>
std::string params::Parameter<long>::serialize() const {
    return std::to_string(this->get());
}

template<>
bool params::Parameter<std::string>::canSerialize() const { return true; }

template<>
std::string params::Parameter<std::string>::serialize() const {
    return this->get();
}

template<>
bool params::Parameter<bool>::canSerialize() const { return true; }

template<>
std::string params::Parameter<bool>::serialize() const {
    return std::to_string(this->get());
}

template<>
bool params::Parameter<ci::vec3>::canSerialize() const { return true; }

template<>
std::string params::Parameter<ci::vec3>::serialize() const {
    ci::vec3 val=this->get();
    return std::to_string(val.x) + "," + std::to_string(val.y) + "," + std::to_string(val.z);
}

template<>
bool params::Parameter<ci::Color>::canSerialize() const { return true; }

template<>
std::string params::Parameter<ci::Color>::serialize() const {
    ci::Color val=this->get();
    return std::to_string(val.r) + "," + std::to_string(val.g) + "," + std::to_string(val.b);
}
