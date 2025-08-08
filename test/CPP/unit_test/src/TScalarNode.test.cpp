#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

#include <details/TScalarNode.hpp>

TEST_CASE("TScalarNode class tests") {
  GIVEN("Random array as raw data and TScalarNode<int32_t> object pointed to byte number 10") {
    std::vector<uint8_t> testRawData1;
    testRawData1.assign({1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0});
    TScalarNode<int32_t> testNode{TBaseNode::EBytesOrder::littleEndian, 1};
    testNode.init(reinterpret_cast<uint8_t*>(testRawData1.data()) + 10);
    WHEN("Writing 4 bytes to the test object") {
      testNode.writeInt32(0xC0DE'ABCD);
      THEN("10, 11, 12, 13 bytes of raw data array are changed") {
        REQUIRE(testRawData1.at(10) == 0xCD);
        REQUIRE(testRawData1.at(11) == 0xAB);
        REQUIRE(testRawData1.at(12) == 0xDE);
        REQUIRE(testRawData1.at(13) == 0xC0);
      }
    }
  }
}  // TScalarNode test
