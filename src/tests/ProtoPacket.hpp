#ifndef __PROTO_PACKET_HPP_SEBTX71MFBHS__
#define __PROTO_PACKET_HPP_SEBTX71MFBHS__

// TODO dynamic index changing
// TODO resize
// TODO base class
#include <ankerl/unordered_dense.h>
#include <tsl/array_map.h>

#include <typeindex>
#include <unordered_map>
#include <variant>

class protoPacketNodeBase;
// using protoPacketNodesMap = ankerl::unordered_dense::map<std::string, protoPacketNodeBase, ankerl::unordered_dense::hash<std::string>>;
// using protoPacketNodesMap = ankerl::unordered_dense::map<std::string, protoPacketNodeBase>;
// using protoPacketNodesMap = std::unordered_map<std::string, protoPacketNodeBase>;
using protoPacketNodesMap = tsl::array_map<char, protoPacketNodeBase>;

// std::variant + 100 ns
// std::type_index + 200 ns

class protoPacketNodeB {
 public:
  uint8_t m_typeIndex{0};
  void* m_pData;
};

class protoPacketNodeB {
 public:
  uint8_t m_typeIndex{0};
  void* m_pData;
  template <typename T>
  T& get() {
    return *reinterpret_cast<T*>(m_pData);
  }

  template <typename T>
  void set(const T&) {
    return *reinterpret_cast<T*>(m_pData);
  }
};

class protoPacketNodeBase {
 protected:
  uint8_t m_typeIndex{0};
  void** m_ppData;

 public:
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wfloat-conversion"
  template <typename T>
  void getValue(T& value) {
    switch (m_typeIndex) {
      case 1:
        value = **reinterpret_cast<uint8_t**>(m_ppData);
        break;
      case 2:
        value = **reinterpret_cast<uint16_t**>(m_ppData);
        break;
      case 3:
        value = **reinterpret_cast<float**>(m_ppData);
        break;
      case 4:
        value = **reinterpret_cast<double**>(m_ppData);
        break;
      default:
        break;
    }
  };
#pragma GCC diagnostic pop

  template <typename T>
  protoPacketNodeBase(T** other) {
    m_ppData = (void**)other;
    if constexpr (std::is_same_v<T, uint8_t>) {
      m_typeIndex = 1;
    }
    if constexpr (std::is_same_v<T, uint16_t>) {
      m_typeIndex = 2;
    }
    if constexpr (std::is_same_v<T, double>) {
      m_typeIndex = 3;
    }
    if constexpr (std::is_same_v<T, float>) {
      m_typeIndex = 4;
    }
  }

  template <typename T>
  protoPacketNodeBase& operator=(const T& value) {
    if (m_typeIndex == 1) {
      **reinterpret_cast<uint8_t**>(m_ppData) = value;
    }
    return *this;
  }

  template <typename T>
  inline bool operator==(const T& value) const noexcept {
    if (m_typeIndex == 1) {
      return **reinterpret_cast<uint8_t**>(m_ppData) == value;
    }
  }
};

// class protoPacketNodeBase {
//  protected:
//   uint8_t m_typeIndex{0};
//   std::variant<uint8_t**, uint16_t**, float**, double**> m_ppData;

//  public:
// #pragma GCC diagnostic push
// #pragma GCC diagnostic ignored "-Wconversion"
// #pragma GCC diagnostic ignored "-Wfloat-conversion"
//   template <typename T>
//   void getValue(T& value) {
//     switch (m_typeIndex) {
//       case 1:
//         value = **std::get<uint8_t**>(m_ppData);
//         break;
//       case 2:
//         value = **std::get<uint16_t**>(m_ppData);
//         break;
//       case 3:
//         value = **std::get<float**>(m_ppData);
//         break;
//       case 5:
//         value = **std::get<double**>(m_ppData);
//         break;
//       default:
//         break;
//     }
//   };
// #pragma GCC diagnostic pop

