#include "CLI.hpp"

#include <chrono>
#include <iostream>

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
  run();
  return EXIT_SUCCESS;
}

void run(void) {
  std::vector<uint8_t> v1;
  v1.assign({1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0});
  ProtoPacket t{};
  t.init(v1.data());
  t.m_keyInt1.writeInt32(11);
  t.m_keyFloat1.writeFloat(33.33);
  t.m_keyCRC8T1.update();
  {
    int xi1 = 0;
    float xf1 = 0;
    uint8_t xc1 = 0;
    t.m_keyInt1.readInt32(xi1);
    t.m_keyFloat1.readFloat(xf1);
    t.m_keyCRC8T1.readUnsignedInt8(xc1);
    printf("int val: %d \n", xi1);
    printf("float val: %f \n", xf1);
    printf("crc8 val: %x \n", xc1);
  }

  {
    int xi1 = 0;
    float xf1 = 0;
    uint8_t xc1 = 0;
    t.m_nodesHashTable.at("KEY1_I32")->readInt32(xi1);
    t.m_nodesHashTable.at("KEY2_F")->readFloat(xf1);
    t.m_nodesHashTable.at("KEY3_CRC8T1")->readUnsignedInt8(xc1);
    t.m_keyCRC8T1.readUnsignedInt8(xc1);
    printf("int val: %d \n", xi1);
    printf("float val: %f \n", xf1);
    printf("crc8 val: %x \n", xc1);
  }
}