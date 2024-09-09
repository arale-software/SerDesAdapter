#ifndef __PROTO_PACKET_HPP_SEBTX71MFBHS__
#define __PROTO_PACKET_HPP_SEBTX71MFBHS__

// TODO dynamic index changing
// TODO resize
// TODO base class
#include <ankerl/unordered_dense.h>
#include <tsl/array_map.h>

class protoPacketNodeBase;
// using protoPacketNodesMap = ankerl::unordered_dense::map<std::string, protoPacketNodeBase, ankerl::unordered_dense::hash<std::string>>;
// using protoPacketNodesMap = ankerl::unordered_dense::map<std::string, protoPacketNodeBase>;
// using protoPacketNodesMap = std::unordered_map<std::string, protoPacketNodeBase>;

#include <libProtoPacket/details/TProtoPacketNode.hpp>

using TProtoPacketNodesMap = tsl::array_map<char, TProtoPacketNode&>;
///////////////////////////////////////////////////////////
/// @brief ProtoPacket
///
class ProtoPacket {
 public:
  //   ProtoPacket() = default;
  virtual ~ProtoPacket() = default;
  ProtoPacket(const ProtoPacket& other) = default;
  ProtoPacket(ProtoPacket&& other) = default;
  ProtoPacket& operator=(const ProtoPacket& other) = default;
  ProtoPacket& operator=(ProtoPacket&& other) = default;

  TProtoPacketNode m_KeyName1{TProtoPacketNodeType::CRC8T1, 1, nullptr, TProtoPacketNodeBytesOrder::littleEndian, &m_pKey2, &m_pKey3, (uint8_t)0xFF, (uint8_t)0xAB};
  TProtoPacketNode m_KeyName2{TProtoPacketNodeType::double64};
  TProtoPacketNode m_KeyName3{TProtoPacketNodeType::i16};
  TProtoPacketNode m_KeyName4{TProtoPacketNodeType::stringUTF8};
  TProtoPacketNode m_KeyName5{TProtoPacketNodeType::ui32};

  // clang-format off
   TProtoPacketNodesMap m_keyMap{
        {"KeyName1",  m_KeyName1}, 
        {"KeyName2",  m_KeyName2}, 
        {"KeyName3",  m_KeyName3}, 
        {"KeyName4",  m_KeyName4}, 
        {"KeyName5",  m_KeyName5}
        };
  // clang-format on

  ProtoPacket(/* args */) {}

  void init(void* data) {
    for (auto& node : m_keyMap) {
      node.init(data);
    }
  }

 private:
  // Members
};

#endif  // __PROTO_PACKET_HPP_SEBTX71MFBHS__
