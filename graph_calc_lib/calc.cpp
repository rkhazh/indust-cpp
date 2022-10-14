#include "graph_calc.h"

void GraphCalc::calculate(const SetGraph &graph, std::map<int, GraphCalc::Node> &nodes)
{
    std::stack<int> stack;
    std::stack<int> stack_rev;
    for (int edg = 0; edg < graph.vertices_count(); ++edg)
    {
        stack.push(edg);
        while (!stack.empty())
        {
            int cur = stack.top();
            stack.pop();
            switch (nodes[cur].color)
            {
            case 0:
                nodes[cur].color = 1;
                break;
            case 3:
                continue;
            case 1:
                continue;
            }
            auto const &children = graph.get_next_vertices(cur);
            if (children.empty())
            {
                nodes[cur].color = 2;
                continue;
            }
            bool has_white_child = false; // #WhiteVertexMatter
            for (auto const &child : children)
            {
                switch (nodes[child].color)
                {
                case 1: // gray
                    // cycle
                    nodes[cur].color = 3;
                    while (!stack_rev.empty())
                    {
                        int cur_rev = stack_rev.top();
                        stack_rev.pop();
                        nodes[cur_rev].color = 3;
                    }
                    break;
                case 0: // white
                    has_white_child = true;
                    stack.push(child);
                    break;
                case 3:
                    nodes[cur].color = 3;
                    while (!stack_rev.empty())
                    {
                        int cur_rev = stack_rev.top();
                        stack_rev.pop();
                        nodes[cur_rev].color = 3;
                    }
                    break;
                };
            }
            if (nodes[cur].color == 1)
            {
                if (!has_white_child)
                {
                    for (auto const &child : children)
                    {
                        if (!nodes[child].defined)
                        {
                            nodes[cur].defined = false;
                            break;
                        }
                        nodes[cur].val += nodes[child].val;
                    }
                    nodes[cur].color = 2;
                }
                else
                {
                    // check this node later, when it will not have any white children
                    stack_rev.push(cur);
                }
            }
        }
        while (!stack_rev.empty())
        {
            int cur = stack_rev.top();
            stack_rev.pop();
            assert(nodes[cur].color == 1);
            auto const &children = graph.get_next_vertices(cur);
            for (auto const &child : children)
            {
                assert(nodes[child].color == 2);
                if (!nodes[child].defined)
                {
                    nodes[cur].defined = false;
                    break;
                }
                nodes[cur].val += nodes[child].val;
            }
            nodes[cur].color = 2;
        }
    }
}

bool is_number(const std::string &s)
{
    for (char const &ch : s)
    {
        if (std::isdigit(ch) == 0)
            return false;
    }
    return true;
}

SetGraph GraphCalc::parse_graph(std::istream &fin, std::map<int, Node> &nodes)
{
    std::string line;
    std::string key;
    std::size_t counter = 0;
    std::size_t cur_id = 0;
    std::map<std::string, int> names = std::map<std::string, int>(); // name -> vertex_id
    SetGraph graph = SetGraph(0);
    while (!fin.eof())
    {
        std::getline(fin, line);
        key = line.substr(0, line.find('='));
        if (names.find(key) == names.end())
        {
            // add key
            cur_id = counter++;
            names[key] = cur_id;
            nodes[cur_id] = Node(key, 0, false);
            graph.add_vertex();
        }
        else
        {
            cur_id = names[key];
        }
        line.erase(0, line.find('=') + 1);
        std::string token;
        std::size_t pos = 0;
        while (line.size() != 0)
        {
            pos = line.find('+');
            pos = pos != std::string::npos ? pos : line.size();
            // for each token in one line
            token = line.substr(0, pos);
            if (is_number(token))
            {
                nodes[cur_id].val += std::stoi(token);

                nodes[cur_id].defined = true;
            }
            else
            {
                // add dependency
                if (names.find(token) == names.end())
                {
                    // token not in graph
                    names[token] = counter;
                    nodes[counter] = Node(token, 0, false);
                    graph.add_vertex();
                    graph.add_edge(cur_id, counter++);
                }
                else
                {
                    graph.add_edge(cur_id, names[token]);
                }
            }
            line.erase(0, pos + 1);
        }
    }
    return graph;
}
