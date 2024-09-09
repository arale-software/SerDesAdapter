#ifndef __TProtoPacketGNMOLK__
#define __TProtoPacketGNMOLK__

#include <tsl/array_map.h>

#include <TProtoPacket/details/TBaseNode.hpp>
#include <TProtoPacket/details/TScalarNode.hpp
#include <TProtoPacket/details/CRC8T1Node.hpp

///////////////////////////////////////////////////////////
/// @brief TProtoPacket
/// USE INIT FUNCTION TO INITIALIZE ADAPTER POINTERS
/// ADAPTER DOESN'T CONTROL POINTER VALIDITY AND SIZE OF DATA TYPES

class TProtoPacket {
 public:
  TProtoPacket() = default;
  virtual ~TProtoPacket() = default;
  TProtoPacket(const TProtoPacket& other) = default;
  TProtoPacket(TProtoPacket&& other) = default;
  TProtoPacket& operator=(const TProtoPacket& other) = default;
  TProtoPacket& operator=(TProtoPacket&& other) = default;

  TScalarNode<uint8_t> m_KeyName1{TBaseNode::EBytesOrder::littleEndian, 1};
	TScalarNode<float> m_KeyName2{TBaseNode::EBytesOrder::littleEndian, 16};
	TCRC8T1Node m_KeyName3{0xff, 0xab, TBaseNode::EBytesOrder::littleEndian};

  void init(void* pInit) {
    size_t pos = 0;
    pos += m_KeyName1.init(reinterpret_cast<uint8_t*>(pInit) + pos);
		pos += m_KeyName2.init(reinterpret_cast<uint8_t*>(pInit) + pos);
		pos += m_KeyName3.init(reinterpret_cast<uint8_t*>(pInit) + pos, &m_KeyName1, &m_KeyName2);
  }
  
   tsl::array_map<char, TBaseNode*> m_nodesHashTable {
    {"KeyName1",		&m_KeyName1},
		{"KeyName2",		&m_KeyName2},
		{"KeyName3",		&m_KeyName3}
  };
};

#endif // __TProtoPacketGNMOLK__

