#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "cinder/Log.h"
#include "ciParams.h"

using namespace std;
using namespace params;


TEST_CASE("params::ParameterInterface", "")
{
    SECTION("get and set"){
        string p1 = "value1";
        ParameterInterface<string> pi(p1);
        REQUIRE(pi.getVar() == &p1);
        REQUIRE(pi.get() == "value1");

        string p2 = "value_2";
        pi.setVar(p2);
        REQUIRE(pi.getVar() == &p2);
        REQUIRE(pi.get() == "value_2");

        pi.set("value#3");
        REQUIRE(pi.get() == "value#3");
        REQUIRE(p2 == "value#3");
    }

    SECTION("change callback"){
        float p1 = 100.0, p2 = 0.0f;
        ParameterInterface<float> pi(p1);
        pi.onChange.connect([&p2](const float& value){
            p2 = value*2.0f;
        });

        pi.set(20.0f);
        REQUIRE(p2 == 40.0f);
    }
}

TEST_CASE("params::Parameter", ""){
    SECTION("transform"){
        Parameter<float> param;
        float var;

        param.set(5.5f);

        param.transform([&var](const float& val){
            var = val * 2.0f;
        });

        // already called by transform
        REQUIRE(var == 11.0f);

        // registers active change listener
        param.set(1.2f);
        REQUIRE(var == 2.4f);
    }

    SECTION("serialize"){
        {
            class CustomClass {};
            Parameter<CustomClass> param;
            REQUIRE(param.canSerialize() == false);
        }
        {
            Parameter<float> param;
            param.set(6.6f);
            REQUIRE(param.canSerialize());
            REQUIRE(param.serialize() == "6.600000");
        }
        {
            Parameter<double> param;
            param.set(0.0001);
            REQUIRE(param.canSerialize());
            REQUIRE(param.serialize() == "0.000100");
        }
        {
            Parameter<int> param;
            param.set(3);
            REQUIRE(param.canSerialize());
            REQUIRE(param.serialize() == "3");
        }
        {
            Parameter<long> param;
            param.set(300045);
            REQUIRE(param.canSerialize());
            REQUIRE(param.serialize() == "300045");
        }
        {
            Parameter<string> param;
            param.set("check");
            REQUIRE(param.canSerialize());
            REQUIRE(param.serialize() == "check");
        }
        {
            Parameter<bool> param;
            param.set(true);
            REQUIRE(param.canSerialize());
            REQUIRE(param.serialize() == "1");
            param.set(false);
            REQUIRE(param.serialize() == "0");
        }
        {
            Parameter<ci::vec3> param;
            param.set(ci::vec3(1.0,2.0,3.0));
            REQUIRE(param.canSerialize());
            REQUIRE(param.serialize() == "1.000000,2.000000,3.000000");
        }
        {
            Parameter<ci::Color> param;
            param.set(ci::Color(1.0,2.0,3.0));
            REQUIRE(param.canSerialize());
            REQUIRE(param.serialize() == "1.000000,2.000000,3.000000");
        }
    }
}

TEST_CASE("params::ParameterGroup", ""){
    SECTION("toJson"){
        ParameterGroup paramGroup, subGroup;
        Parameter<float> floatP1, floatP2;
        Parameter<string> stringP1, stringP2;
        Parameter<ci::vec3> vec3P1;

        paramGroup.add(floatP1.init("num1", 1.0f));
        paramGroup.add(subGroup.init("groupo1"));
        paramGroup.add(stringP1.init("s1", "empty"));
        paramGroup.add(vec3P1.init("pos", ci::vec3(11.0f,22.0f,33.0f)));
        subGroup.add(stringP2.init("s2", "empty#2"));
        subGroup.add(floatP2.init("num2", 10.0f));
        REQUIRE(paramGroup.toJson() == "{\n\
   \"groupo1\" : {\n\
      \"num2\" : \"10.000000\",\n\
      \"s2\" : \"empty#2\"\n\
   },\n\
   \"num1\" : \"1.000000\",\n\
   \"pos\" : \"11.000000,22.000000,33.000000\",\n\
   \"s1\" : \"empty\"\n\
}\n");
        paramGroup.setName("RootGroup");
        REQUIRE(paramGroup.toJson() == "{\n\
   \"RootGroup\" : {\n\
      \"groupo1\" : {\n\
         \"num2\" : \"10.000000\",\n\
         \"s2\" : \"empty#2\"\n\
      },\n\
      \"num1\" : \"1.000000\",\n\
      \"pos\" : \"11.000000,22.000000,33.000000\",\n\
      \"s1\" : \"empty\"\n\
   }\n\
}\n");
    }

    SECTION("loadJson"){
        ParameterGroup paramGroup, subGroup;
        Parameter<float> floatP1, floatP2;
        Parameter<string> stringP1, stringP2;
        Parameter<ci::vec3> vec3P1;

        paramGroup.add(floatP1.init("num1", 0.0f));
        paramGroup.add(subGroup.init("groupo1"));
        paramGroup.add(stringP1.init("s1", ""));
        paramGroup.add(vec3P1.init("pos", ci::vec3(0.0f)));
        subGroup.add(stringP2.init("s2", ""));
        subGroup.add(floatP2.init("num2", 0.0f));

        std::string json = "{\n\
   \"groupo1\" : {\n\
      \"num2\" : \"10.000000\",\n\
      \"s2\" : \"empty#2\"\n\
   },\n\
   \"num1\" : \"1.000000\",\n\
   \"pos\" : \"11.000000,22.000000,33.000000\",\n\
   \"s1\" : \"empty\"\n\
}\n";
        REQUIRE(paramGroup.loadJson(json));
        REQUIRE(floatP1.get() == 1.0f);
        REQUIRE(floatP2.get() == 10.0f);
        REQUIRE(stringP1.get() == "empty");
        REQUIRE(stringP2.get() == "empty#2");
        REQUIRE(vec3P1.get() == ci::vec3(11.0f,22.0f,33.0f));
    }

    SECTION("loadJson"){
        ParameterGroup paramGroup, subGroup;
        Parameter<float> floatP1, floatP2;
        Parameter<string> stringP1, stringP2;
        Parameter<ci::vec3> vec3P1;

        paramGroup.add(floatP1.init("num1", 0.0f));
        paramGroup.add(subGroup.init("groupo1"));
        paramGroup.add(stringP1.init("s1", ""));
        paramGroup.add(vec3P1.init("pos", ci::vec3(0.0f)));
        subGroup.add(stringP2.init("s2", ""));
        subGroup.add(floatP2.init("num2", 0.0f));

        CI_LOG_I("getAssetPath: " << ci::app::getAssetPath("params.json"));
        REQUIRE(paramGroup.loadJson(ci::app::loadAsset("params.json")));
        REQUIRE(floatP1.get() == 1.0f);
        REQUIRE(floatP2.get() == 10.0f);
        REQUIRE(stringP1.get() == "empty");
        REQUIRE(stringP2.get() == "empty#2");
        REQUIRE(vec3P1.get() == ci::vec3(11.0f,22.0f,33.0f));
        
        paramGroup.setName("RootGroup");
        REQUIRE(paramGroup.loadJson(ci::app::loadAsset("params2.json")));
        REQUIRE(floatP1.get() == 5.0f);
        REQUIRE(floatP2.get() == 22.0f);
        REQUIRE(stringP1.get() == "empty_");
        REQUIRE(stringP2.get() == "empty##2");
        REQUIRE(vec3P1.get() == ci::vec3(22.0f,44.0f,66.0f));
    }
}
