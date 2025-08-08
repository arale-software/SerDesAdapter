#include <catch2/catch_all.hpp>
#include <details/TBaseNode.hpp>
#include <details/TBaseSerDesAdapter.hpp>
#include <details/TCRC8T1Node.hpp>
#include <details/TScalarNode.hpp>

class TGenericSerDesAdapter : public TBaseSerDesAdapter {
 public:
  TGenericSerDesAdapter() = default;
  virtual ~TGenericSerDesAdapter() = default;
  TGenericSerDesAdapter(const TGenericSerDesAdapter& other) = default;
  TGenericSerDesAdapter(TGenericSerDesAdapter&& other) = default;
  TGenericSerDesAdapter& operator=(const TGenericSerDesAdapter& other) = default;
  TGenericSerDesAdapter& operator=(TGenericSerDesAdapter&& other) = default;

  TScalarNode<uint8_t> m_field1_u8{TBaseNode::EBytesOrder::littleEndian, 1};
  TScalarNode<uint8_t> m_field2_u8{TBaseNode::EBytesOrder::littleEndian, 1};
  TScalarNode<float> m_field3_float{TBaseNode::EBytesOrder::littleEndian, 1};
  TCRC8T1Node m_field4_crc8{0xff, 0xab, TBaseNode::EBytesOrder::littleEndian};

  virtual void init(void* pInit) override {
    size_t pos = 0;
    pos += m_field1_u8.init(reinterpret_cast<uint8_t*>(pInit) + pos, 11);
    pos += m_field2_u8.init(reinterpret_cast<uint8_t*>(pInit) + pos, 11);
    pos += m_field3_float.init(reinterpret_cast<uint8_t*>(pInit) + pos, 33.33);
    pos += m_field4_crc8.init(reinterpret_cast<uint8_t*>(pInit) + pos, &m_field1_u8, &m_field3_float);
  }

  virtual void update() override { m_field4_crc8.update(); }

  TBaseNodePtrMap m_nodesHashTable{
      {"field1_u8", &m_field1_u8},        //
      {"field2_u8", &m_field2_u8},        //
      {"field3_float", &m_field3_float},  //
      {"field4_crc8", &m_field4_crc8}     //
  };

  virtual TBaseNodePtrMap& getNodeMap() override { return m_nodesHashTable; }

  virtual void reinit(void* pInit) override {
    for (auto&& node : m_nodesHashTable) {
      node->reinit(pInit);
    }
  }
};

TEST_CASE("Generic class basic tests") {
  GIVEN("Random array as raw data and Generic class object") {
    [[maybe_unused]] TGenericSerDesAdapter genericObject{};
    [[maybe_unused]] std::array<uint8_t, 32> initArray{};
    AND_GIVEN("Some scalar values same types of generic class fields") {
      [[maybe_unused]] uint8_t controlValue1_u8{0};
      [[maybe_unused]] uint8_t controlValue2_u8{0};
      [[maybe_unused]] float controlValue3_f{0};
      [[maybe_unused]] uint8_t controlValue4_crc8{0};
      [[maybe_unused]] std::array<uint8_t, 32> controlArray{0xB, 0xB, 0xEC, 0x51, 0x5, 0x42, 0xD6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
                                                            0x0, 0x0, 0x0,  0x0,  0x0, 0x0,  0x0,  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
      WHEN("Init method has been executed") {
        REQUIRE_NOTHROW(genericObject.init(initArray.data()));
        THEN("Array has been changed with init values of generic class fields") {
          REQUIRE(initArray == controlArray);
        }
        AND_WHEN("Node fields method 'read' executed") {
          REQUIRE_NOTHROW(genericObject.m_field1_u8.readUnsignedInt8(controlValue1_u8));
          REQUIRE_NOTHROW(genericObject.m_field2_u8.readUnsignedInt8(controlValue2_u8));
          REQUIRE_NOTHROW(genericObject.m_field3_float.readFloat(controlValue3_f));
          REQUIRE_NOTHROW(genericObject.m_field4_crc8.readUnsignedInt8(controlValue4_crc8));
          THEN("Control values are same with init values") {
            REQUIRE(controlValue1_u8 == 11);
            REQUIRE(controlValue2_u8 == 11);
            REQUIRE(std::abs(controlValue3_f - 33.33f) < 0.01);
            REQUIRE(controlValue4_crc8 == 0xD6);
          }
        }
      }
    }
  }
}
