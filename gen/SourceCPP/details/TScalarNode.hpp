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

#include "TBaseNode.hpp"

///////////////////////////////////////////////////////////
/// @brief TScalarNode
///
template <typename ScalarType>
class TScalarNode : public TBaseNode {
 protected:
  ScalarType* m_pData{nullptr};

  template <typename T>
  void readScalar(T& value) {
    if (m_littleEndian == EBytesOrder::littleEndian) {
      value = static_cast<T>(*m_pData);
    } else {
      value = swapBytes(static_cast<T>(*m_pData));
    }
  }

  template <typename T>
  void writeScalar(const T& value) {
    if (m_littleEndian == EBytesOrder::littleEndian) {
      *m_pData = static_cast<ScalarType>(value);
    } else {
      *m_pData = swapBytes(static_cast<ScalarType>(value));
    }
  }

 public:
  TScalarNode() = delete;
  explicit TScalarNode(EBytesOrder littleEndian = EBytesOrder::littleEndian, const size_t& arraySize = 1)
   : TBaseNode{littleEndian, arraySize, arraySize * sizeof(ScalarType)} {}

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
  virtual void readData(void* pDst, size_t countBytes, size_t posArray = 0) override {
    char* data = static_cast<char*>(m_pData);
    char* dst = static_cast<char*>(pDst);
    for (int i = posArray; i < countBytes && i < m_countBytes; ++i) {
      dst[i] = data[i];
    }
  }

  virtual void writeFloat(float src) override { writeScalar(src); }
  virtual void writeDouble(double src) override { writeScalar(src); }
  virtual void writeInt8(int8_t src) override { writeScalar(src); }
  virtual void writeInt16(int16_t src) override { writeScalar(src); }
  virtual void writeInt32(int32_t src) override { writeScalar(src); }
  virtual void writeInt64(int64_t src) override { writeScalar(src); }
  virtual void writeInt128(__int128_t src) override { writeScalar(src); }
  virtual void writeUnsignedInt8(uint8_t src) override { writeScalar(src); }
  virtual void writeUnsignedInt16(uint16_t src) override { writeScalar(src); }
  virtual void writeUnsignedInt32(uint32_t src) override { writeScalar(src); }
  virtual void writeUnsignedInt128(__uint128_t src) override { writeScalar(src); }
  virtual void writeData(void* pSrc, size_t countBytes, size_t posArray = 0) override {
    char* data = static_cast<char*>(m_pData);
    char* src = static_cast<char*>(pSrc);
    for (int i = posArray; i < countBytes && i < m_countBytes; ++i) {
      data[i] = src[i];
    }
  }

  virtual operator float() const override { float res; readScalar(res); return res; }
  virtual operator double() const override { double res; readScalar(res); return res; }
  virtual operator int8_t() const override  { int8_t res; readScalar(res); return res; }
  virtual operator int16_t() const override  { int16_t res; readScalar(res); return res; }
  virtual operator int32_t() const override  { int32_t res; readScalar(res); return res; }
  virtual operator int64_t() const override  { int64_t res; readScalar(res); return res; }
  virtual operator __int128_t() const override  { __int128_t res; readScalar(res); return res; }
  virtual operator uint8_t() const override  { uint8_t res; readScalar(res); return res; }
  virtual operator uint16_t () const override  { uint16_t res; readScalar(res); return res; }
  virtual operator uint32_t () const override  { uint32_t res; readScalar(res); return res; }
  virtual operator __uint128_t () const override  { __uint128_t res; readScalar(res); return res; }

  virtual TBaseNode& operator=(float rhs) { writeScalar(rhs); return *this; }
  virtual TBaseNode& operator=(double rhs) { writeScalar(rhs); return *this; }
  virtual TBaseNode& operator=(int8_t rhs) { writeScalar(rhs); return *this; }
  virtual TBaseNode& operator=(int16_t rhs) { writeScalar(rhs); return *this; }
  virtual TBaseNode& operator=(int32_t rhs) { writeScalar(rhs); return *this; }
  virtual TBaseNode& operator=(int64_t rhs) { writeScalar(rhs); return *this; }
  virtual TBaseNode& operator=(__int128_t rhs) { writeScalar(rhs); return *this; }
  virtual TBaseNode& operator=(uint8_t rhs) { writeScalar(rhs); return *this; }
  virtual TBaseNode& operator=(uint16_t rhs) { writeScalar(rhs); return *this; }
  virtual TBaseNode& operator=(uint32_t rhs) { writeScalar(rhs); return *this; }
  virtual TBaseNode& operator=(__uint128_t rhs) { writeScalar(rhs); return *this; }

  virtual void fromString(const char* str, int32_t base = 10) override {
    char* end = nullptr;
    if constexpr (std::is_integral_v<ScalarType> || std::is_enum_v<ScalarType>) {
      if (std::is_signed_v<ScalarType>) {
        writeScalar(static_cast<ScalarType>(strtol(str, &end, base)));
      } else {
        writeScalar(static_cast<ScalarType>(strtoul(str, &end, base)));
      }
    } else if constexpr (std::is_floating_point_v<ScalarType>) {
      writeScalar(static_cast<ScalarType>(strtod(str, &end)));
    }
    if (*end != '\0') {
      throw std::invalid_argument("Invalid argument to convert");
    }
  }

  virtual std::string toString() override {
    if constexpr (std::is_same_v<ScalarType, __uint128_t>
     || std::is_same_v<ScalarType, __int128_t>) {
      if (*m_pData == 0) {
        return "0";
      }
      std::string result;
      ScalarType num;
      readScalar(num);
      if (num < 0) {
          num = -num;
          result += '-';
      }
      do {
          int digit = num % 10;
          result = std::to_string(digit) + result;
          num = num / 10;
      } while (num != 0);
      return result;
    }
    return std::to_string(*m_pData);
  }

  virtual void update() override {}
  virtual void* data() noexcept override { return m_pData; }
  virtual size_t init(void* pInit) noexcept override {
    m_pData = reinterpret_cast<ScalarType*>(pInit);
    m_countBytes = m_arraySize * sizeof(ScalarType);
    return m_countBytes;
  }

  ScalarType swapBytes(ScalarType original) {
    if constexpr (std::is_same_v<float, ScalarType>) {
      union {
          float f;
          uint32_t i;
      } converter;
      converter.f = original;
      converter.i = __bswap_32(converter.i);
      return converter.f;
    }
    if constexpr (std::is_same_v<double, ScalarType>) {
      union {
          double d;
          uint64_t i;
      } converter;
      converter.d = original;
      converter.i = __bswap_64(converter.i);
      return converter.d;
    }
    if constexpr (sizeof(ScalarType == 2)) {
      return __bswap_16(original);
    }
    if constexpr (sizeof(ScalarType == 4)) {
      return __bswap_32(original);
    }
    if constexpr (sizeof(ScalarType == 8)) {
      return __bswap_64(original);
    }
    if constexpr (sizeof(ScalarType == 16)) {
      union {
        unsigned __uint128_t v;
        unsigned uint64_t q[2];
      } u1, u2;
      u1.v = original;
      u2.q[1] = __bswap_64(u1.q[0]);
      u2.q[0] = __bswap_64(u1.q[1]);
      return u2.v;
    }
    return original;
  }
};

#endif  // __T_SCALAR_NODE_HPP_VVPF5CN38WNG__
