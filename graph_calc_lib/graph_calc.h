#ifndef GRAPH_CALC_H
#define HRAPH_CALC_H

#include <stack>
#include <map>
#include <string>
#include <cassert>
#include <sstream>
#include "set_graph.h"

namespace GraphCalc
{
    struct Node
    {
        std::string name;
        int val = 0;
        bool defined = true;
        std::uint8_t color = 0; // 0 - white, 1 - gray, 2 - black, 3 - yellow

        explicit Node(std::string name = "", int val = 0, bool defined = true) : name(std::move(name)), val(val),
                                                                                 defined(defined){};
    };

    void calculate(SetGraph const &graph, std::map<int, Node> &nodes); // Calculates graph sum of vertices

    SetGraph parse_graph(std::istream &fin, std::map<int, Node> &nodes);
}

#endif
