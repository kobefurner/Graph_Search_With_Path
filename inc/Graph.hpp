#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <deque>

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
Graph<T>::Graph(){

}

/*********************************************
* Constructs an empty graph with a given max number of verticies
* 
*********************************************/
template<typename T>
Graph<T>::Graph(int maxVerticies){

}


/*********************************************
* Adds a Vertex to the GraphIf number of verticies is less than the 
* Max Possible number of verticies.  
*********************************************/
template <typename T>
void Graph<T>::addVertex(const T& vertex){

}

/*********************************************
* Returns the current number of vertices
* 
*********************************************/
template<typename T>
int Graph<T>::getNumVertices() const {
  return 0;
}

/*********************************************
* Returns the position in the verticies list where the given vertex is located, -1 if not found.
* 
*********************************************/
template <typename T>
int Graph<T>::findVertexPos(const T& item) const {
  return -1; //return negative one
}

/*********************************************
* Returns the position in the verticies list where the given vertex is located, -1 if not found.
* 
*********************************************/
template <typename T>
bool Graph<T>::vertexExists(const T& item) const {
  return false;
} 


/*********************************************
* Adds an edge going in the direction of source going to target
* 
*********************************************/
template <typename T>
void Graph<T>::addEdge(const T& source, const T& target){
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
  // Load the answer into the solution deque
 
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
  return out;
}

#endif
