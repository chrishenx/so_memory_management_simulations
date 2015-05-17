#include "memory_management.h"

#include "task.h"
#include "page.h"

#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;

void assign_SO_memory(SList<MemoryUnit>& memory_units) {
  static bool assigned = false;
  if (!assigned) {
    auto current_memory_unit = memory_units.begin();
    for (uint i = 0; i < SO_PAGES; i++) {
      current_memory_unit->state = true;
      current_memory_unit++;
    }
  }
  assigned = true;
}

void simple_pagination(SList<MemoryUnit>& memory_units, SList<Task>& tasks) {
  auto current_memory_unit = memory_units.begin();
  current_memory_unit += SO_PAGES;
  uint remaining_memory_units = memory_units.length() - SO_PAGES;
  for (auto& task : tasks) {
    if (remaining_memory_units > 0) {
      auto page = task.pages.begin();
      page->memory_address = current_memory_unit->address;
      page->state = true;
      page->referenced = true;
      current_memory_unit->state = true;
      current_memory_unit++;
      remaining_memory_units--;
    }
  }
}

void Simulate_PaginationByDemand(SList<MemoryUnit>& memory_units, 
    SList<Task>& tasks, uint how_many_tasks) {
  if (how_many_tasks > tasks.length()) {
    how_many_tasks = tasks.length();
  }
  cout << endl;
  auto current_memory_unit = memory_units.begin();
  current_memory_unit += SO_PAGES;  
  uint tasks_completed = 0;
  printf("Se han asignado %d paginas para el SO\n\n", SO_PAGES);
  cout << "Presione ENTER para comenzar la simulacion de paginacion por demanda...\n" << endl;
  system("pause>null&cls");
  for (auto& task : tasks) {
    if (tasks_completed >= how_many_tasks) break;
    for (uint i = 0; i < task.sequence.size(); i++) {
      auto current_page = task.sequence[i];
      current_page->referenced = true;
      if (i > 0) {
        task.sequence[i - 1]->referenced = false; 
      }
      if (!current_page->state) {
        current_page->state = true;
        if (!current_memory_unit.is_nullptr()) {
          current_page->memory_address = current_memory_unit->address;
          current_memory_unit->state = true;
          current_memory_unit++;
        } else {
          // Fallo de pagina
          current_page->memory_address = task.sequence[i - 1]->memory_address;
          task.sequence[i - 1]->state = false;
          task.sequence[i - 1]->memory_address = 0;  
        }
      }
      cout << "  Asignando tarea J" << task.number << endl;
      cout << "\n Secuencia a ejecutar:  ";
      print_task_sequence(task);
      cout << endl;
      printf("\nEjecutando P%02d\n", current_page->number);
      print_memory_units(memory_units); 
      print_pages(task);
      cout << "\n-------------------------------" << endl;
      system("pause&cls");      
    }
    cout << endl;
    tasks_completed++;
  }
}

void FIFO_Simulation(SList<MemoryUnit>& memory_units, SList<Task>& tasks,
    uint how_many_tasks) {   
  if (how_many_tasks > tasks.length()) {
    how_many_tasks = tasks.length();
  }   
  cout << endl;
  auto current_memory_unit = memory_units.begin();
  current_memory_unit += SO_PAGES;  
  uint tasks_completed = 0;
  printf("Se han asignado %d paginas para el SO\n\n", SO_PAGES);
  cout << "Presione ENTER para comenzar la simulacion de algoritmo FIFO...\n" << endl;
  system("pause>null&cls");
  for (auto& task : tasks) {
    if (tasks_completed >= how_many_tasks) break;
    queue<Page*> pages_queue; 
    for (uint i = 0; i < task.sequence.size(); i++) {
      auto current_page = task.sequence[i];
      current_page->referenced = true;
      if (i > 0) {
        task.sequence[i - 1]->referenced = false; 
      }
      if (!current_page->state) { 
        pages_queue.push(current_page);
        current_page->state = true;
        if (!current_memory_unit.is_nullptr()) {
          current_page->memory_address = current_memory_unit->address;
          current_memory_unit->state = true;
          current_memory_unit++;
        } else {
          // Fallo de pagina
          auto oldest_page = pages_queue.front();
          pages_queue.pop();
          oldest_page->state = false;
          current_page->memory_address = oldest_page->memory_address;
          oldest_page->memory_address = 0;
        } 
      }
      cout << "\n Asignando tarea J" << task.number << endl;
      cout << "\n Ejecutando secuencia:  ";
      print_task_sequence(task);
      cout << endl;
      printf("\n    Ejecutando P%02d\n", current_page->number);
      print_memory_units(memory_units); 
      print_pages(task);
      cout << "\n-------------------------------" << endl;
      system("pause&cls");      
    }
    cout << endl;
    tasks_completed++;
  }  
}

