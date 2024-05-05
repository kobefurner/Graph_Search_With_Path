#include <iostream>
#include <string>
#include <deque>
#include "Graph.hpp"
#include "MC.h"

using std::cout;
using std::endl;
using std::stoi;
using std::deque;

//Function Headers
void populateNumbersGraph(Graph<char>& graphToPopulate);

bool testWithNumbers();
bool testMissionariesCannibals();
bool checkCase(string name, bool condition);

int main(int argc, char** argv){

   int test = 0;
   int count = 0;

   if(argc > 1){
      test = stoi(argv[1]);
   }
   switch(test){
      case 0:
         if (testWithNumbers()) count++;
         if (testMissionariesCannibals()) count++;
         cout << "Passed " << count << " out of 2 tests";
         return count != 2;
      case 1:
         return !testWithNumbers();
      case 2:
         return !testMissionariesCannibals();
   }
}

bool testWithNumbers(){
  bool passed = true;
  cout << "Numbers Graph" << endl;
  Graph<char> g(10);
  populateNumbersGraph(g);

  cout << g << endl;
  cout << "\nNumber Graph Test Cases" << endl;
  passed &= checkCase("Numbers Test size", g.getNumVertices() == 10);
  //passed &= checkCase("Vertex position test", g.findVertexPos(7) == 3);

  deque<char> solution;
  g.getPath(solution, 'a', 'f');
  passed &= checkCase("Solution implemented", solution.size() > 0);
  if(passed){
    passed &= checkCase("Checking path order 1", solution[0] == 'a');
    passed &= checkCase("Checking path order 2", solution[solution.size() - 1] == 'f');
    passed &= checkCase("Checking solution size", solution.size() <= 4);

    char possPath1[] = {'a', 'b', 'e', 'f'};
    char possPath2[] = {'a', 'd', 'g', 'f'};
 
    bool isPath = true;
    for(int i = 0; i < solution.size(); i++){
      if(solution[i] != possPath1[i] && solution[i] != possPath2[i]){
          isPath = false;
      }
    }
     passed &= checkCase("Is solution", isPath);
  }
  return passed;
}

bool testMissionariesCannibals(){
  bool passed = true;

  cout << "\nMissionaries Cannibals Solution" << endl;

  MC mc;
  cout << "one";
  cout << "two";
  deque<GameState> solution;
  mc.getGraphPath(solution, GameState(3, 3, true), GameState(0, 0, false));
  passed &= checkCase("Solution implemented", solution.size() > 0);
  if(passed){
    for(int i = 0; i < solution.size(); i++){
      cout <<  solution[i] << endl;
    }
    cout << "\nMissionaries Cannibals Test Cases" << endl;
    passed &= checkCase("Solution Size: ", solution.size() == 12);
    if (solution.size() > 0 ) {
      passed &= checkCase("Solution Order 0: ", solution[0] == GameState(3, 3, true));
    } else {
      passed &= checkCase("Solution Order 0: ", false); // Failed test, solution didn't have any entries
    }
    if (solution.size() >= 12 ) {
      passed &= checkCase("Solution Order 12: ", solution[11] == GameState(0, 0, false));
    } else {
      passed &= checkCase("Solution Order 12: ", false); // Failed test, solution didn't have a 12th entry
    }

    bool isValid = true;

    for(int i = 1; i < solution.size(); i++){
      if(!solution[i].isNeighbor(solution[i-1])){
        isValid = false;
      }
    }
    passed &= checkCase("Valid Solution", isValid);
  }
  return passed;
}

void populateNumbersGraph(Graph<char>& g){
  char verts [] = {'j', 'c', 'b', 'h', 'f', 'e', 'i', 'd', 'g', 'a'};
  for(int i = 0; i < 10; i++){
    g.addVertex(verts[i]);
  }

  g.addEdge('a', 'b');
  g.addEdge('a', 'c');
  g.addEdge('a', 'd');
  g.addEdge('b', 'e');
  g.addEdge('e', 'f');
  g.addEdge('f', 'g');
  g.addEdge('d', 'g');
  g.addEdge('g', 'h');
  g.addEdge('c', 'h');
  g.addEdge('g', 'i');
  g.addEdge('f', 'i');
  g.addEdge('f', 'j');
  g.addEdge('j', 'i');

  g.addEdge('b', 'a');
  g.addEdge('c', 'a');
  g.addEdge('d', 'a');
  g.addEdge('e', 'b');
  g.addEdge('f', 'e');
  g.addEdge('g', 'f');
  g.addEdge('g', 'd');
  g.addEdge('h', 'g');
  g.addEdge('h', 'c');
  g.addEdge('i', 'g');
  g.addEdge('i', 'f');
  g.addEdge('j', 'f');
  g.addEdge('i', 'j');

}


/*
Numbers Undirected Graph

[a]-----------[c]
|  \            \
|   \            \
[b]  [d]----[g]---[h]
|          /  \
|         /    \
|        /      \
|     [f]--------[i]
|    /   \       /
|   /     \     /
|  /       \   /
[e]         [j]

*/

bool checkCase(string name, bool condition){
  if(!condition){
      cout << "Failed: " << name << endl;
  }else{
       cout << "Passed: " << name << endl;
  }return condition;
}