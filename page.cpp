/**
  This file implements the non-inline functions in page.h 
  
  @author Christian Gonzalez Leon : Aliases (chrishenx, CPlayMasH on youtube)
 */

#include "page.h"

#include <cstdio>

using namespace std;

ostream& operator<<(ostream& os, const Page& page) {
  if (page.memory_address == 0) {
    printf("P%02d      ---------    %d     %d     %d", 
      page.number, page.state, page.referenced, page.modified);
  } else {
    printf("P%02d      %05d KB     %d     %d     %d", 
      page.number, page.memory_address, page.state, page.referenced, page.modified);
  }
  return os;
}