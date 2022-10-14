#include <gtest/gtest.h>
#include "graph_calc.h"
#include <vector>



TEST(Matrix, matrixConstructors)
{
    using namespace GraphCalc;
    int size = 10;
    SetGraph graph = SetGraph(size);
    std::map<int, Node> nodes_map = std::map<int, Node>();
    nodes_map[0] = Node("0", 0);
    nodes_map[1] = Node("1", 1000, false);
    nodes_map[2] = Node("2", 2000);
    nodes_map[3] = Node("3", 10000);
    nodes_map[4] = Node("4", 1);
    nodes_map[5] = Node("5", 10);
    nodes_map[6] = Node("6", 100);
    nodes_map[7] = Node("7", 200);
    nodes_map[8] = Node("8", 1);
    nodes_map[9] = Node("9", 10, false);
    graph.add_edge(0, 1);
    graph.add_edge(0, 2);
    graph.add_edge(2, 1);
    graph.add_edge(1, 3);
    graph.add_edge(3, 4);
    //graph.add_edge(4, 1);
    graph.add_edge(4, 5);
    graph.add_edge(4, 6);
    graph.add_edge(6, 7);
    graph.add_edge(8, 9);
    nodes_map[10] = Node("10",5000);
    graph.add_vertex();
    graph.add_edge(10,3);
    calculate(graph, nodes_map);
    std::cout << "DONE" << std::endl;
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}