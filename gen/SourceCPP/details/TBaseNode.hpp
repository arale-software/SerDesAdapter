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

#ifdef __SIZEOF_INT128__
using int128_t = __int128_t;
using uint128_t = __uint128_t;
#define INT128_CODE(...) __VA_ARGS__
#else
#define INT128_CODE(...)
#endif

///////////////////////////////////////////////////////////
/// @brief TBaseNode
/// abstract class
/// Setters and getters are more preferable then operators
/// Use init function after ctor for proper node usege
class TBaseNode {
 public:
  enum class EBytesOrder : bool { bigEndian = 0, littleEndian = 1 };

 protected:
  EBytesOrder m_endianess{EBytesOrder::littleEndian};  //!< Refers to the byte order in which multi-byte data types
  size_t m_arraySize{1};                               //!< TODO size for Array-type nodes
  size_t m_countBytes{1};                              //!< Sizeof node data

 public:
  /**
   * @brief Construct a new TBaseNode object
   * @attention DEFAULT CTOR DELETED
   *
   */
  TBaseNode() = delete;

  /**
   * @brief Construct a new TBaseNode object
   *
   * @param littleEndian
   * @param arraySize
   * @param countBytes
   */
  TBaseNode(EBytesOrder endianess, const size_t& arraySize, const size_t& countBytes) : m_endianess{endianess}, m_arraySize{arraySize}, m_countBytes{countBytes} {};

  /**
   * @brief Destroy the TBaseNode object
   * @note default virtual
   */
  virtual ~TBaseNode() = default;

  /**
   * @brief Construct a new TBaseNode object
   * @note default
   *
   * @param other
   */
  TBaseNode(const TBaseNode& other) = default;

  /**
   * @brief Construct a new TBaseNode object
   * @note default
   *
   * @param other
   */
  TBaseNode(TBaseNode&& other) = default;

  /**
   * @brief Assignment operator
   * @note default
   *
   * @param other
   * @return TBaseNode&
   */
  TBaseNode& operator=(const TBaseNode& other) = default;

  /**
   * @brief Move operator
   * @note default
   *
   * @param other
   * @return TBaseNode&
   */
  TBaseNode& operator=(TBaseNode&& other) = default;

  virtual void readFloat(float& dst) const = 0;
  virtual void readDouble(double& dst) const = 0;
  virtual void readInt8(int8_t& dst) const = 0;
  virtual void readInt16(int16_t& dst) const = 0;
  virtual void readInt32(int32_t& dst) const = 0;
  virtual void readInt64(int64_t& dst) const = 0;
  INT128_CODE(virtual void readInt128(int128_t& dst) const = 0;)
  virtual void readUnsignedInt8(uint8_t& dst) const = 0;
  virtual void readUnsignedInt16(uint16_t& dst) const = 0;
  virtual void readUnsignedInt32(uint32_t& dst) const = 0;
  INT128_CODE(virtual void readUnsignedInt128(uint128_t& dst) const = 0;)
  virtual void readData(void* pDst, size_t countBytes, size_t posArray = 0) const = 0;

  virtual void writeFloat(float src) = 0;
  virtual void writeDouble(double src) = 0;
  virtual void writeInt8(int8_t src) = 0;
  virtual void writeInt16(int16_t src) = 0;
  virtual void writeInt32(int32_t src) = 0;
  virtual void writeInt64(int64_t src) = 0;
  INT128_CODE(virtual void writeInt128(int128_t src) = 0;)
  virtual void writeUnsignedInt8(uint8_t src) = 0;
  virtual void writeUnsignedInt16(uint16_t src) = 0;
  virtual void writeUnsignedInt32(uint32_t src) = 0;
  INT128_CODE(virtual void writeUnsignedInt128(uint128_t src) = 0;)
  virtual void writeData(const void* pSrc, size_t countBytes, size_t posArray = 0) = 0;

  virtual void* data() noexcept = 0;
  virtual size_t init(void* pInit) noexcept = 0;
  virtual void reinit(void* pInit) noexcept = 0;
  virtual void update() = 0;
  size_t sizeBytes() const noexcept { return m_countBytes; }

  virtual void fromString(const char* str, int32_t base = 10) = 0;
  virtual std::string toString() = 0;

  virtual operator float() const = 0;
  virtual operator double() const = 0;
  virtual operator int8_t() const = 0;
  virtual operator int16_t() const = 0;
  virtual operator int32_t() const = 0;
  virtual operator int64_t() const = 0;
  INT128_CODE(virtual operator int128_t() const = 0;)
  virtual operator uint8_t() const = 0;
  virtual operator uint16_t() const = 0;
  virtual operator uint32_t() const = 0;
  INT128_CODE(virtual operator uint128_t() const = 0;)
};

#endif  // __T_BASE_NODE_HPP_1UV98Z4DK9ZI__
