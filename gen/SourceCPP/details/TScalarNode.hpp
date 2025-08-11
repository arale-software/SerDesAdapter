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
#pragma once

#include <array>
#include <charconv>
#include <system_error>
#include <type_traits>

#include "TBaseNode.hpp"

///////////////////////////////////////////////////////////
/// @brief TScalarNode
///
inline thread_local std::array<char, 21> g_int_buffer_scalar_node;
inline thread_local std::array<char, 32> g_float_buffer_scalar_node;

template <typename ScalarType>
class TScalarNode : public TBaseNode {
 protected:
  ScalarType* mp_data{nullptr};

  ScalarType read_scalar() const {
    if (m_endianness == EBytesOrder::littleEndian) {
      return *mp_data;
    } else {
      return swap_bytes(*mp_data);
    }
  }

  template <typename T>
  void write_scalar(const T& value) {
    if (m_endianness == EBytesOrder::littleEndian) {
      *mp_data = static_cast<ScalarType>(value);
    } else {
      *mp_data = swap_bytes(static_cast<ScalarType>(value));
    }
  }

 public:
  TScalarNode() = delete;
  explicit TScalarNode(EBytesOrder endianness = EBytesOrder::littleEndian, const size_t& array_size = 1) : TBaseNode{endianness, array_size, array_size * sizeof(ScalarType)} {}

  virtual ~TScalarNode() = default;
  TScalarNode(const TScalarNode& other) = default;
  TScalarNode(TScalarNode&& other) = default;
  TScalarNode& operator=(const TScalarNode& other) = default;
  TScalarNode& operator=(TScalarNode&& other) = default;

 public:
#define DEF_IMPL_READ_TYPE_METHOD(__TYPE__) \
  DEF_DECL_READ_TYPE_METHOD(__TYPE__) override { dst = static_cast<__TYPE__>(read_scalar()); }

  DEF_IMPL_READ_TYPE_METHOD(float)
  DEF_IMPL_READ_TYPE_METHOD(double)
  DEF_IMPL_READ_TYPE_METHOD(int8_t)
  DEF_IMPL_READ_TYPE_METHOD(int16_t)
  DEF_IMPL_READ_TYPE_METHOD(int32_t)
  DEF_IMPL_READ_TYPE_METHOD(int64_t)
  DEF_IMPL_READ_TYPE_METHOD(uint8_t)
  DEF_IMPL_READ_TYPE_METHOD(uint16_t)
  DEF_IMPL_READ_TYPE_METHOD(uint32_t)
  DEF_IMPL_READ_TYPE_METHOD(uint64_t)

#define DEF_IMPL_WRITE_TYPE_METHOD(__TYPE__) \
  DEF_DECL_WRITE_TYPE_METHOD(__TYPE__) override { write_scalar(src); }

  DEF_IMPL_WRITE_TYPE_METHOD(float)
  DEF_IMPL_WRITE_TYPE_METHOD(double)
  DEF_IMPL_WRITE_TYPE_METHOD(int8_t)
  DEF_IMPL_WRITE_TYPE_METHOD(int16_t)
  DEF_IMPL_WRITE_TYPE_METHOD(int32_t)
  DEF_IMPL_WRITE_TYPE_METHOD(int64_t)
  DEF_IMPL_WRITE_TYPE_METHOD(uint8_t)
  DEF_IMPL_WRITE_TYPE_METHOD(uint16_t)
  DEF_IMPL_WRITE_TYPE_METHOD(uint32_t)
  DEF_IMPL_WRITE_TYPE_METHOD(uint64_t)

#define DEF_DECL_TYPE_OPERATOR(__TYPE__) \
  virtual operator __TYPE__() const override { return static_cast<__TYPE__>(read_scalar()); }

  DEF_DECL_TYPE_OPERATOR(float)
  DEF_DECL_TYPE_OPERATOR(double)
  DEF_DECL_TYPE_OPERATOR(int8_t)
  DEF_DECL_TYPE_OPERATOR(int16_t)
  DEF_DECL_TYPE_OPERATOR(int32_t)
  DEF_DECL_TYPE_OPERATOR(int64_t)
  DEF_DECL_TYPE_OPERATOR(uint8_t)
  DEF_DECL_TYPE_OPERATOR(uint16_t)
  DEF_DECL_TYPE_OPERATOR(uint32_t)
  DEF_DECL_TYPE_OPERATOR(uint64_t)

  virtual void read_data(void* p_dst, size_t byte_count, size_t pos = 0) const override {
    auto data = reinterpret_cast<char*>(mp_data);
    auto dst = static_cast<char*>(p_dst);
    for (size_t i = pos; i < byte_count && i < m_byte_count; ++i) {
      dst[i] = data[i];
    }
  }

  virtual void write_data(const void* p_src, size_t byte_count, size_t pos = 0) override {
    auto data = reinterpret_cast<char*>(mp_data);
    auto src = static_cast<const char*>(p_src);
    for (size_t i = pos; i < byte_count && i < m_byte_count; ++i) {
      data[i] = src[i];
    }
  }

  virtual void from_string(const char* str, int32_t base = 10) override {
    char* end = nullptr;
    if constexpr (std::is_integral_v<ScalarType> || std::is_enum_v<ScalarType>) {
      if (std::is_signed_v<ScalarType>) {
        write_scalar(static_cast<ScalarType>(strtol(str, &end, base)));
      } else {
        write_scalar(static_cast<ScalarType>(strtoul(str, &end, base)));
      }
    } else if constexpr (std::is_floating_point_v<ScalarType>) {
      write_scalar(static_cast<ScalarType>(strtod(str, &end)));
    }
    if (*end != '\0') {
      throw std::invalid_argument("Invalid argument to convert");
    }
  }

  virtual const char* to_string() const override {
    if constexpr (std::is_integral_v<ScalarType>) {
      auto [ptr, ec] = std::to_chars(::g_int_buffer_scalar_node.data(), ::g_int_buffer_scalar_node.data() + ::g_int_buffer_scalar_node.size(), *mp_data);

      if (ec == std::errc()) {
        *ptr = '\0';
        return ::g_int_buffer_scalar_node.data();
      }
    } else if constexpr (std::is_floating_point_v<ScalarType>) {
      constexpr int precision = std::is_same_v<ScalarType, float> ? 6 : 15;
      auto [ptr, ec] = std::to_chars(::g_int_buffer_scalar_node.data(), ::g_int_buffer_scalar_node.data() + ::g_int_buffer_scalar_node.size(), *mp_data, std::chars_format::fixed, precision);

      if (ec == std::errc()) {
        *ptr = '\0';
        return ::g_int_buffer_scalar_node.data();
      }
    }
    return "NaN";
  }

  virtual void update() override {}
  virtual void* data() noexcept override { return mp_data; }

  virtual size_t init(void* p_init) noexcept override {
    mp_data = reinterpret_cast<ScalarType*>(p_init);
    m_byte_count = m_array_size * sizeof(ScalarType);
    return m_byte_count;
  }

  template <typename T>
  size_t init(void* p_init, T init_value) {  // std::forward?
    auto result = init(p_init);
    write_scalar(init_value);
    return result;
  }

  static ScalarType swap_bytes(ScalarType original) {
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
    return original;
  }

  template <typename T>
  const char* numeric_to_cstr(T value) {
    if constexpr (std::is_integral_v<T>) {
      return number_to_cstr(value);
    } else if constexpr (std::is_floating_point_v<T>) {
      return double_to_cstr(value);
    }
  }
};

#endif  // __T_SCALAR_NODE_HPP_VVPF5CN38WNG__