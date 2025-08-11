#include <benchmark/benchmark.h>

#define private public
#include <details/TScalarNode.hpp>
#undef private

static void BM_TScalarNode_WriteInt32Operation(benchmark::State& state) {
  std::vector<uint8_t> testRawData1;
  testRawData1.assign({1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0});
  TScalarNode<int32_t> testNode{TBaseNode::EBytesOrder::littleEndian, 1};
  testNode.init(reinterpret_cast<uint8_t*>(testRawData1.data()) + 10);
  for (auto _ : state) {
    testNode.write_int32_t(0xC0DE'ABCD);
  }
}
BENCHMARK(BM_TScalarNode_WriteInt32Operation);

BENCHMARK_MAIN();