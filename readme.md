# Graphs
 Finding a route from one vertex to another in a graph can solve many different types of problems. In this assignment you will create a templated graph. You will use the graph to solve the missionaries vs cannibals problem.

## Goals:
The purpose of this project is to practice using graphs, graph algorithms, and templated classes.

## Requirements:
Graph class

This class creates and manages a Graph.
You are welcome to create and add whatever variables you see fit to implement the graph.
At minimum, you must implement the following public methods:

+ Graph(); // Constructs an empty graph with a max number of verticies
+ Graph(int); // Creates a graph with the given max number of verticies
+ void addVertex(const T& vertex); // Adds a vertex to the graph
+ void addEdge(const T& source, const T& target); // Adds an edge to the graph from vertex "source" going towards "target"
+ void getPath(std::deque<T>& solution, const T& source, const T& target); // Computes the path from source to target.  The solution container has the entire path of vertices, starting at the source node, ending at the target, and all vertices in between. The solution container is a doubly ended queue which allows you to push and pop on the front and/or the back.
+ int getNumVertices(); // Returns the current number of verticies

Optional for closed adjacency list graphs: 
+ int findVertexPos(const T& item); // Returns the index position in list where the given vertex is found. Useful if an array or vertex based approach is used. This method is not necessary if a map approach is used.
+ friend ostream& operator << <>(ostream & out, const Graph<T>& g); // Returns the output stream of the nodes in a display of your choice.  This method is for debugging and will not be tested

Note that this assignment utilizes const correctness throughout. Ensure any custom methods you write keep appropriate things constant. If not the compiler won't compile the assignment.

Also, this assignment disables the graph copy constructor and copy assignment. Students shouldn't be cloning the graph, but in case a student attempts this, the code won't compile.  

# Assignment parts:

The first part of the assignment tests using this graph and seeks a path from 'a' to 'f'.

```
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
```

The second part of the assignment tests the missionaries vs cannibals graph whose image is provided in Canvas.

## Graph approaches

Several options exist to represent a graph. For this assignment, students typically implement one of these three approaches:

1. An adjacency list. An index in the first array represents a source vertex, and the value in that first array index is a linked list whose nodes are vertices which connect with the source vertex.  This approach often utilizes a helper array to map vertex values to array indexes.

Suppose the vertices are loaded in this order: 'j', 'c', 'b', 'h', 'f', 'e', 'i', 'd', 'g', 'a'.  The helper array of size 10 is needed to map indexes. Vertex 'j' will be at index 0, vertex 'c' will be at index 1, and so on. 

The array of linked lists (or vector of linked lists) will then have the following:

[0] = 'i' -> 'f'
[1] = 'h' -> 'a'
[2] = 'e' -> 'a'
[3] = 'g' -> 'c'
[4] = 'g' -> 'i' -> 'j' -> 'e'
[5] = 'f' -> 'b'
[6] = 'g' -> 'f' -> 'j'
[7] = 'g' -> 'a'
[8] = 'h' -> 'i' -> 'f' -> 'd'
[9] = 'b' -> 'c' -> 'd'

So suppose the graph is checked to see if 'f' has an edge to connect to 'j'. First the helper array finds 'f' at index 4, and so index 4 of the array of linked lists has all the edges for 'f'. Iterating down that linked list finds 'g', then 'i', then 'j'. Since 'j' is the target, node 'f' has an edge with node 'j'.

2. An array of arrays. (Or a vector of vectors.) This approach is very similar to the prior item.  An index in the first array represents a source vertex, and the value in that first array index is another array whose values are vertices which connect with the source vertex. This approach often utilizes a helper array to map vertex values to array indexes.

An example of this using the prior sample graph (vertices with values 'a' through 'j'):

Suppose the vertices are loaded in this order: 'j', 'c', 'b', 'h', 'f', 'e', 'i', 'd', 'g', 'a'.  The helper array of size 10 is needed to map indexes. Vertex 'j' will be at index 0, vertex 'c' will be at index 1, and so on. 

The array of arrays (or vector of vectors) will then have the following:

[0] = 'i' 'f'
[1] = 'h' 'a'
[2] = 'e' 'a'
[3] = 'g' 'c'
[4] = 'g' 'i' 'j' 'e'
[5] = 'f' 'b'
[6] = 'g' 'f' 'j'
[7] = 'g' 'a'
[8] = 'h' 'i' 'f' 'd'
[9] = 'b' 'c' 'd'

So suppose the graph is checked to see if 'f' has an edge to connect to 'j'. First the helper array finds 'f' at index 4, and so index 4 of the array of arrays has all the edges for 'f'. Iterating down that array finds 'g', then 'i', then 'j'. Since 'j' is the target, node 'f' has an edge with node 'j'.

3. A map of key/value pairs. This is most commonly implemented using std::unordered_map or std::map. The key is of data type T (templated), the value is a container of values of type char (this container can be an array, a vector, a forward list, a doubly ended queue, or anything that just holds a set of items of type T).

An example of this using the prior sample graph, using a list for the value.

[Key] =  Value
--------------
['a'] = 'b' -> 'c' -> 'd'
['b'] = 'e' -> 'a'
['c'] = 'h' -> 'a'
['d'] = 'g' -> 'a'
['e'] = 'f' -> 'b'
['f'] = 'g' -> 'i' -> 'j' -> 'e'
['g'] = 'h' -> 'i' -> 'f' -> 'd'
['h'] = 'g' -> 'c'
['i'] = 'g' -> 'f' -> 'j'
['j'] = 'i' -> 'f'

