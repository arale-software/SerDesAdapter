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

  ScalarType readScalar() const {
    if (m_endianess == EBytesOrder::littleEndian) {
      return *m_pData;
    } else {
      return swapBytes(*m_pData);
    }
  }

  template <typename T>
  void writeScalar(const T& value) {
    if (m_endianess == EBytesOrder::littleEndian) {
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
  virtual void readFloat(float& dst) const override { dst = static_cast<float>(readScalar()); }
  virtual void readDouble(double& dst) const override { dst = static_cast<double>(readScalar()); }
  virtual void readInt8(int8_t& dst) const override { dst = static_cast<int8_t>(readScalar()); }
  virtual void readInt16(int16_t& dst) const override { dst = static_cast<int16_t>(readScalar()); }
  virtual void readInt32(int32_t& dst) const override { dst = static_cast<int32_t>(readScalar()); }
  virtual void readInt64(int64_t& dst) const override { dst = static_cast<int64_t>(readScalar()); }
  INT128_CODE(virtual void readInt128(int128_t& dst) const override { dst = static_cast<int128_t>(readScalar()); })
  virtual void readUnsignedInt8(uint8_t& dst) const override { dst = static_cast<uint8_t>(readScalar()); }
  virtual void readUnsignedInt16(uint16_t& dst) const override { dst = static_cast<uint16_t>(readScalar()); }
  virtual void readUnsignedInt32(uint32_t& dst) const override { dst = static_cast<uint32_t>(readScalar()); }
  INT128_CODE(virtual void readUnsignedInt128(uint128_t& dst) const override { dst = static_cast<uint128_t>(readScalar()); })
  virtual void readData(void* pDst, size_t countBytes, size_t posArray = 0) const override {
    auto data = reinterpret_cast<char*>(m_pData);
    auto dst = static_cast<char*>(pDst);
    for (size_t i = posArray; i < countBytes && i < m_countBytes; ++i) {
      dst[i] = data[i];
    }
  }

  virtual void writeFloat(float src) override { writeScalar(src); }
  virtual void writeDouble(double src) override { writeScalar(src); }
  virtual void writeInt8(int8_t src) override { writeScalar(src); }
  virtual void writeInt16(int16_t src) override { writeScalar(src); }
  virtual void writeInt32(int32_t src) override { writeScalar(src); }
  virtual void writeInt64(int64_t src) override { writeScalar(src); }
  INT128_CODE(virtual void writeInt128(int128_t src) override { writeScalar(src); })
  virtual void writeUnsignedInt8(uint8_t src) override { writeScalar(src); }
  virtual void writeUnsignedInt16(uint16_t src) override { writeScalar(src); }
  virtual void writeUnsignedInt32(uint32_t src) override { writeScalar(src); }
  INT128_CODE(virtual void writeUnsignedInt128(uint128_t src) override { writeScalar(src); })
  virtual void writeData(const void* pSrc, size_t countBytes, size_t posArray = 0) override {
    auto data = reinterpret_cast<char*>(m_pData);
    auto src = static_cast<const char*>(pSrc);
    for (size_t i = posArray; i < countBytes && i < m_countBytes; ++i) {
      data[i] = src[i];
    }
  }

  virtual operator float() const override { return static_cast<float>(readScalar()); }
  virtual operator double() const override { return static_cast<double>(readScalar()); }
  virtual operator int8_t() const override  { return static_cast<int8_t>(readScalar()); }
  virtual operator int16_t() const override  { return static_cast<int16_t>(readScalar()); }
  virtual operator int32_t() const override  { return static_cast<int32_t>(readScalar()); }
  virtual operator int64_t() const override  { return static_cast<int64_t>(readScalar()); }
  INT128_CODE(virtual operator int128_t() const override  { return static_cast<int128_t>(readScalar()); })
  virtual operator uint8_t() const override  { return static_cast<uint8_t>(readScalar()); }
  virtual operator uint16_t () const override  { return static_cast<uint16_t>(readScalar()); }
  virtual operator uint32_t () const override  { return static_cast<uint32_t>(readScalar()); }
  INT128_CODE(virtual operator uint128_t () const override  { return static_cast<uint128_t>(readScalar()); })

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
    INT128_CODE(if constexpr (std::is_same_v<ScalarType, uint128_t> ||
     std::is_same_v<ScalarType, int128_t>) {
      if (*m_pData == 0) {
        return "0";
      }
      std::string result;
      ScalarType num = readScalar();
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
    })
    return std::to_string(*m_pData);
  }

  virtual void update() override {}
  virtual void* data() noexcept override { return m_pData; }
  virtual size_t init(void* pInit) noexcept override {
    m_pData = reinterpret_cast<ScalarType*>(pInit);
    m_countBytes = m_arraySize * sizeof(ScalarType);
    return m_countBytes;
  }

  static ScalarType swapBytes(ScalarType original) {
    if constexpr (std::is_same_v<float, ScalarType>) {
      union {
          float f;
          uint32_t i;
      } converter;
      converter.f = original;
      converter.i = __bswap_32(converter.i);
      return converter.f;
    } else if constexpr (std::is_same_v<double, ScalarType>) {
      union {
          double d;
          uint64_t i;
      } converter;
      converter.d = original;
      converter.i = __bswap_64(converter.i);
      return converter.d;
    } else if constexpr (sizeof(ScalarType) == 2) {
      return __bswap_16(original);
    } else if constexpr (sizeof(ScalarType) == 4) {
      return __bswap_32(original);
    } else if constexpr (sizeof(ScalarType) == 8) {
      return __bswap_64(original);
    }
    INT128_CODE( else if constexpr (sizeof(ScalarType) == 16) {
      union {
        uint128_t v;
        uint64_t q[2];
      } u1, u2;
      u1.v = original;
      u2.q[1] = __bswap_64(u1.q[0]);
      u2.q[0] = __bswap_64(u1.q[1]);
      return u2.v;
    })
    return original;
  }
};

#endif  // __T_SCALAR_NODE_HPP_VVPF5CN38WNG__
