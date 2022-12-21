# industrial_cpp_task1

## Calculator usage
Sample of test.txt:
```
A0=0+B2+A1
B2=A1+2000
A1=A3+1000
A3=10000+A4
A4=A1+A5+1+A6
A6=100
A7=200+A8
A5=10
A8=2
G9=G10+1
```

usage:
```
./solution path_to_file.txt
```

library usage:

```
GraphCalc::calculate(SetGraph, map<int, GraphCalc::Node>& nodes);
```
Method calculates nodes "in place". Results will be in `nodes`.

Each `Node` has:
- value -- value of this node
- bool defined
- color -- color of node. 0 -- unchecked, 1 -- processing, 2 -- checked, 3 -- cycle

Function `parse_graph(std::istream &fin, std::map<int, Node> &nodes);` returns graph and fill nodes with default values. Data in stream should be in following format:
```node_name_i=value+...+node_name_j+...+node_name_k+...value```

Example:
`A0=0+B2+A1`

## SetGraph usage

class SetGraph contains graph in `std::set`

methods:
```
void add_edge(int from, int to); // add edge in graph

void add_vertex(); // add vertex in graph

int vertices_count() const; // returns vertex count

std::vector<int> get_next_vertices(int vertex) const; // returns next verticies

std::vector<int> get_prev_vertices(int vertex) const; // returns previous verticies
```

Example:
```
SetGraph graph = SetGraph(3);
graph.add_edge(0, 1);
graph.add_edge(0, 2);
auto next_vert = graph.get_next_vertices(0);
```
