#define CATCH_CONFIG_MAIN
#include "catch.hpp"

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

TEST_CASE("params::ParameterBase", ""){
    SECTION("has embedded variable instance"){
        ParameterBase<int> intParam;
        int dummy;

        intParam.onChange.connect([&dummy](const int& val){
            dummy = val*2;
        });

        intParam.set(6);
        REQUIRE(dummy == 12);
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