//   template <typename T>
//   protoPacketNodeBase(T** other) {
//     m_ppData = other;
//     if constexpr (std::is_same_v<T, uint8_t>) {
//       m_typeIndex = 1;
//     }
//     if constexpr (std::is_same_v<T, uint16_t>) {
//       m_typeIndex = 2;
//     }
//     if constexpr (std::is_same_v<T, float>) {
//       m_typeIndex = 3;
//     }
//     if constexpr (std::is_same_v<T, double>) {
//       m_typeIndex = 4;
//     }
//   }
// };

///////////////////////////////////////////////////////////
/// @brief ProtoPacket
///
class ProtoPacket : public std::vector<uint8_t> {
 public:
  //   ProtoPacket() = default;
  virtual ~ProtoPacket() = default;
  ProtoPacket(const ProtoPacket& other) = default;
  ProtoPacket(ProtoPacket&& other) = default;
  ProtoPacket& operator=(const ProtoPacket& other) = default;
  ProtoPacket& operator=(ProtoPacket&& other) = default;

  enum class ProtoPacketIndex : std::vector<uint8_t>::size_type {
    key1 = 0,
    key2 = key1 + sizeof(uint8_t),
    key3 = key2 + sizeof(uint16_t),
    key4 = key3 + sizeof(double),
    key5 = key4 + sizeof(float),
  };

  uint8_t* m_pKey1{nullptr};
  uint16_t* m_pKey2{nullptr};
  double* m_pKey3{nullptr};
  float* m_pKey4{nullptr};
  uint8_t* m_pKey5{nullptr};

  uint8_t& getKey1() { return *m_pKey1; }
  uint16_t& getKey2() { return *m_pKey2; }
  double& getKey3() { return *m_pKey3; }
  float& getKey4() { return *m_pKey4; }
  uint8_t& getKey5() { return *m_pKey5; }

  protoPacketNodeB m_pKEY1;
  protoPacketNodeB m_pKEY2;
  protoPacketNodeB m_pKEY3;
  protoPacketNodeB m_pKEY4;
  protoPacketNodeB m_pKEY5;

  protoPacketNodeBase m_ppKey1{&m_pKey1};
  protoPacketNodeBase m_ppKey2{&m_pKey2};
  protoPacketNodeBase m_ppKey3{&m_pKey3};
  protoPacketNodeBase m_ppKey4{&m_pKey4};
  protoPacketNodeBase m_ppKey5{&m_pKey5};

  // clang-format off
   protoPacketNodesMap m_ptrs{
        {"KEY1_U8",  &m_pKey1}, 
        {"KEY2_X16", &m_pKey2}, 
        {"KEY3_D",   &m_pKey3}, 
        {"KEY4_F",   &m_pKey4}, 
        {"KEY5_U8",  &m_pKey5}
        };
  // clang-format on

  ProtoPacket(/* args */) { init(); }

  void init(/* args */) {
    m_pKEY1.m_pData = begin().base();
    m_pKEY2.m_pData = (begin() + sizeof(uint8_t)).base();
    m_pKEY3.m_pData = (begin() + sizeof(uint16_t)).base();
    m_pKEY4.m_pData = (begin() + sizeof(double)).base();
    m_pKEY5.m_pData = (begin() + sizeof(float)).base();

    m_pKey1 = reinterpret_cast<decltype(m_pKey1)>(&data()[static_cast<std::vector<uint8_t>::size_type>(ProtoPacketIndex::key1)]);
    m_pKey2 = reinterpret_cast<decltype(m_pKey2)>(&data()[static_cast<std::vector<uint8_t>::size_type>(ProtoPacketIndex::key2)]);
    m_pKey3 = reinterpret_cast<decltype(m_pKey3)>(&data()[static_cast<std::vector<uint8_t>::size_type>(ProtoPacketIndex::key3)]);
    m_pKey4 = reinterpret_cast<decltype(m_pKey4)>(&data()[static_cast<std::vector<uint8_t>::size_type>(ProtoPacketIndex::key4)]);
    m_pKey5 = reinterpret_cast<decltype(m_pKey5)>(&data()[static_cast<std::vector<uint8_t>::size_type>(ProtoPacketIndex::key5)]);
  }

 private:
  // Members
};

#endif  // __PROTO_PACKET_HPP_SEBTX71MFBHS__
