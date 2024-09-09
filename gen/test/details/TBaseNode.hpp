/**
 * @file TBaseNode.hpp
 * @author Sokolov Alexander (a.s.sokolov@arale.ru)
 * @brief Arale SerDesAdapter base node
 * @version 0.1
 * @date 2024-09-08
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef __T_BASE_NODE_HPP_1UV98Z4DK9ZI__
#define __T_BASE_NODE_HPP_1UV98Z4DK9ZI__

#include <cstddef>

#include <stdint.h>

///////////////////////////////////////////////////////////
/// @brief TBaseNode
/// abstract class
/// Setters and getters are more preferable then operators
/// Use init function after ctor for proper node usege
class TBaseNode {
 protected:
  bool m_littleEndian{true};
  size_t m_arraySize{1};
  size_t m_countBytes{1};

 public:
  TBaseNode() = delete;
  TBaseNode(bool littleEndian, const size_t& arraySize, const size_t& countBytes) : m_littleEndian{littleEndian}, m_arraySize{arraySize}, m_countBytes{countBytes} {};

  virtual ~TBaseNode() = default;
  TBaseNode(const TBaseNode& other) = default;
  TBaseNode(TBaseNode&& other) = default;
  TBaseNode& operator=(const TBaseNode& other) = default;
  TBaseNode& operator=(TBaseNode&& other) = default;

  virtual void readFloat(float& dst) = 0;
  virtual void readDouble(double& dst) = 0;
  virtual void readInt8(int8_t& dst) = 0;
  virtual void readInt16(int16_t& dst) = 0;
  virtual void readInt32(int32_t& dst) = 0;
  virtual void readInt64(int64_t& dst) = 0;
  virtual void readInt128(__int128_t& dst) = 0;
  virtual void readUnsignedInt8(uint8_t& dst) = 0;
  virtual void readUnsignedInt16(uint16_t& dst) = 0;
  virtual void readUnsignedInt32(uint32_t& dst) = 0;
  virtual void readUnsignedInt128(__uint128_t& dst) = 0;
  virtual void readData(void* pDst, size_t const countBytes, size_t const posArray = 0) = 0;

  virtual void writeFloat(const float& src) = 0;
  virtual void writeDouble(const double& src) = 0;
  virtual void writeInt8(const int8_t& src) = 0;
  virtual void writeInt16(const int16_t& src) = 0;
  virtual void writeInt32(const int32_t& src) = 0;
  virtual void writeInt64(const int64_t& src) = 0;
  virtual void writeInt128(const __int128_t& src) = 0;
  virtual void writeUnsignedInt8(const uint8_t& src) = 0;
  virtual void writeUnsignedInt16(const uint16_t& src) = 0;
  virtual void writeUnsignedInt32(const uint32_t& src) = 0;
  virtual void writeUnsignedInt128(const __uint128_t& src) = 0;
  virtual void writeData(void* pSrc, size_t const countBytes, size_t const posArray = 0) = 0;

  virtual void* data() noexcept = 0;
  virtual size_t init(void* pInit) noexcept = 0;
  virtual void update() = 0;
  const size_t& sizeBytes() const noexcept { return m_countBytes; }

  virtual void fromString(const char* str) = 0;
  // TODO virtual std::string_view toString() = 0;

  virtual operator float() const = 0;
  // TODO virtual TBaseNode& operator=(const float& rhs)
};

#endif  // __T_BASE_NODE_HPP_1UV98Z4DK9ZI__
