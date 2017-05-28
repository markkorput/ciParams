#include "ParameterGroupBaseJsonDeserializer.h"

using namespace params;

bool ParameterGroupBaseJsonDeserializer::deserialize(const std::string& jsonText){
    ci::JsonTree jsonTree(jsonText);
    return deserialize(jsonTree);
}

bool ParameterGroupBaseJsonDeserializer::deserialize(ci::JsonTree& jsonTree){
    bool allGood = true;

    for(auto itemRef : rootGroup->getItems()){
        if(itemRef->param){
            if(jsonTree.hasChild(itemRef->param->getName())){
                allGood &= itemRef->param->deserialize(jsonTree.getValueForKey(itemRef->param->getName()));
            }
        }
        
        if(itemRef->group){
            if(jsonTree.hasChild(itemRef->group->getName())){
                allGood &= ParameterGroupBaseJsonDeserializer(*itemRef->group)
                    .deserialize( jsonTree.getChild(itemRef->group->getName()) );
            }
        }
    }

    return allGood;
}
