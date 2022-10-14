#ifndef SET_GRAPH_H
#define SET_GRAPH_H

#include <iostream>
#include <set>
#include <vector>


class SetGraph {
public:

    explicit SetGraph(size_t vertices_count);

    SetGraph(const SetGraph&);

    ~SetGraph() = default;

    void add_edge(int from, int to);

    void add_vertex();

    int vertices_count() const;

    std::vector<int> get_next_vertices(int vertex) const;

    std::vector<int> get_prev_vertices(int vertex) const;

private:
    std::vector<std::set<int>> graph;
};

#endif
