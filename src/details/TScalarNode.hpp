/**
 * @file TScalarNode.hpp
 * @author Sokolov Alexander (a.s.sokolov@arale.ru)
 * @brief Arale SerDesAdapter simple types node
 * @version 0.1
 * @date 2024-09-08
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef __T_SCALAR_NODE_HPP_VVPF5CN38WNG__
#define __T_SCALAR_NODE_HPP_VVPF5CN38WNG__

#include <libSerDesAdapter/details/TBaseNode.hpp>

///////////////////////////////////////////////////////////
/// @brief TScalarNode
///
template <typename ScalarType>
class TScalarNode : public TBaseNode {
 protected:
  ScalarType* m_pData{nullptr};

  template <typename T>
  void readScalar(T& value) {
    value = *m_pData;
  }

  template <typename T>
  void writeScalar(const T& value) {
    *m_pData = value;
  }

 public:
  TScalarNode() = delete;
  explicit TScalarNode(EBytesOrder littleEndian = EBytesOrder::littleEndian, const size_t& arraySize = 1) : TBaseNode{littleEndian, arraySize, arraySize * sizeof(ScalarType)} {};

  virtual ~TScalarNode() = default;
  TScalarNode(const TScalarNode& other) = default;
  TScalarNode(TScalarNode&& other) = default;
  TScalarNode& operator=(const TScalarNode& other) = default;
  TScalarNode& operator=(TScalarNode&& other) = default;

 public:
  virtual void readFloat(float& dst) override { readScalar(dst); }
  virtual void readDouble(double& dst) override { readScalar(dst); }
  virtual void readInt8(int8_t& dst) override { readScalar(dst); }
  virtual void readInt16(int16_t& dst) override { readScalar(dst); }
  virtual void readInt32(int32_t& dst) override { readScalar(dst); }
  virtual void readInt64(int64_t& dst) override { readScalar(dst); }
  virtual void readInt128(__int128_t& dst) override { readScalar(dst); }
  virtual void readUnsignedInt8(uint8_t& dst) override { readScalar(dst); }
  virtual void readUnsignedInt16(uint16_t& dst) override { readScalar(dst); }
  virtual void readUnsignedInt32(uint32_t& dst) override { readScalar(dst); }
  virtual void readUnsignedInt128(__uint128_t& dst) override { readScalar(dst); }
  virtual void readData(void* pDst, size_t const countBytes, size_t const posArray = 0) override {}

  virtual void writeFloat(const float& src) override { writeScalar(src); }
  virtual void writeDouble(const double& src) override { writeScalar(src); }
  virtual void writeInt8(const int8_t& src) override { writeScalar(src); }
  virtual void writeInt16(const int16_t& src) override { writeScalar(src); }
  virtual void writeInt32(const int32_t& src) override { writeScalar(src); }
  virtual void writeInt64(const int64_t& src) override { writeScalar(src); }
  virtual void writeInt128(const __int128_t& src) override { writeScalar(src); }
  virtual void writeUnsignedInt8(const uint8_t& src) override { writeScalar(src); }
  virtual void writeUnsignedInt16(const uint16_t& src) override { writeScalar(src); }
  virtual void writeUnsignedInt32(const uint32_t& src) override { writeScalar(src); }
  virtual void writeUnsignedInt128(const __uint128_t& src) override { writeScalar(src); }
  virtual void writeData(void* pSrc, size_t const countBytes, size_t const posArray = 0) override {}
  // TODO
  virtual operator float() const override { return *m_pData; }
  virtual void fromString(const char* str) override {}
  virtual void update() override {}
  virtual void* data() noexcept override { return m_pData; }
  virtual size_t init(void* pInit) noexcept override {
    m_pData = reinterpret_cast<ScalarType*>(pInit);
    m_countBytes = m_arraySize * sizeof(ScalarType);
    return m_countBytes;
  }
};

#endif  // __T_SCALAR_NODE_HPP_VVPF5CN38WNG__
