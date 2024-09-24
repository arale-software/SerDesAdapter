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
  virtual TBaseNodePtrMap& getNodeMap() = 0;
};
