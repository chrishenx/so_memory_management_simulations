#ifndef PAGE_H
#define PAGE_H

#include <ostream>

using uint = unsigned int;

struct Page {
  const uint number;
  uint memory_address;
  
  bool state = false;
  bool referenced = false;
  bool modified = false; 
  
  uint times_referenced = 0;
  
  Page(uint number, uint address = 0) 
    : number(number), memory_address(address) {}
};

std::ostream& operator<<(std::ostream& os, const Page& page);

#endif // PAGE_H