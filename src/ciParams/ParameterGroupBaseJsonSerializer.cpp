#include "ParameterGroupBaseJsonSerializer.h"

using namespace params;

ci::JsonTree ParameterGroupBaseJsonSerializer::getJsonTree(){
    ci::JsonTree rootTree;
    ci::JsonTree nestTree;
    ci::JsonTree *childTreeContainer;

    if(rootGroup->getName() == ""){
        childTreeContainer = &rootTree;
    } else {
        // CI_LOG_I("rootGroup->getName(): " << rootGroup->getName());
        rootTree = ci::JsonTree::makeObject(rootGroup->getName());
        // rootTree.addChild(nestTree);
        childTreeContainer = &rootTree;
    }

    for(auto itemRef : rootGroup->getItems()){
        if(itemRef->param){
            if(itemRef->param->canSerialize()){
                ci::JsonTree paramTree(
                                       itemRef->param->getName(),
                                       itemRef->param->serialize());
                childTreeContainer->addChild(paramTree);
            }
        }

        if(itemRef->group){
            childTreeContainer->addChild(ParameterGroupBaseJsonSerializer(*itemRef->group).getJsonTree());
        }
    }

    return rootTree;
}

std::string ParameterGroupBaseJsonSerializer::getJson(){
    if(rootGroup->getName() == "")
        return getJsonTree().serialize();
    ci::JsonTree rootTree = ci::JsonTree::makeObject(rootGroup->getName());
    rootTree.addChild(getJsonTree());
    return rootTree.serialize();
}
