#include <string>
#include <iostream>

#ifndef GAMESTATE_H
#define GAMESTATE_H

using std::cout;
using std::endl;
using std::ostream;
using std::string;

// Set up some forward declares
class GameState;
namespace std {
  template<>
  struct hash<GameState> {
  public:
    size_t operator()(const GameState& obj) const; 
  };
}

// forward declare
class GameState{
// This friend is in case a std::unordered_map and/or std::unordered_set is used for the graph, which uses this overloaded definition of hash.
friend size_t std::hash<GameState>::operator()(const GameState&) const;
friend ostream& operator<<(ostream& out, GameState& state);
public:
  GameState(){ }
  GameState(int missionaries, int cannibals, bool boatIsLeft) {
    this->missionaries = missionaries;
    this->cannibals = cannibals;
    this->boatIsLeft = boatIsLeft;
  }
  int getMissionariesLeft() const { return missionaries; }
  int getCannibalsLeft() const { return cannibals; }

  bool isValidState() const{

  //Missionaries outnumber canabals on right side
  if (missionaries < cannibals && missionaries > 0){
    return false;
  }
  //Missionaries outnumber Cannibals left isde
  if(3-missionaries < 3-cannibals && 3-missionaries > 0){
    return false;
  }
  if(missionaries < 0 || cannibals < 0 || missionaries > 3 || cannibals > 3){
    return false;
  }
    return true;
  }
  bool isBoatLeft() const {
    return boatIsLeft;
  }

  bool operator==(const GameState& other) const {
    return other.missionaries == missionaries && other.cannibals == cannibals && other.boatIsLeft == boatIsLeft;
  }

  // This overload is in case a std::map is used for the graph, which requires this. 
  bool operator<(const GameState& other) const {
    if (other.missionaries < missionaries) {
      return true;
    } else if (other.missionaries == missionaries && other.cannibals < cannibals) {
      return true;
    } else if (other.missionaries == missionaries && other.cannibals == cannibals && other.boatIsLeft < boatIsLeft) {
      return true;
    } else {
      return false;
    }
  }

  bool isNeighbor(const GameState& other) const {
    if (boatIsLeft == other.boatIsLeft){
      return false;
    }
    int m = abs(missionaries-other.missionaries);
    int c = abs(cannibals - other.cannibals);
    int boat = m + c;
    if(boat > 2){
      return false;
    }

    return true;
  }

private:
  int missionaries{0};
  int cannibals{0};
  bool boatIsLeft{false};

};

ostream& operator<<(ostream& out, GameState& state) {
  for (int i = 0; i < state.missionaries; i++) {
    out << "M";
  }

  for (int i = 0; i < state.cannibals; i++) {
    out << "C";
  }

  if (state.boatIsLeft) {
    out << " B~~~~~~~ ";
  }
  else {
    out << " ~~~~~~~B ";
  }
  for (int i = 0; i < (3 - state.missionaries); i++) {
    out << "M";
  }
  for (int i = 0; i < (3 - state.cannibals); i++) {
    out << "C";
  }
  return out;
}

namespace std {
  //template<>
  size_t hash<GameState>::operator()(const GameState& obj) const {
    size_t val{ 0 };
    val &= (unsigned long long)(0x0001 & obj.boatIsLeft) << 62ull;
    // get 31 bits of missionaries and shift it over 31
    val &= (unsigned long long)(0x8FFF & obj.missionaries) << 31ull;
    // get 31 bits of cannibals and bitwise-and it in
    val &= (0x8FFF & obj.cannibals);
    // Consider this val the hashed value. It's not a well distributed hash, but it works just fine for this use case
    return val;
  }
}

#endif