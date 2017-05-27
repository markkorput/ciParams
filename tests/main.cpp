#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "ciParams.h"

using namespace ci;
using namespace params;
//using namespace std;

TEST_CASE("params::ParameterInterface", "")
{
    SECTION("get and set")
    {
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
}
