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

#include <tsl/array_map.h>

#include "TBaseNode.hpp"

///////////////////////////////////////////////////////////
/// @brief TBaseSerDesAdapter
using TBaseNodePtrMap = tsl::array_map<char, TBaseNode*>;

class TBaseSerDesAdapter {
 public:
  TBaseSerDesAdapter() = default;
  virtual ~TBaseSerDesAdapter() = default;
  TBaseSerDesAdapter(const TBaseSerDesAdapter& other) = default;
  TBaseSerDesAdapter(TBaseSerDesAdapter&& other) = default;
  TBaseSerDesAdapter& operator=(const TBaseSerDesAdapter& other) = default;
  TBaseSerDesAdapter& operator=(TBaseSerDesAdapter&& other) = default;
  virtual void init(void* pInit) = 0;
  virtual void update() = 0;
  virtual TBaseNodePtrMap& getNodeMap() = 0;
};

#endif  // __T_BASE_SER_DES_ADAPTER_HPP_XT6CLJEHL75C__
