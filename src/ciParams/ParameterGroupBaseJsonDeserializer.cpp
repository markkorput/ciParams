#include "ParameterGroupBaseJsonDeserializer.h"

using namespace params;

bool ParameterGroupBaseJsonDeserializer::deserialize(const std::string& jsonText){
    ci::JsonTree jsonTree(jsonText);
    if(rootGroup->getName() == "" || !jsonTree.hasChild(rootGroup->getName()))
        return deserialize(jsonTree);

    ci::JsonTree subTree = jsonTree[rootGroup->getName()];
    return deserialize(subTree);
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
