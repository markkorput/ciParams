#pragma once

#include "cinder/DataSource.h"
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

        bool loadJson(std::string jsonText){
            return ParameterGroupBaseJsonDeserializer(*this).deserialize(jsonText);
        }

        bool loadJson(ci::DataSourceRef dataSourceRef){
            CI_LOG_I("loadJson from: " << dataSourceRef->getFilePath());
            string s( static_cast<const char*>( dataSourceRef->getBuffer()->getData() ));
            if(s.length() > dataSourceRef->getBuffer()->getSize()){
                s.resize( dataSourceRef->getBuffer()->getSize() );
            }
            CI_LOG_I("json from file: " + s);
            return loadJson(s);
        }
    };
}
