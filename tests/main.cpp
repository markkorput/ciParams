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
        REQUIRE(pi.getParameter() == &p1);
        REQUIRE(pi.get() == "value1");
        
        string p2 = "value_2";
        pi.setParameter(p2);
        REQUIRE(pi.getParameter() == &p2);
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
