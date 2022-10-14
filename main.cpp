#include "graph_calc.h"
#include <fstream>
#include <iostream>

int main()
{
    std::ifstream fin = std::ifstream("../inp/test.txt");
    if (!fin.is_open())
    {
        return 1;
    }

    std::map<int, GraphCalc::Node> nodes = std::map<int, GraphCalc::Node>();
    SetGraph graph = GraphCalc::parse_graph(fin, nodes);
    fin.close();

    GraphCalc::calculate(graph, nodes);

    std::string str_color = "";
    for (auto pair : nodes)
    {
        std::cout << pair.first << " " << pair.second.name << " ";
        if (pair.second.color == 2)
        {
            if (pair.second.defined)
            {
                std::cout << "Value: " << pair.second.val << std::endl;
                continue;
            }
            std::cout << "Error: Vertex is not defined" << std::endl;
            continue;
        }
        if (pair.second.color == 3)
            std::cout << "Error: Cycle vertex" << std::endl;
    }

    return 0;
}
