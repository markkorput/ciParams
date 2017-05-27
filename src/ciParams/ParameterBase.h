#pragma once

#include "ParameterInterface.h"

namespace params {
    template<class T>
    class ParameterBase : public ParameterInterface<T> {
    public:
        ParameterBase(){
            this->setVar(myVar);
        }

    private:
        T myVar;
    };
}
