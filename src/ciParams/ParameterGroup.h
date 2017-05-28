#pragma once

#include "cinder/Log.h"
#include <stdio.h>

#include "ParameterGroupBase.h"
#include "ParameterBase.h"
#include "ParameterGroupBaseJsonSerializer.h"

namespace params {

    class ParameterGroup : public ParameterGroupBase {
    public:
        string toJson() const {
            return ParameterGroupBaseJsonSerializer(*this).getJson();
        }
    };
}
