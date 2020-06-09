#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Human {
public:
  Human(const string& name, const string& type):
    Name(name), humanType(type) {
  }
  virtual void Walk(const string& destination) = 0;
  virtual ~Human(){};
  string GetName() const{
    return Name;
  };
  string GetType() const{
    return humanType;
  };
private:
    const string Name;
    const string humanType;
};

class Student : public Human {
public:
  Student(const string& name, const string& favouriteSong):
    Human(name, "Student"), FavouriteSong(favouriteSong){
  }

  void Learn() {
      cout << "Student: " << GetName() << " learns" << endl;
  }

  void Walk(const string& destination) {
      cout << "Student: " << GetName() << " walks to: " << destination << endl;
      cout << "Student: " << GetName() << " sings a song: " << FavouriteSong << endl;
  }

  void SingSong() {
      cout << "Student: " << GetName() << " sings a song: " << FavouriteSong << endl;
  }

private:
  const string FavouriteSong;
};

class Teacher: public Human{
public:
  Teacher(const string& name, const string& subject):
    Human(name, "Teacher"), Subject(subject) {
  }

  void Teach() {
    cout << "Teacher: " << GetName() << " teaches: " << Subject << endl;
  }

  void Walk(const string& destination) {
    cout << "Teacher: " << GetName() << " walks to: " << destination << endl;
  }

private:
  const string Subject;
};

class Policeman: public Human {
public:
  Policeman(const string& name):
    Human(name, "Policeman") {
  }

  void Check(const Human& h) {
    cout << "Policeman: " << GetName() << " checks " <<
        h.GetType() << ". " << h.GetType() << "'s name is: " <<
        h.GetName() << endl;
  }

  void Walk(const string& destination) {
      cout << "Policeman: " << GetName() << " walks to: " << destination << endl;
  }
};

void VisitPlaces(Human& h, vector<string> places) {
  for (auto item : places) {
    h.Walk(item);
  }
}

int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});
    return 0;
}
