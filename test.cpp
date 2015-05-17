#include <iostream>
#include <chrono>
#include <random>
#include <cstdio>
#include <cstdlib>

#include "simple_list.h"
#include "memory_unit.h"
#include "task.h"
#include "memory_management.h"

using namespace std;
using namespace chrono;

static mt19937_64 gen(chrono::system_clock::now().time_since_epoch().count());

using uint = unsigned int;

// Unidades en KB

const uint MEMORY_SIZE = 1 * 12;
const uint MemoryUnit::SIZE = 2;
const uint Task::LINES_PER_PAGE = 100;

SList<MemoryUnit> create_memory_units();
SList<Task> create_tasks(uint count);
void create_tasks_sequences(SList<Task>& tasks);

// MAIN FUNCTION

void Practica1(); // Paginacion simple
void Practica2(); // Paginacion por demanda
void Practica3(); // Algoritmo de reemplazo FIFO
void Practica4(); // Algoritmo de reemplazo LFU

int main() {
  system("cls");
  
  cout << "      IPN" << endl;
  cout << "    ESIME Culhuacan" << endl;
  cout << "\n  Materia: Sistemas operativos" << endl;
  cout << "  Programa creado por Christian Gonzalez Leon\n" << endl;
 
  // Practica1(); 
  
  // Practica2();
  
  // Practica3();
  
  Practica4();
  
  cout << "\n   Gracias por usar este programa," << endl;
  cout << "   Hasta luego!" << endl;
  
  cout << "\n  Presione una tecla para salir . . ." << endl;
  system("pause>null");
  
  return 0;
}

// END OF MAIN FUNCTION

void Practica1() {
  printf("Tama%co de memoria: %d KB\n", char(164), MEMORY_SIZE);
  printf("Tama%co de marcos: %d KB\n", char(164), MemoryUnit::SIZE);
  SList<MemoryUnit> memory_units = create_memory_units();
  print_memory_units(memory_units);
  cout << endl;
  SList<Task> tasks = create_tasks(10);
  print_tasks(tasks);
  print_all_pages(tasks);
  
  assign_SO_memory(memory_units);
  simple_pagination(memory_units, tasks);
  print_memory_units(memory_units);
  cout << endl;
  print_all_pages(tasks);
  cout << endl;
}

void Practica2() {
  printf("Tama%co de memoria: %d KB\n", char(164), MEMORY_SIZE);
  printf("Tama%co de marcos: %d KB\n", char(164), MemoryUnit::SIZE);
  SList<MemoryUnit> memory_units = create_memory_units();
  print_memory_units(memory_units);
  cout << endl;
  SList<Task> tasks = create_tasks(1);
  print_tasks(tasks);
  cout << endl;
  print_all_pages(tasks);
  
  cout << endl;
  assign_SO_memory(memory_units);  
  create_tasks_sequences(tasks);
  print_tasks_sequences(tasks);
  Simulate_PaginationByDemand(memory_units, tasks, 1);
}

void Practica3() {
  printf("Tama%co de memoria: %d KB\n", char(164), MEMORY_SIZE);
  printf("Tama%co de marcos: %d KB\n", char(164), MemoryUnit::SIZE);
  SList<MemoryUnit> memory_units = create_memory_units();
  print_memory_units(memory_units);
  cout << endl;
  SList<Task> tasks = create_tasks(1);
  print_tasks(tasks);
  cout << endl;
  print_all_pages(tasks);
  
  cout << endl;
  assign_SO_memory(memory_units);  
  create_tasks_sequences(tasks);
  print_tasks_sequences(tasks);
  FIFO_Simulation(memory_units, tasks, 1);
}

void Practica4() {
  printf("Tama%co de memoria: %d KB\n", char(164), MEMORY_SIZE);
  printf("Tama%co de marcos: %d KB\n", char(164), MemoryUnit::SIZE);
  SList<MemoryUnit> memory_units = create_memory_units();
  print_memory_units(memory_units);
  cout << endl;
  SList<Task> tasks = create_tasks(1);
  print_tasks(tasks);
  cout << endl;
  print_all_pages(tasks);
  
  cout << endl;
  assign_SO_memory(memory_units);  
  create_tasks_sequences(tasks);
  print_tasks_sequences(tasks);
  LFU_Simulation(memory_units, tasks, 1);
}

SList<MemoryUnit> create_memory_units() {
  SList<MemoryUnit> memory_units;
  auto last_unit = memory_units.before_begin();
  const uint N = MEMORY_SIZE / MemoryUnit::SIZE;
  for (uint i = 0; i < N; i++) {
    last_unit = memory_units.insert(last_unit, MemoryUnit(false));
  }
  return memory_units;
}

SList<Task> create_tasks(uint count) {
  uint limit = SO * 1024 - 1;
  uniform_int_distribution<int> dist1(0, limit);
  uniform_int_distribution<int> dist2(100, 1000);
  uint start_address = 0;
  do  {
    start_address = dist1(gen);
  } while(start_address + count > limit);
  SList<Task> tasks;
  auto last_task = tasks.before_begin();
  for (uint i = 0; i < count; i++) {
    last_task = tasks.insert(last_task, Task(start_address + i, dist2(gen)));
    last_task->create_pages();
  }
  return tasks;
}

void create_tasks_sequences(SList<Task>& tasks) {
  for (auto& task : tasks) {
    task.create_random_sequence(10);
  }
}

