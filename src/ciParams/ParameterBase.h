#pragma once

#include "ParameterInterface.h"

namespace params {
    class ParameterBase {
    public:
        const std::string& getName() const { return name; }
        void setName(const std::string& newName){ name = newName; }

        virtual bool canSerialize() const { return false; }
        virtual std::string serialize() const { return ""; }
        virtual bool deserialize(const std::string& value){ return false; }

    private:
        std::string name;
    };
}
