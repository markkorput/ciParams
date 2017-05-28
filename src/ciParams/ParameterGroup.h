#pragma once

#include "cinder/Json.h"
#include "cinder/Log.h"
#include <stdio.h>

#include "ParameterGroupBase.h"
#include "ParameterBase.h"

namespace params {

    class ParameterGroupJson {
    public:
        ParameterGroupJson(const ParameterGroupBase& paramGroup) : rootGroup(&paramGroup){}

        ci::JsonTree getJsonTree() const {
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
                    childTreeContainer->addChild(ParameterGroupJson(*itemRef->group).getJsonTree());
                }
            }
            
            return rootTree;
        }

        string getJson() const {
            if(rootGroup->getName() == "")
                return getJsonTree().serialize();
            ci::JsonTree rootTree = ci::JsonTree::makeObject(rootGroup->getName());
            rootTree.addChild(getJsonTree());
            return rootTree.serialize();
        }
        
    private:
        const ParameterGroupBase* rootGroup;
    };

    class ParameterGroup : public ParameterGroupBase {
    public:
        string toJson() const {
            return ParameterGroupJson(*this).getJson();
        }

    private:
        // std::vector<shared_ptr<ParamType>> parameterRefs;
    };
}
