#include "cinder/Json.h"
#include "ParameterGroupBase.h"

namespace params {
    class ParameterGroupBaseJsonSerializer {
    public:
        ParameterGroupBaseJsonSerializer(const ParameterGroupBase& paramGroup) : rootGroup(&paramGroup){}

        ci::JsonTree getJsonTree() const;
        std::string getJson() const;

    private:
        const ParameterGroupBase* rootGroup;
    };
}
