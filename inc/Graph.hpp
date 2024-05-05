#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <deque>
#include <vector>
#include <map>
#include "GameState.h"

using std::endl;
using std::cout;
using std::ostream;
using std::deque;

template <typename T>
class Graph;

template <typename T>
ostream& operator << (ostream& out, const Graph<T>& g);

template <typename T>
class Graph{
friend ostream& operator << <>(ostream& out, const Graph<T>& g);
private:
  std::vector<std::vector<T>> adjList;
  std::map<T, int> vertexToIndex;
  int numVertices;
  // Declare any variables needed for your graph

public:
  Graph();
  Graph(int);
  Graph(const Graph<T>& obToCopy) = delete;             // Prevent copy construction
  Graph& operator=(const Graph<T>& objToCopy) = delete; // Prevent copy assignment

  void addVertex(const T& vertex);
  void addEdge(const T& source, const T& target);
  void getPath(std::deque<T>& solution, const T& source, const T& target);
  
  int findVertexPos(const T& item) const;               // Optional
  bool vertexExists(const T& item) const;
  int getNumVertices() const;
};

/*********************************************
* Constructs an empty graph with a max number of verticies of 100
* 
*********************************************/
template<typename T>
Graph<T>::Graph() {
  adjList.resize(100);
  numVertices = 0;
}

/*********************************************
* Constructs an empty graph with a given max number of verticies
* 
*********************************************/
template<typename T>
Graph<T>::Graph(int maxVerticies){
  adjList.resize(maxVerticies);
  numVertices = 0;
}


/*********************************************
* Adds a Vertex to the Graph If number of verticies is less than the 
* Max Possible number of verticies.  
*********************************************/
template <typename T>
void Graph<T>::addVertex(const T& vertex){
  if (!vertexExists(vertex)){
    vertexToIndex[vertex] = numVertices++;
  }
}

/*********************************************
* Returns the current number of vertices
* 
*********************************************/
template<typename T>
int Graph<T>::getNumVertices() const {
  return numVertices;
}

/*********************************************
* Returns the position in the verticies list where the given vertex is located, -1 if not found.
* 
*********************************************/
template <typename T>
int Graph<T>::findVertexPos(const T& item) const {
  if (vertexExists(item)){
    return vertexToIndex.at(item);
  }
  return -1; //return negative one
}

/*********************************************
* Returns the position in the verticies list where the given vertex is located, -1 if not found.
* 
*********************************************/
template <typename T>
bool Graph<T>::vertexExists(const T& item) const {
  return vertexToIndex.find(item) != vertexToIndex.end();
} 


/*********************************************
* Adds an edge going in the direction of source going to target
* 
*********************************************/
template <typename T>
void Graph<T>::addEdge(const T& source, const T& target) {
    if (vertexExists(source) && vertexExists(target)) {
        adjList[vertexToIndex[source]].push_back(target);
    }
}

/*
  getPath will return the shortest path from source to dest.  
  Given the test graph:
  
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

getPath('a', 'f') should return 
'a' -> 'b' -> 'e' -> 'f'   or   'a' -> 'd' -> 'g' -> 'f'
*/

template <typename T>
void Graph<T>::getPath(std::deque<T>& solution, const T& source, const T& target) {
    if (!vertexExists(source) || !vertexExists(target)) {
        return;
    }

    std::map<T, T> parent;

    std::deque<T> queue;
    queue.push_back(source);

    while (!queue.empty()) {
        T current = queue.front();
        queue.pop_front();

        if (current == target) {
            T temp = target;
            while (!(temp == source)) {
                solution.push_front(temp);
                temp = parent[temp];
            }
            solution.push_front(source);
            return;
        }

        int index = vertexToIndex[current];
        for (const T& neighbor : adjList[index]) {
            if (parent.find(neighbor) == parent.end()) {
                parent[neighbor] = current;
                queue.push_back(neighbor);
            }
        }
    }
}

/*********************************************
* Returns a display of the graph in the format
* vertex: edge edge
Your display will look something like the following

    j: i f
    c: h a
    b: e a
    h: g c
    f: g i j e
    e: f b
    i: g f j
    d: g a
    g: h i f d
    a: b c d
*********************************************/
template <typename T>
ostream& operator << (ostream& out, const Graph<T>& g) {
  for (const auto& pair : g.vertexToIndex) {
        out << pair.first << ": ";
        for (const T& neighbor : g.adjList[pair.second]) {
            out << neighbor << " ";
        }
        out << "\n";
    }
    return out;
}

#endif
