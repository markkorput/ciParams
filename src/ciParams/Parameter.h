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
    };
}
