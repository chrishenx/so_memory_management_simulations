#ifndef MEMORY_MANAGEMENT_H
#define MEMORY_MANAGEMENT_H

#include "simple_list.h"

#include "memory_unit.h"

struct Task;

static const uint SO_PAGES = 3;
static const uint SO = MemoryUnit::SIZE * SO_PAGES;

using uint = unsigned int;

void assign_SO_memory(SList<MemoryUnit>& memory_units);

void simple_pagination(SList<MemoryUnit>& memory_units, SList<Task>& tasks);

void Simulate_PaginationByDemand(SList<MemoryUnit>& memory_units, 
  SList<Task>& tasks, uint how_many_tasks);
  
void FIFO_Simulation(SList<MemoryUnit>& memory_units, SList<Task>& tasks,
  uint how_many_tasks);
  
void LFU_Simulation(SList<MemoryUnit>& memory_units, SList<Task>& tasks,
  uint how_many_tasks);

void print_tasks(const SList<Task>& tasks);
void print_memory_units(const SList<MemoryUnit>& memory_units);  
void print_task_sequence(const Task& tasks);
void print_tasks_sequences(const SList<Task>& tasks);
void print_pages(const Task& task);
void print_all_pages(const SList<Task>& tasks);

#endif // MEMORY_MANAGEMENT_H