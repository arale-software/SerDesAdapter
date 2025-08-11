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
#pragma once

#include <stdint.h>
#include <concepts>

/**
 * @brief The concept defines the supported data types
 * for the read and write methods of the base class.
 * @note int types, floating point, 8 bytes max size
 * @tparam T
 */
template <typename T>
concept CSupportedBaseNodeType =                            //
    (std::is_floating_point_v<T> || std::is_integral_v<T>)  //
    &&                                                      //
    (sizeof(T) >= 1 && sizeof(T) <= 8)                      //
    &&                                                      //
    !std::is_same_v<T, bool>;                               //

/**
 * @brief Macro for data getter definition
 * @example virtual void read_int8_t(int8_t&) const
 *
 */
#define DEF_DECL_READ_TYPE_METHOD(__TYPE__) virtual void read_##__TYPE__(__TYPE__& dst) const

/**
 * @brief Macro for data setter definition
 * @example virtual void write_int8_t(int8_t)
 *
 */
#define DEF_DECL_WRITE_TYPE_METHOD(__TYPE__) virtual void write_##__TYPE__(__TYPE__ src)

/**
 * @brief Macro helper for read(T) function
 *
 */
#define DEF_READ_METHOD_CE_READ_TYPE(__TYPE__) \
  if constexpr (std::is_same_v<T, __TYPE__>) { \
    read_##__TYPE__(dst);                      \
  }

/**
 * @brief Macro helper for write(T) function
 *
 */
#define DEF_WRITE_METHOD_CE_WRITE_TYPE(__TYPE__) \
  if constexpr (std::is_same_v<T, __TYPE__>) {   \
    write_##__TYPE__(src);                       \
  }
///////////////////////////////////////////////////////////
/**
 * @class TBaseNode
 * /// Abstract class ///
 * Setters and getters are more preferred than operators.
 * Use the init function after the constructor for proper node usage.
 */
class TBaseNode {
 public:
  enum class EBytesOrder : bool { bigEndian = 0, littleEndian = 1 };

 protected:
  EBytesOrder m_endianness{EBytesOrder::littleEndian};  //!< Refers to the byte order in which multi-byte data types
  size_t m_array_size{1};                               //!< TODO size for array-type nodes
  size_t m_byte_count{1};                               //!< Sizeof node data

 public:
  /**
   * @brief Construct a new TBaseNode object
   * @attention DEFAULT CTOR DELETED
   *
   */
  TBaseNode() = delete;

  /**
   * @brief Construct a new TBaseNode object
   * @param endianness    byte order
   * @param array_size    size for array-type nodes
   * @param byte_count    size of node data
   */
  TBaseNode(EBytesOrder endianness, const size_t& array_size, const size_t& byte_count) : m_endianness{endianness}, m_array_size{array_size}, m_byte_count{byte_count} {};

  /**
   * @brief Destroy the TBaseNode object
   * @note default virtual
   */
  virtual ~TBaseNode() = default;

  /**
   * @brief Getter for the size of the node data
   *
   *  @return The size of the data in bytes
   */
  virtual size_t bytesize() const noexcept { return m_byte_count; }

  /**
   * @brief The method initializes the node by setting its pointer to the desired segment of the data array.
   * @implements It is assumed that inherited classes will record the default value when this function is used.
   * @param p_init     pointer to the desired segment
   * @return size_t   the count of bytes used by the current node.
   */
  virtual size_t init(void* p_init) noexcept = 0;

  /**
   * @brief Think about reallocation original data array
   * @todo configure function?
   * @todo same for init? return size_t?
   * @todo maybe pos?
   * @param p_init
   */
  // TODO virtual void reinit(void* p_init) noexcept = 0;  // FIXME

  /**
   * @brief Getter for raw pointer to the original fragment of data.
   *
   * @return void* data pointer
   */
  virtual void* data() noexcept = 0;

  /**
   * @brief Recalculation of values for custom node types.
   *
   */
  virtual void update() = 0;

  /**
   * @brief Getters for supported data types
   *
   */
  DEF_DECL_READ_TYPE_METHOD(float) = 0;
  DEF_DECL_READ_TYPE_METHOD(double) = 0;
  DEF_DECL_READ_TYPE_METHOD(int8_t) = 0;
  DEF_DECL_READ_TYPE_METHOD(int16_t) = 0;
  DEF_DECL_READ_TYPE_METHOD(int32_t) = 0;
  DEF_DECL_READ_TYPE_METHOD(int64_t) = 0;
  DEF_DECL_READ_TYPE_METHOD(uint8_t) = 0;
  DEF_DECL_READ_TYPE_METHOD(uint16_t) = 0;
  DEF_DECL_READ_TYPE_METHOD(uint32_t) = 0;
  DEF_DECL_READ_TYPE_METHOD(uint64_t) = 0;

