/**
  This file declares a struct which represents a task to execute.
  
  @author Christian Gonzalez Leon : Aliases (chrishenx, CPlayMasH on youtube)
 */

#ifndef TASK_H
#define TASK_H

#include "page.h"

#include <ostream>
#include <vector>

using uint = unsigned int;

struct Task {
  static const uint LINES_PER_PAGE;

  const uint number;
  const uint address_repr; 
  const uint loc; // Lines of code
  std::vector<Page> pages;
  std::vector<Page*> sequence; // Sequence of calls to the pages

  Task(uint address, uint loc) 
    : number(last_number++), address_repr(address), loc(loc) {}
  void create_pages();
  void create_random_sequence(uint max_seq_size);
  Page* get_LFU_page();
 private:
  static uint last_number;
};

std::ostream& operator<<(std::ostream& os, const Task& task);

#endif // TASK_H