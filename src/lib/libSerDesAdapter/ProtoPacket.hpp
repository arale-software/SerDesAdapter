#ifndef __PROTO_PACKET_HPP_SEBTX71MFBHS__
#define __PROTO_PACKET_HPP_SEBTX71MFBHS__

#include <tsl/array_map.h>

#include <libSerDesAdapter/details/TBaseNode.hpp>
#include <libSerDesAdapter/details/TCRC8T1Node.hpp>
#include <libSerDesAdapter/details/TScalarNode.hpp>

using protoPacketNodesMap = tsl::array_map<char, TBaseNode*>;

///////////////////////////////////////////////////////////
/// @brief ProtoPacket
/// USE INIT FUNCTION TO INITIALIZE ADAPTER POINTERS
/// ADAPTER DOESN'T CONTROL POINTER VALIDITY AND SIZE OF DATA TYPES

class ProtoPacket {
 public:
  ProtoPacket() = default;
  virtual ~ProtoPacket() = default;
  ProtoPacket(const ProtoPacket& other) = default;
  ProtoPacket(ProtoPacket&& other) = default;
  ProtoPacket& operator=(const ProtoPacket& other) = default;
  ProtoPacket& operator=(ProtoPacket&& other) = default;

  // rules to gen ctor
  // rules to gen varNames
  TScalarNode<int32_t> m_keyInt1{true, 1};
  TScalarNode<float> m_keyFloat1{true, 1};
  TCRC8T1Node m_keyCRC8T1{0xFF, 0x00, true};

  // clang-format off
   protoPacketNodesMap m_nodesHashTable {
        {"KEY1_I32",      &m_keyInt1}, 
        {"KEY2_F",        &m_keyFloat1}, 
        {"KEY3_CRC8T1",   &m_keyCRC8T1}
        };
  // clang-format on

  // rules to gen init args
  void init(void* pInit) {
    size_t pos = 0;
    pos += m_keyInt1.init(reinterpret_cast<uint8_t*>(pInit) + pos);
    pos += m_keyFloat1.init(reinterpret_cast<uint8_t*>(pInit) + pos);
    pos += m_keyCRC8T1.init(reinterpret_cast<uint8_t*>(pInit) + pos, &m_keyInt1, &m_keyFloat1);
  }
};

#endif  // __PROTO_PACKET_HPP_SEBTX71MFBHS__
