#include "cinder/Json.h"
#include "ParameterGroupBase.h"

namespace params {
    class ParameterGroupBaseJsonDeserializer {
    public:
        ParameterGroupBaseJsonDeserializer(ParameterGroupBase& paramGroup, const string& json = "") : rootGroup(&paramGroup){}
        bool deserialize(const std::string& jsonText);
        bool deserialize(ci::JsonTree& jsonTree);
        
        
    private:
        ParameterGroupBase* rootGroup;
    };
}
