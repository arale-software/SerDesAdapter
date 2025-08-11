/**
 * @file TBaseSerDesAdapter.hpp
 * @author Sokolov Alexander (a.s.sokolov@arale.ru)
 * @brief Base class for SerDesAdapter
 * @version 0.1
 * @date 2024-09-26
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef __T_BASE_SER_DES_ADAPTER_HPP_XT6CLJEHL75C__
#define __T_BASE_SER_DES_ADAPTER_HPP_XT6CLJEHL75C__
#pragma once

#include <tsl/array_map.h>

#include "TBaseNode.hpp"

///////////////////////////////////////////////////////////
/// @brief TBaseSerDesAdapter
/**
 * @note The most efficient hash table by string key
 */
using TBaseNodePtrMap = tsl::array_map<char, TBaseNode*>;

/**
 * @class Base of generic class
 *
 */
class TBaseSerDesAdapter {
 public:
  TBaseSerDesAdapter() = default;
  virtual ~TBaseSerDesAdapter() = default;
  TBaseSerDesAdapter(const TBaseSerDesAdapter& other) = default;
  TBaseSerDesAdapter(TBaseSerDesAdapter&& other) = default;
  TBaseSerDesAdapter& operator=(const TBaseSerDesAdapter& other) = default;
  TBaseSerDesAdapter& operator=(TBaseSerDesAdapter&& other) = default;

  /**
   * @brief The method initializes the nodes by setting its pointer to the desired segment of the data array.
   *
   * @param p_init     begin pointer to the desired segment
   */
  virtual void init(void* p_init) = 0;

  /**
   * @brief think about realloc
   *
   * @param p_init   begin pointer to the desired segment
   */
  // TODO virtual void reinit(void* p_init) = 0;

  /**
   * @brief Recalculation of values for custom nodes.
   *
   */
  virtual void update() = 0;

  /**
   * @brief Get the Node Map object
   * @implements [string key] = TBaseNode pointer
   * @return TBaseNodePtrMap&
   */
  virtual TBaseNodePtrMap& getNodeMap() = 0;
};

#endif  // __T_BASE_SER_DES_ADAPTER_HPP_XT6CLJEHL75C__
