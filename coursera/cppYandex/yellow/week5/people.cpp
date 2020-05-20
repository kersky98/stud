#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Human {
public:
  Human(string name, string type) {
    Name = name;
    peopleType = type;
  }
  virtual void Walk(string destination) = 0;
  virtual ~Human(){};
  string GetName(){
    return Name;
  };
  string GetType(){
    return peopleType;
  };
private:
    string Name;
    string peopleType;
};

class Student : public Human {
public:
  Student(string name, string favouriteSong): Human(name, "Student"){
    //Name = name;
    FavouriteSong = favouriteSong;
  }

  void Learn() {
      cout << "Student: " << GetName() << " learns" << endl;
  }

  void Walk(string destination) {
      cout << "Student: " << GetName() << " walks to: " << destination << endl;
      cout << "Student: " << GetName() << " sings a song: " << FavouriteSong << endl;
  }

  void SingSong() {
      cout << "Student: " << GetName() << " sings a song: " << FavouriteSong << endl;
  }

private:
  string FavouriteSong;
};

class Teacher: public Human{
public:
  Teacher(string name, string subject): Human(name, "Teacher") {
    Subject = subject;
  }

  void Teach() {
    cout << "Teacher: " << GetName() << " teaches: " << Subject << endl;
  }

  void Walk(string destination) {
    cout << "Teacher: " << GetName() << " walks to: " << destination << endl;
  }

private:
  string Subject;
};

class Policeman: public Human {
public:
  Policeman(string name): Human(name, "Policeman") {
  }

  void Check(Human& h) {
    cout << "Policeman: " << GetName() << " checks " <<
        h.GetType() << ". " << h.GetType() << "'s name is: " <<
        h.GetName() << endl;
  }

  void Walk(string destination) {
      cout << "Policeman: " << GetName() << " walks to: " << destination << endl;
  }
};

void VisitPlaces(Human& h, vector<string> places) {
  for (auto item : places) {
    h.Walk(item);
  }
}






/*
class Student {
public:

    Student(string name, string favouriteSong) {
        Name = name;
        FavouriteSong = favouriteSong;
    }

    void Learn() {
        cout << "Student: " << Name << " learns" << endl;
    }

    void Walk(string destination) {
        cout << "Student: " << Name << " walks to: " << destination << endl;
        cout << "Student: " << Name << " sings a song: " << FavouriteSong << endl;
    }

    void SingSong() {
        cout << "Student: " << Name << " sings a song: " << FavouriteSong << endl;
    }

public:
    string Name;
    string FavouriteSong;
};


class Teacher {
public:

    Teacher(string name, string subject) {
        Name = name;
        Subject = subject;
    }

    void Teach() {
        cout << "Teacher: " << Name << " teaches: " << Subject << endl;
    }

    void Walk(string destination) {
        cout << "Teacher: " << Name << " walks to: " << destination << endl;
    }

public:
    string Name;
    string Subject;
};


class Policeman {
public:
    Policeman(string name) {
        Name = name;
    }

    void Check(Teacher t) {
        cout << "Policeman: " << Name << " checks Teacher. Teacher's name is: " << t.Name << endl;
    }

    void Check(Student s) {
        cout << "Policeman: " << Name << " checks Student. Student's name is: " << s.Name << endl;
    }

    void Check(Policeman p) {
        cout << "Policeman: " << Name << " checks Policeman. Policeman's name is: " << p.Name << endl;
    }

    void Walk(string destination) {
        cout << "Policeman: " << Name << " walks to: " << destination << endl;
    }

public:
    string Name;
};


void VisitPlaces(Teacher t, vector<string> places) {
    for (auto p : places) {
        t.Walk(p);
    }
}

void VisitPlaces(Student s, vector<string> places) {
    for (auto p : places) {
        s.Walk(p);
    }
}

void VisitPlaces(Policeman pol, vector<string> places) {
    for (auto p : places) {
        pol.Walk(p);
    }
}
*/

int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});
    return 0;
}
