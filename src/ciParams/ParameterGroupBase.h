#pragma once

#include <memory>
#include "ParameterBase.h"

using namespace std;

namespace params {
    class ParameterGroupBase {
    private:

        typedef struct {
            ParameterBase* param;
            ParameterGroupBase* group;
        } Item;

    public:
        
        ParameterGroupBase() : name(""){
        }
        
        ParameterGroupBase& init(const std::string& newName){
            setName(newName);
            return *this;
        }
        
        const std::string& getName() const {
            return name;
        }

        void setName(const std::string& newName){
            name = newName;
        }

        void add(ParameterBase& param){
            auto itemRef = make_shared<Item>();
            itemRef->param = &param;
            itemRef->group = NULL;
            itemRefs.push_back(itemRef);
        }

        void add(ParameterGroupBase& group){
            auto itemRef = make_shared<Item>();
            itemRef->param = NULL;
            itemRef->group = &group;
            itemRefs.push_back(itemRef);
        }

        const std::vector<shared_ptr<Item>>& getItems() const {
            return itemRefs;
        }

    private:
        std::vector<shared_ptr<Item>> itemRefs;
        string name;
    };
}