void LFU_Simulation(SList<MemoryUnit>& memory_units, SList<Task>& tasks,
  uint how_many_tasks) {
  if (how_many_tasks > tasks.length()) {
    how_many_tasks = tasks.length();
  }   
  cout << endl;
  auto current_memory_unit = memory_units.begin();
  current_memory_unit += SO_PAGES;  
  uint tasks_completed = 0;
  printf("Se han asignado %d paginas para el SO\n\n", SO_PAGES);
  cout << "Presione ENTER para comenzar la simulacion de algoritmo LFU...\n" << endl;
  system("pause>null&cls");  
  for (auto& task : tasks) {
    if (tasks_completed >= how_many_tasks) break;
    for (uint i = 0; i < task.sequence.size(); i++) {
      auto current_page = task.sequence[i];
      current_page->referenced = true;
      current_page->times_referenced++;
      if (i > 0) {
        task.sequence[i - 1]->referenced = false; 
      }
      if (!current_page->state) { 
        current_page->state = true;
        if (!current_memory_unit.is_nullptr()) {
          current_page->memory_address = current_memory_unit->address;
          current_memory_unit->state = true;
          current_memory_unit++;
        } else { 
          // Fallo de pagina
          auto LFU_page = task.get_LFU_page();
          LFU_page->state = false;
          current_page->memory_address = LFU_page->memory_address;
          LFU_page->memory_address = 0;
        }
      }
      cout << "\n Asignando tarea J" << task.number << endl;
      cout << "\n Ejecutando secuencia:  ";
      print_task_sequence(task);
      cout << endl;
      printf("\n    Ejecutando P%02d\n", current_page->number);
      print_memory_units(memory_units); 
      print_pages(task);
      cout << "\n-------------------------------" << endl;
      system("pause&cls");    
    }
    cout << endl;
    tasks_completed++;
  }
}

//  FUNCIONS TO PRINT 

void print_memory_units(const SList<MemoryUnit>& memory_units) {
  cout << "\n  No  |  Localidad  | Estado" << endl;
  for (const auto& memory_unit :  memory_units) {
    cout << "  " << memory_unit << endl;
  }
}

void print_tasks(const SList<Task>& tasks) {
  cout << "Tareas:\n" << endl;
  cout << " Tarea | Localidad | LOC" << endl;
  for (const auto& task : tasks) {
    cout << "  " << task << endl;
  }
}

void print_task_sequence(const Task& task) {
  printf("J%02d  ", task.number);
  for (const auto& page_ptr : task.sequence) {
    printf("  -> P%02d", page_ptr->number);
  }
}

void print_tasks_sequences(const SList<Task>& tasks) {
  cout << "Secuencia en las tareas:\n" << endl;
  for (const auto& task : tasks) {
    print_task_sequence(task);
    cout << endl;
  }
}

void print_pages(const Task& task) {
  printf("\n  J%02d\n", task.number);
  for (const auto& page : task.pages) {
    cout << "  " << page << endl;
  }
}

void print_all_pages(const SList<Task>& tasks) {
  cout << "Paginas:" << endl;
  cout << "\n  No.      LOC Marco   Est    Ref  Mod" << endl;
  for (const auto& task : tasks) {
    print_pages(task);
  }
}