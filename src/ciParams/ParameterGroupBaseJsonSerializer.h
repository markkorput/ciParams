
#include "cinder/Json.h"
#include "ParameterGroupBase.h"

namespace params {
    class ParameterGroupBaseJsonSerializer {
    public:
        ParameterGroupBaseJsonSerializer(ParameterGroupBase& paramGroup) : rootGroup(&paramGroup){}
        
        ci::JsonTree getJsonTree();
        std::string getJson();
        
    private:
        ParameterGroupBase* rootGroup;
    };
}
