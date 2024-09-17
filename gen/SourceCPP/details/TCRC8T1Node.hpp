/**
 * @file TCRC8T1Node.hpp
 * @author Sokolov Alexander (a.s.sokolov@arale.ru)
 * @brief Arale SerDesAdapter simple crc8 node
 * @version 0.1
 * @date 2024-09-08
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef __T_C_R_C8_T1_NODE_HPP_9VDG0BGKUQ88__
#define __T_C_R_C8_T1_NODE_HPP_9VDG0BGKUQ88__

#include <boost/crc.hpp>

#include "TScalarNode.hpp"

///////////////////////////////////////////////////////////
/// @brief TCRC8T1Node
///
class TCRC8T1Node : public TScalarNode<uint8_t> {
 protected:
  TBaseNode* m_pBeginNode;
  TBaseNode* m_pEndNode;
  size_t m_distanceBytes;
  boost::crc_basic<8> m_crc;

 public:
  TCRC8T1Node() = delete;
  TCRC8T1Node(const uint8_t& crcpoly = 0x00, const uint8_t& crcinit = 0x00, EBytesOrder littleEndian = EBytesOrder::littleEndian)
      : TScalarNode<uint8_t>(littleEndian, 1), m_pBeginNode{nullptr}, m_pEndNode{nullptr}, m_distanceBytes{0}, m_crc{crcpoly, crcinit} {}

  virtual ~TCRC8T1Node() = default;
  TCRC8T1Node(const TCRC8T1Node& other) = default;
  TCRC8T1Node(TCRC8T1Node&& other) = default;
  TCRC8T1Node& operator=(const TCRC8T1Node& other) = default;
  TCRC8T1Node& operator=(TCRC8T1Node&& other) = default;

  virtual void update() override {
    m_crc.process_bytes(m_pBeginNode->data(), m_distanceBytes);
    uint8_t asd = m_crc.checksum();
    writeUnsignedInt8(m_crc.checksum());
  }

  size_t init(void* pInit, TBaseNode* pBeginNode, TBaseNode* pEndNode) noexcept {
    m_pBeginNode = pBeginNode;
    m_pEndNode = pEndNode;
    m_distanceBytes = reinterpret_cast<char*>(pEndNode->data()) - reinterpret_cast<char*>(pBeginNode->data()) + pEndNode->sizeBytes();
    return TScalarNode<uint8_t>::init(pInit);
  }

 private:
  // Members
};

#endif  // __T_C_R_C8_T1_NODE_HPP_9VDG0BGKUQ88__
