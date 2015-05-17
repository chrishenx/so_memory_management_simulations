#include "memory_unit.h"
#include <cstdio>

using namespace std;

uint MemoryUnit::last_number = 0;

ostream& operator<<(ostream& os, const MemoryUnit& mu) {
  printf("%02d      %05d KB      %d", mu.number, mu.address, mu.state);
  return os;
}
