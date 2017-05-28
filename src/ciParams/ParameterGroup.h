#pragma once

#include "cinder/Log.h"
#include <stdio.h>

#include "ParameterGroupBase.h"
#include "ParameterBase.h"
#include "ParameterGroupBaseJsonDeserializer.h"
#include "ParameterGroupBaseJsonSerializer.h"

namespace params {

    class ParameterGroup : public ParameterGroupBase {
    public:
        string toJson(){
            return ParameterGroupBaseJsonSerializer(*this).getJson();
        }

        bool fromJson(std::string jsonText){
            return ParameterGroupBaseJsonDeserializer(*this).deserialize(jsonText);
        }
    };
}
