/*Дана структура LectureTitle:
  struct LectureTitle {
  string specialization;
  string course;
  string week;
};
Допишите конструктор и структуры Specialization, Course, Week так, чтобы объект
LectureTitle можно было создать с помощью кода
LectureTitle title(
    Specialization("C++"),
    Course("White belt"),
    Week("4th")
);
*/
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

struct Specialization{
  string value;
  explicit Specialization(string sp){
    value = sp;
  }
};

struct Course{
  string value;
  explicit Course(string co){
    value = co;
  }
};

struct Week{
  string value;
  explicit Week(string we){
    value = we;
  }
};

struct LectureTitle {
  string specialization;
  string course;
  string week;
  LectureTitle(const struct Specialization& sp,
               const struct Course& co,
               const struct Week& we){
    specialization = sp.value;
    course = co.value;
    week = we.value;
  }
};

void PrintLectureTitle(const struct LectureTitle& title){
  cout << "Specialization: " << title.specialization << endl;
  cout << "Course: " << title.course << endl;
  cout << "Week: " << title.week << endl;
}

int main() {
  LectureTitle title(
    Specialization("C++"),
    Course("White belt"),
    Week("4th")
  );

  //LectureTitle title("C++", "White belt", "4th");
  //LectureTitle title(string("C++"), string("White belt"), string("4th"));
  //LectureTitle title = {"C++", "White belt", "4th"};

  //LectureTitle title = {{"C++"}, {"White belt"}, {"4th"}};

  /*LectureTitle title(
      Course("White belt"),
      Specialization("C++"),
      Week("4th")
  );

  LectureTitle title(
      Specialization("C++"),
      Week("4th"),
      Course("White belt")
  );*/

  PrintLectureTitle(title);
  return 0;
}