So suppose the graph is checked to see if 'f' has an edge to connect to 'j'. Also suppose that this map is given variable name sampleGraph. Simply iterate down all the values found at simpleGraph['f']. Iterating down that finds 'g', then 'i', then 'j'. Since 'j' is the target, node 'f' has an edge with node 'j'.

Note that using std::unordered_map or std::map requires a small learning curve. For example, these maps use std::pair for key/value pairs, where the key is pair's `first` and the value is pair's `second`. Inserting an item requires first checking if the key exists. If the key does not exist, then create a pair object where the `first` is the key and the `second` is empty. (If you are feeling adventurous, emplace allows for avoiding explicitly mentioning the pair on creation.) Now after this if statement, obtain the `second` through the map's [] operater passing in the key, then invoke .insert, passing in the value.

Using a map does tend to result in both cleaner code and less code.

## Traversal approaches to find a path from start to finish

Three approaches can be used here. 

1. Depth-first traversal. This is fundamentally rooted in using a stack to "dive deep" down a graph, and if the target isn't found, unwind the stack to dive deep down another path. Numerous implementations of depth-first traversal can be found online and in various texts. A great feature of depth first traversal is that once a the target is reached, the stack has the full vertex-by-vertex path embedded in it. One implementation is given below in pseudocode, and uses recursion, because recursion is a built-in stack.  

Public getPath() method:

  // When a vertex is visited, indicate it in a container (discovered). An unordered_set of type T works. A map of key T and value bool also works. An array of booleans also works provided each vertex is properly mapped to an index.
  // Add the start vertex into the discovered container
  
  // Create a boolean called `found`, initialize it to false
  
  // Call a private getPath() method, passing in the solution, visited, found, start, and target. This private method handles the recursion.

  // The recursion is done. Check if found is set to true
  //   If so, add the start into the front of solution container.
    
Private getPath() method: // All parameters should be by-reference. The start is referred to as `curr`

  // Iterate through all neighbors of curr
  //   Check if this neighbor is the finish vertex
  //     Set found to true. Add the neighbor to the front of the solution container, and return
  //   If the neighbor isn't the destination, then check if this neighbor has been discovered yet
  //     Add the neighbor into the discovered container
  //     Recursively call getPath again. Pass in appropraite arguments. The current neighbor becomes the new `curr`
  //     Now that the recursive call has returned, check if a solution was found
  //       If so, add this neighbor into the discovered container, and return
  
2. Breadth-first traversal. This is fundamentally rooted in using a queue to "sweep outward" through a frontier in a graph. If a target isn't found down one path, the queue is ready to provide other vertices to check as it sweeps outward. Numerous implementations of depth-first traversal can be found online and in various texts. 

Below is a psuedocode for a breath first search:
```
  // When a vertex is visited, indicate it in a container (discovered). An unordered_set of type T works. A map of key T and value bool also works. An array of booleans also works provided each vertex is properly mapped to an index.

  // Create a parent container. The purpose of this container is to track from which vertex another vertex came from. For example, if a graph path from 'a' to 'f' is 'a' -> 'd' -> 'g' -> 'f', then the parent value for 'f' is 'g', the parent value for 'g' is 'd', the parent value for 'd' is 'a', and the parent value for 'a' is 'a' to indicate the start vertex. This container can be an array (if each vertex is mapped to an index), or map with the key of type T and value of type T.  

  // Create a queue (frontier)

  // Add the start vertex to the frontier queue
  // Add the start vertex to the discovered container

  // While the frontier queue has items
  //   Get the next vertex from the queue
  //   Iterate through all neighbor vertices of that vertex
  //     Check if this neighbor hasn't been discovered yet
  //       Add this neighbor to the discovered container
  //       Add the neighbor to the frontier queue
  //       Add to the parent container the prior vertex this neighbor arrived from
  //       Check if the neighbor is the destination vertex (if so, a solution has been found!)
  //         Use a while loop to walk back through parent, keep looping until a vertex isn't its own parent (indicating the start vertex)
  //           Add the current vertex to the solution
  //           Set the current vertex to be the current vertex's parent
  //         When the while loop is done, return the solution
```  

3. Dijkstra's shortest path algorithm. This process will reach the target, and if multiple paths to the target exist, will find the path with the shortest cost. Here treat every edge of having a length of size 1. Numerous implementations of this algorithm exist online and in other texts, and you can refer to those. Note that most of these solutions simply determine if a path exists from a start vertex to an end vertex, and what the total path length is, but does not provide a vertex-by-vertex order of the path. This assignment is not concerned with the length of the path, but is concerned with the vertex-by-vertex path.  

The Dijskta's shortest path algorithm can be easily modified for a vertex-by-vertex path. Start by creating a parent container. The purpose of this container is to track from which vertex another vertex came from. For example, if a graph path from 'a' to 'f' is 'a' -> 'd' -> 'g' -> 'f', then the value for 'f' is 'g', the value for 'g' is 'd', the value for 'd' is 'a', and the value for 'a' is 'a' to indicate the start vertex. This container can be an array (if each vertex is mapped to an index), or map with the key of type T and value of type T. Once a parent container is created, then any time a new shortest weight is found and updated, also update the parent container indicating this new relationship. For example, if a shortest path is found to 'g' by going through 'd', then update the parent container so that the vertex 'g' has value 'd' indicating that 'g' arrived from 'd'. Upon reaching the destination, then iterate backward through the parent container, from the destination walking back to the start node, each iteration adding the current vertex to the solution container. 

Implement vertextExists
