#include <array>
#include <libTProtoPacket/TProtoPacket.hpp>

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
  std::vector<uint8_t> v1;
  v1.assign({1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0});
  TProtoPacket t{};
  t.init(v1.data());
  return 0;
}