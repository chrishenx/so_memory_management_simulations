#ifndef MARCO_H
#define MARCO_H

#include <ostream>

using uint = unsigned int;

struct MemoryUnit {
  const static uint SIZE;

  uint number;
  uint address;
  bool state;

  MemoryUnit(bool state = false)
      : number(last_number), address(last_number * SIZE), state(state) {
    last_number++;
  }

 private:
  static uint last_number;
};

std::ostream& operator<<(std::ostream& os, const MemoryUnit& mu);

#endif // MARCO_H