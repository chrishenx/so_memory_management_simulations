#include "task.h"

#include <cstdio>
#include <random>
#include <chrono>

using namespace std;

static mt19937_64 random_generator(
    chrono::system_clock::now().time_since_epoch().count()
  );

uint Task::last_number = 1;

ostream& operator<<(ostream& os, const Task& task) {
  printf(" J%02d     %05d     %03d", task.number, task.address_repr, task.loc);
  return os;
}

void Task::create_pages() {
  for (uint i = 0; i * LINES_PER_PAGE < loc; i++) {
    pages.push_back(Page(i));
  }
}

void Task::create_random_sequence(uint max_seq_size) {
  sequence.clear();
  uniform_int_distribution<uint> distribution1(0, pages.size() - 1);
  if (max_seq_size < 4) max_seq_size = 4;
  uniform_int_distribution<uint> distribution2(3, max_seq_size);
  uint sequence_size = distribution2(random_generator);
  int last_random_value = -1;
  while (sequence_size > 0) {
    int random_value = distribution1(random_generator);   
    if (last_random_value == -1 || random_value != last_random_value) {
      last_random_value = random_value;
      sequence.push_back(&pages[last_random_value]);
      sequence_size--;
    }
  }    
}

Page* Task::get_LFU_page() {
  Page* LFU_page = nullptr;
  for (auto& page : pages) {
    if (page.state && !page.referenced) {
      if (LFU_page == nullptr || page.times_referenced < LFU_page->times_referenced) {
        // If LFU_page is null, then page_ptr is the first page in memory
        LFU_page = &page;
      }
    }
  }
  return LFU_page;
}