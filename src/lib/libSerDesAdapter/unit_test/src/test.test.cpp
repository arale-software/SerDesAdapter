#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

#include <libtest/test.hpp>

TEST_CASE("ARALE libtest unit test example") {
  GIVEN("object of library test class created") {
    test testClassObject;
    WHEN("argument variable initialized with 1") {
      int result = 1;
      AND_WHEN("and used run method run(int) with result variable") {
        testClassObject.run(result);
        THEN("argument variable expected value is 2") {
          REQUIRE(result == 2);
        }
        AND_THEN("expected something else") {
          REQUIRE(true);
        }
      }
    }

    WHEN("argument variable initialized with max size of integer") {
      int result = std::numeric_limits<int>::max();
      AND_WHEN("and used run method run(int) with result variable") {
        THEN("run method executed without without exception") {
          REQUIRE_NOTHROW(testClassObject.run(result));
          AND_THEN("argument variable expected value is minimal size of integer") {
            REQUIRE(result == std::numeric_limits<int>::min());
          }
        }
      }
    }
  }
}