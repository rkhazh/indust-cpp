#include "set_graph.h"

SetGraph::SetGraph(size_t vertices_count)
{
    graph.resize(vertices_count);
}

SetGraph::SetGraph(const SetGraph &input_graph)
{
    graph.resize(input_graph.vertices_count());
    for (int from = 0; from < input_graph.vertices_count(); ++from)
    {
        auto children = input_graph.get_next_vertices(from);
        for (auto const &to : children)
        {
            this->add_edge(from, to);
        }
    }
}

void SetGraph::add_vertex()
{
    graph.emplace_back(std::set<int>());
}

void SetGraph::add_edge(int from, int to)
{
    graph[from].insert(to);
}

int SetGraph::vertices_count() const { return graph.size(); }

std::vector<int> SetGraph::get_next_vertices(int vertex) const
{
    std::vector<int> result = std::vector<int>(graph[vertex].begin(), graph[vertex].end());
    return result;
}

std::vector<int> SetGraph::get_prev_vertices(int vertex) const
{
    std::vector<int> result;
    for (int from = 0; from < graph.size(); ++from)
    {
        if (from == vertex)
            continue;
        for (auto const &i : graph[from])
        {
            if (vertex == i)
            {
                result.push_back(from);
                break;
            }
        }
    }
    return result;
}