  /**
   * @brief Setters for supported data types
   *
   */
  DEF_DECL_WRITE_TYPE_METHOD(float) = 0;
  DEF_DECL_WRITE_TYPE_METHOD(double) = 0;
  DEF_DECL_WRITE_TYPE_METHOD(int8_t) = 0;
  DEF_DECL_WRITE_TYPE_METHOD(int16_t) = 0;
  DEF_DECL_WRITE_TYPE_METHOD(int32_t) = 0;
  DEF_DECL_WRITE_TYPE_METHOD(int64_t) = 0;
  DEF_DECL_WRITE_TYPE_METHOD(uint8_t) = 0;
  DEF_DECL_WRITE_TYPE_METHOD(uint16_t) = 0;
  DEF_DECL_WRITE_TYPE_METHOD(uint32_t) = 0;
  DEF_DECL_WRITE_TYPE_METHOD(uint64_t) = 0;

  /**
   * @brief Universal getter for supported data types
   *
   * @tparam T    CSupportedBaseNodeType concept data type
   * @param dst   The variable that the data will be written into.
   */
  template <CSupportedBaseNodeType T>
  void read_node(T& dst) const {
    DEF_READ_METHOD_CE_READ_TYPE(float)     //
    DEF_READ_METHOD_CE_READ_TYPE(double)    //
    DEF_READ_METHOD_CE_READ_TYPE(int8_t)    //
    DEF_READ_METHOD_CE_READ_TYPE(int16_t)   //
    DEF_READ_METHOD_CE_READ_TYPE(int32_t)   //
    DEF_READ_METHOD_CE_READ_TYPE(int64_t)   //
    DEF_READ_METHOD_CE_READ_TYPE(uint8_t)   //
    DEF_READ_METHOD_CE_READ_TYPE(uint16_t)  //
    DEF_READ_METHOD_CE_READ_TYPE(uint32_t)  //
    DEF_READ_METHOD_CE_READ_TYPE(uint64_t)  //
  }

  /**
   * @brief Universal setter for supported data types
   *
   * @tparam T    CSupportedBaseNodeType concept data type
   * @param src   A variable whose value is written to by a pointer to the data part of a node.
   */
  template <CSupportedBaseNodeType T>
  void write_node(T& src) const {
    DEF_WRITE_METHOD_CE_WRITE_TYPE(float)     //
    DEF_WRITE_METHOD_CE_WRITE_TYPE(double)    //
    DEF_WRITE_METHOD_CE_WRITE_TYPE(int8_t)    //
    DEF_WRITE_METHOD_CE_WRITE_TYPE(int16_t)   //
    DEF_WRITE_METHOD_CE_WRITE_TYPE(int32_t)   //
    DEF_WRITE_METHOD_CE_WRITE_TYPE(int64_t)   //
    DEF_WRITE_METHOD_CE_WRITE_TYPE(uint8_t)   //
    DEF_WRITE_METHOD_CE_WRITE_TYPE(uint16_t)  //
    DEF_WRITE_METHOD_CE_WRITE_TYPE(uint32_t)  //
    DEF_WRITE_METHOD_CE_WRITE_TYPE(uint64_t)  //
  }

  /**
   * @brief A pointer, an array of data to which the pointer will be written from the data part of the node
   *
   * @param p_dst poiner   array data pointer
   * @param byte_count    size of data to write
   * @param pos           position to write
   */
  virtual void read_data(void* p_dst, size_t byte_count, size_t pos = 0) const = 0;

  /**
   * @brief A pointer is an array of data that the pointer will write to the data portion of the node.
   *
   * @param p_src source   array data pointer
   * @param byte_count    size of data to write
   * @param pos           position to write
   */
  virtual void write_data(const void* p_src, size_t byte_count, size_t pos = 0) = 0;

  /**
   * @brief Converts a string to the target data type for the node
   *
   * @param str     original string
   * @param base    integer number representation
   */
  virtual void from_string(const char* str, int32_t base = 10) = 0;

  /**
   * @brief Converts a target data type for the node to the string
   *
   * @return const char*    string data representation
   */
  virtual const char* to_string() const = 0;

  /**
   * @brief scalar type operators for node
   *
   */
  virtual operator float() const = 0;
  virtual operator double() const = 0;
  virtual operator int8_t() const = 0;
  virtual operator int16_t() const = 0;
  virtual operator int32_t() const = 0;
  virtual operator int64_t() const = 0;
  virtual operator uint8_t() const = 0;
  virtual operator uint16_t() const = 0;
  virtual operator uint32_t() const = 0;
  virtual operator uint64_t() const = 0;

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
};

#endif  // __T_BASE_NODE_HPP_1UV98Z4DK9ZI__
