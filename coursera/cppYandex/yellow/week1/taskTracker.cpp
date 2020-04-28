/*Реализуйте класс TeamTasks, позволяющий хранить статистику по статусам задач
 * команды разработчиков:
 * Метод PerformPersonTasks должен реализовывать следующий алгоритм:
 * Рассмотрим все не выполненные задачи разработчика person.
   Упорядочим их по статусам: сначала все задачи в статусе NEW, затем все задачи
   в статусе IN_PROGRESS и, наконец, задачи в статусе TESTING.
   Рассмотрим первые task_count задач и переведём каждую из них в следующий статус
   в соответствии с естественным порядком: NEW → IN_PROGRESS → TESTING → DONE.
   Вернём кортеж из двух элементов: информацию о статусах обновившихся задач
   (включая те, которые оказались в статусе DONE) и информацию о статусах остальных
   не выполненных задач.

В случае отсутствия разработчика с именем person метод PerformPersonTasks должени
вернуть кортеж из двух пустых TasksInfo

Гарантируется, что task_count является положительным числом. Если task_count
превышает текущее количество невыполненных задач разработчика, достаточно считать,
что task_count равен количеству невыполненных задач: дважды обновлять статус
какой-либо задачи в этом случае не нужно.

Кроме того, гарантируется, что метод GetPersonTasksInfo не будет вызван для
разработчика, не имеющего задач.
Пример работы метода PerformPersonTasks
Предположим, что у конкретного разработчика имеется 10 задач со следующими статусами:

    NEW — 3
    IN_PROGRESS — 2
    TESTING — 4
    DONE — 1

Поступает команда PerformPersonTasks с параметром task_count = 4, что означает
обновление статуса для 3 задач c NEW до IN_PROGRESS и для 1 задачи с IN_PROGRESS до
TESTING. Таким образом, новые статусы задач будут следующими:

    IN_PROGRESS — 3 обновлённых, 1 старая
    TESTING — 1 обновлённая, 4 старых
    DONE — 1 старая

В этом случае необходимо вернуть кортеж из 2 словарей:

    Обновлённые задачи: IN_PROGRESS — 3, TESTING — 1.
    Не обновлённые задачи, исключая выполненные: IN_PROGRESS — 1, TESTING — 4.

Ни один из словарей не должен содержать лишних элементов, то есть статусов, которым
соответствует ноль задач.

Примечание
Обновление словаря одновременно с итерированием по нему может привести к
непредсказуемым последствиям. При возникновении такой необходимости рекомендуется
сначала в отдельном временном словаре собрать информацию об обновлениях, а затем
применить их к основному словарю.
*/

#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <tuple>

using namespace std;

// Перечислимый тип для статуса задачи
enum class TaskStatus {
  NEW,          // новая
  IN_PROGRESS,  // в разработке
  TESTING,      // на тестировании
  DONE          // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

class TeamTasks {
public:
  // Получить статистику по статусам задач конкретного разработчика
  const TasksInfo& GetPersonTasksInfo(const string& person) const{
    return m.at(person);
  }

  // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
  void AddNewTask(const string& person){
    ++m[person][TaskStatus::NEW];
  }

  // Обновить статусы по данному количеству задач конкретного разработчика,
  // подробности см. ниже
  tuple<TasksInfo, TasksInfo> PerformPersonTasks(
      const string& person, int task_count){
    TasksInfo t = m[person];
    TasksInfo updated_tasks, untouched_tasks;
    int max_task_count = t[TaskStatus::NEW] + t[TaskStatus::IN_PROGRESS] +
        t[TaskStatus::TESTING];
    task_count = min(task_count, max_task_count);
    int for_new = min(task_count, t[TaskStatus::NEW]);
    int for_progress = min(task_count-for_new, t[TaskStatus::IN_PROGRESS]);
    int for_testing = min(task_count-for_new-for_progress, t[TaskStatus::TESTING]);
    if(for_testing > 0){
      int untouched_tasks_count = t[TaskStatus::TESTING]-for_testing;
      if(untouched_tasks_count > 0)
        untouched_tasks[TaskStatus::TESTING] = untouched_tasks_count;
      t[TaskStatus::TESTING]-=for_testing;
      t[TaskStatus::DONE]+=for_testing;
      updated_tasks[TaskStatus::DONE] = for_testing;
    }else{
      if(t[TaskStatus::TESTING] > 0)
        untouched_tasks[TaskStatus::TESTING] = t[TaskStatus::TESTING];
    }
    if(for_progress > 0){
      int untouched_tasks_count = t[TaskStatus::IN_PROGRESS]-for_progress;
      if(untouched_tasks_count > 0)
        untouched_tasks[TaskStatus::IN_PROGRESS] = untouched_tasks_count;
      t[TaskStatus::IN_PROGRESS]-=for_progress;
      t[TaskStatus::TESTING]+=for_progress;
      updated_tasks[TaskStatus::TESTING] = for_progress;
    }else{
      if(t[TaskStatus::IN_PROGRESS] > 0)
        untouched_tasks[TaskStatus::IN_PROGRESS] = t[TaskStatus::IN_PROGRESS];
    }
    if(for_new > 0){
      int untouched_tasks_count = t[TaskStatus::NEW]-for_new;
      if(untouched_tasks_count > 0)
        untouched_tasks[TaskStatus::NEW] = untouched_tasks_count;
      t[TaskStatus::NEW]-=for_new;
      t[TaskStatus::IN_PROGRESS]+=for_new;
      updated_tasks[TaskStatus::IN_PROGRESS] = for_new;
    }else{
      if(t[TaskStatus::NEW] > 0)
        untouched_tasks[TaskStatus::NEW] = t[TaskStatus::NEW];
    }
    vector<TaskStatus> v;
    for(auto& item : t){
      if(item.second == 0)
        v.push_back(item.first);
    }
    for(auto& item : v){
      t.erase(item);
    }
    m[person] = t;
    return tie(updated_tasks, untouched_tasks);
  }
private:
  map<string, TasksInfo> m;
};

// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintTasksInfo(TasksInfo tasks_info) {
  cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
      ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
      ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
      ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main1(){
  cout << static_cast<int>(TaskStatus::NEW) <<
      static_cast<int>(TaskStatus::IN_PROGRESS) << endl;
  return 0;
}

int main() {
  TeamTasks tasks;
  tasks.AddNewTask("Ilia");
  for (int i = 0; i < 3; ++i) {
    tasks.AddNewTask("Ivan");
  }
  cout << "Ilia's tasks: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
  cout << "Ivan's tasks: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

  TasksInfo updated_tasks, untouched_tasks;

  tie(updated_tasks, untouched_tasks) =
      tasks.PerformPersonTasks("Ivan", 2);
  cout << "Updated Ivan's tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "Untouched Ivan's tasks: ";
  PrintTasksInfo(untouched_tasks);

  tie(updated_tasks, untouched_tasks) =
      tasks.PerformPersonTasks("Ivan", 2);
  cout << "Updated Ivan's tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "Untouched Ivan's tasks: ";
  PrintTasksInfo(untouched_tasks);

  return 0;
}
