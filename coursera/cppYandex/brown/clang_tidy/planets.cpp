#include <algorithm>
#include <array>
#include <iostream>
#include <string_view>

using namespace std;

const array PLANETS{
    "Mercury"sv, "Venus"sv, "Earth"sv,
    "Mars"sv, "Jupiter"sv, "Saturn"sv,
    "Uranus"sv, "Neptune"sv,
};

bool IsPlanet(string_view name) {
    return find(begin(PLANETS), end(PLANETS), name) != end(PLANETS);
}

void Test(string_view name) {
    cout << name << " is " << (IsPlanet(name) ? ""sv : "NOT "sv) << "a planet"sv << endl;
}

int main() {
    Test("Earth"sv);
    Test("Jupiter"sv);
    Test("Pluto"sv);
    Test("Moon"sv);
}


/*
#include <iostream>
#include <string_view>

using namespace std;

const int NUM_PLANETS = 8;
const string_view PLANETS[] = {
    "Mercury"sv, "Venus"sv, "Earth"sv,
    "Mars"sv, "Jupiter"sv, "Saturn"sv,
    "Uranus"sv, "Neptune"sv,
};

bool IsPlanet(string_view name) {
    for (int i = 0; i < NUM_PLANETS; ++i) {
        if (PLANETS[i] == name) {
            return true;
        }
    }
    return false;
}

void Test(string_view name) {
    cout << name << " is " << (IsPlanet(name) ? ""sv : "NOT "sv) << "a planet"sv << endl;
}

int main() {
    Test("Earth"sv);
    Test("Jupiter"sv);
    Test("Pluto"sv);
    Test("Moon"sv);
} */
