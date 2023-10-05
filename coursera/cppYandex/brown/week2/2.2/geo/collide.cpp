#include "geo2d.h"
#include "game_object.h"

#include "test_runner.h"

#include <vector>
#include <memory>

using namespace std;

// Определите классы Unit, Building, Tower и Fence так, чтобы они наследовались от
// GameObject и реализовывали его интерфейс.

template <typename T>
struct Collider : GameObject {
bool Collide(const GameObject& that) const final {
// Статически приводим тип *this к типу const T&, потому что мы знаем,
// что T — наш наследник (см. ниже)
return that.CollideWith(static_cast<const T&>(*this));
}
};

class Unit final: public Collider<Unit> {
private:
  geo2d::Point pos;
public:
  Unit(geo2d::Point position);
  geo2d::Point GetPosition() const;
  bool CollideWith(const Unit& that) const;
  bool CollideWith(const Building& that) const;
  bool CollideWith(const Tower& that) const;
  bool CollideWith(const Fence& that) const;
};

class Building final: public Collider<Building> {
private:
  geo2d::Rectangle pos;
public:
  Building(geo2d::Rectangle geometry);
  geo2d::Rectangle GetPosition() const;
  bool CollideWith(const Unit& that) const;
  bool CollideWith(const Building& that) const;
  bool CollideWith(const Tower& that) const;
  bool CollideWith(const Fence& that) const;
};

class Tower final: public Collider<Tower>{
private:
  geo2d::Circle pos;
public:
  Tower(geo2d::Circle geometry);
  geo2d::Circle GetPosition() const;
  bool CollideWith(const Unit& that) const;
  bool CollideWith(const Building& that) const;
  bool CollideWith(const Tower& that) const;
  bool CollideWith(const Fence& that) const;
};

class Fence final: public Collider<Fence> {
private:
  geo2d::Segment pos;
public:
  Fence(geo2d::Segment geometry);
  geo2d::Segment GetPosition() const;
  bool CollideWith(const Unit& that) const;
  bool CollideWith(const Building& that) const;
  bool CollideWith(const Tower& that) const;
  bool CollideWith(const Fence& that) const;
};

// definitions Unit
Unit::Unit(geo2d::Point position): pos(position){
}
geo2d::Point Unit::GetPosition() const{
  return pos;
}
bool Unit::CollideWith(const Unit& that) const{
  return geo2d::Collide(pos, that.GetPosition());
}
bool Unit::CollideWith(const Building& that) const{
  return geo2d::Collide(pos, that.GetPosition());
}
bool Unit::CollideWith(const Tower& that) const{
  return geo2d::Collide(pos, that.GetPosition());
}
bool Unit::CollideWith(const Fence& that) const{
  return geo2d::Collide(pos, that.GetPosition());
}

// definitions Building
Building::Building(geo2d::Rectangle position): pos(position){
}
geo2d::Rectangle Building::GetPosition() const{
  return pos;
}
bool Building::CollideWith(const Unit& that) const{
  return geo2d::Collide(pos, that.GetPosition());
}
bool Building::CollideWith(const Building& that) const{
  return geo2d::Collide(pos, that.GetPosition());
}
bool Building::CollideWith(const Tower& that) const{
  return geo2d::Collide(pos, that.GetPosition());
}
bool Building::CollideWith(const Fence& that) const{
  return geo2d::Collide(pos, that.GetPosition());
}

// definitions Tower
Tower::Tower(geo2d::Circle position): pos(position){
}
geo2d::Circle Tower::GetPosition() const{
  return pos;
}
bool Tower::CollideWith(const Unit& that) const{
  return geo2d::Collide(pos, that.GetPosition());
}
bool Tower::CollideWith(const Building& that) const{
  return geo2d::Collide(pos, that.GetPosition());
}
bool Tower::CollideWith(const Tower& that) const{
  return geo2d::Collide(pos, that.GetPosition());
}
bool Tower::CollideWith(const Fence& that) const{
  return geo2d::Collide(pos, that.GetPosition());
}

// definitions Fence
Fence::Fence(geo2d::Segment position): pos(position){
}
geo2d::Segment Fence::GetPosition() const{
  return pos;
}
bool Fence::CollideWith(const Unit& that) const{
  return geo2d::Collide(pos, that.GetPosition());
}
bool Fence::CollideWith(const Building& that) const{
  return geo2d::Collide(pos, that.GetPosition());
}
bool Fence::CollideWith(const Tower& that) const{
  return geo2d::Collide(pos, that.GetPosition());
}
bool Fence::CollideWith(const Fence& that) const{
  return geo2d::Collide(pos, that.GetPosition());
}

// Реализуйте функцию Collide из файла GameObject.h

bool Collide(const GameObject& first, const GameObject& second) {
  return first.Collide(second);
}

void TestAddingNewObjectOnMap() {
  // Юнит-тест моделирует ситуацию, когда на игровой карте уже есть какие-то объекты,
  // и мы хотим добавить на неё новый, например, построить новое здание или башню.
  // Мы можем его добавить, только если он не пересекается ни с одним из существующих.
  using namespace geo2d;

  const vector<shared_ptr<GameObject>> game_map = {
    make_shared<Unit>(Point{3, 3}),
    make_shared<Unit>(Point{5, 5}),
    make_shared<Unit>(Point{3, 7}),
    make_shared<Fence>(Segment{{7, 3}, {9, 8}}),
    make_shared<Tower>(Circle{Point{9, 4}, 1}),
    make_shared<Tower>(Circle{Point{10, 7}, 1}),
    make_shared<Building>(Rectangle{{11, 4}, {14, 6}})
  };

  for (size_t i = 0; i < game_map.size(); ++i) {
    Assert(
      Collide(*game_map[i], *game_map[i]),
      "An object doesn't collide with itself: " + to_string(i)
    );

    for (size_t j = 0; j < i; ++j) {
      Assert(
        !Collide(*game_map[i], *game_map[j]),
        "Unexpected collision found " + to_string(i) + ' ' + to_string(j)
      );
    }
  }

  auto new_warehouse = make_shared<Building>(Rectangle{{4, 3}, {9, 6}});
  ASSERT(!Collide(*new_warehouse, *game_map[0]));
  ASSERT( Collide(*new_warehouse, *game_map[1]));
  ASSERT(!Collide(*new_warehouse, *game_map[2]));
  ASSERT( Collide(*new_warehouse, *game_map[3]));
  ASSERT( Collide(*new_warehouse, *game_map[4]));
  ASSERT(!Collide(*new_warehouse, *game_map[5]));
  ASSERT(!Collide(*new_warehouse, *game_map[6]));

  auto new_defense_tower = make_shared<Tower>(Circle{{8, 2}, 2});
  ASSERT(!Collide(*new_defense_tower, *game_map[0]));
  ASSERT(!Collide(*new_defense_tower, *game_map[1]));
  ASSERT(!Collide(*new_defense_tower, *game_map[2]));
  ASSERT( Collide(*new_defense_tower, *game_map[3]));
  ASSERT( Collide(*new_defense_tower, *game_map[4]));
  ASSERT(!Collide(*new_defense_tower, *game_map[5]));
  ASSERT(!Collide(*new_defense_tower, *game_map[6]));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestAddingNewObjectOnMap);
  return 0;
}
